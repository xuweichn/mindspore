# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
""" test adam """
import numpy as np
import pytest

import mindspore.nn as nn
from mindspore import Tensor, Parameter
from mindspore.common.api import _executor
from mindspore.nn import TrainOneStepCell, WithLossCell
from mindspore.nn.wrap.cell_wrapper import _VirtualDatasetCell
from mindspore.nn.optim import Adam, AdamWeightDecay, Lamb, Momentum
from mindspore.ops import operations as P
from mindspore import context


class Net(nn.Cell):
    """Net definition"""
    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Dense(128, 768, activation='relu')
        self.fc2 = nn.Dense(128, 768, activation='relu')
        self.fc3 = nn.Dense(128, 768, activation='relu')
        self.fc4 = nn.Dense(768, 768, activation='relu')
        self.relu4 = nn.ReLU()
        self.relu5 = nn.ReLU()
        self.transpose = P.Transpose()
        self.matmul1 = P.MatMul()
        self.matmul2 = P.MatMul()

    def construct(self, x):
        q = self.fc1(x)
        k = self.fc2(x)
        v = self.fc3(x)
        k = self.transpose(k, (1, 0))
        c = self.relu4(self.matmul1(q, k))
        s = self.relu5(self.matmul2(c, v))
        s = self.fc4(s)
        return s


class Net2(nn.Cell):
    """Net definition"""
    def __init__(self, strategy1, strategy2):
        super(Net2, self).__init__()
        self.fc1 = P.MatMul().shard(strategy=strategy1)
        self.fc2 = P.MatMul().shard(strategy=strategy2)
        self.p1 = Parameter(Tensor(np.ones([48, 64]).astype(np.float32)), name="weight1")
        self.p2 = Parameter(Tensor(np.ones([64, 16]).astype(np.float32)), name="weight2")

    def construct(self, x, y):
        x = self.fc1(x, self.p1)
        x = self.fc2(x, self.p2)
        return x - y


def auto_parallel_compile_net(mode, dev_num, strategy1=None, strategy2=None):
    context.set_context(mode=context.GRAPH_MODE)
    context.set_auto_parallel_context(parallel_mode=mode, device_num=dev_num, enable_parallel_optimizer=True)
    inputs = Tensor(np.ones([32, 48]).astype(np.float32))
    label = Tensor(np.zeros([32, 16]).astype(np.float32))
    net = Net2(strategy1, strategy2)
    net = _VirtualDatasetCell(net)
    optimizer = Momentum(net.trainable_params(), learning_rate=0.1, momentum=0.9)
    train_network = TrainOneStepCell(net, optimizer)
    train_network.set_auto_parallel()
    train_network.set_train()
    _executor.compile(train_network, inputs, label, phase="train", auto_parallel_mode=True)
    context.reset_auto_parallel_context()
    return train_network


def test_auto_parallel_momentum_1():
    auto_parallel_compile_net("auto_parallel", 8)


def test_auto_parallel_momentum_2():
    # data parallel case
    auto_parallel_compile_net("auto_parallel", 8, ((8, 1), (1, 1)), ((8, 1), (1, 1)))


def test_auto_parallel_momentum_3():
    # hybrid parallel case
    # weight1 could not be shard and weight2 is repeated
    train_network = auto_parallel_compile_net("semi_auto_parallel", 32, ((4, 8), (8, 1)), ((4, 4), (4, 2)))
    param_dict = train_network.parameter_layout_dict
    # validate opt_shard_group
    assert not param_dict["weight1"][5]
    assert param_dict["weight2"][5].startswith("4")


def test_auto_parallel_momentum_4():
    # hybrid parallel cases
    # devices are repeatedly used
    auto_parallel_compile_net("semi_auto_parallel", 32, ((4, 4), (4, 1)), ((4, 4), (4, 2)))


def test_AdamWeightDecay():
    """ test_AdamWeightDecay """
    context.set_auto_parallel_context(parallel_mode="data_parallel", device_num=2, enable_parallel_optimizer=True)
    inputs = Tensor(np.ones([32, 128]).astype(np.float32))
    label = Tensor(np.zeros([32, 768]).astype(np.float32))
    net = Net()
    net.set_train()
    loss = nn.SoftmaxCrossEntropyWithLogits()
    optimizer = AdamWeightDecay(net.trainable_params(), learning_rate=0.1)

    net_with_loss = WithLossCell(net, loss)
    train_network = TrainOneStepCell(net_with_loss, optimizer)
    _executor.compile(train_network, inputs, label)
    context.reset_auto_parallel_context()


def test_lamb_compile():
    """ test_Lamb_compile """
    context.set_auto_parallel_context(parallel_mode="data_parallel", device_num=2, enable_parallel_optimizer=True)
    inputs = Tensor(np.ones([32, 128]).astype(np.float32))
    label = Tensor(np.zeros([32, 768]).astype(np.float32))
    net = Net()
    net.set_train()
    loss = nn.SoftmaxCrossEntropyWithLogits()
    optimizer = Lamb(net.trainable_params(), learning_rate=0.1)

    net_with_loss = WithLossCell(net, loss)
    train_network = TrainOneStepCell(net_with_loss, optimizer)
    _executor.compile(train_network, inputs, label)
    context.reset_auto_parallel_context()


def test_lamb_split_fusion():
    """ test_Lamb_split_fusion """
    context.set_auto_parallel_context(parallel_mode="data_parallel", device_num=2, enable_parallel_optimizer=True,
                                      all_reduce_fusion_config=[2, 4, 6, 8])
    inputs = Tensor(np.ones([32, 128]).astype(np.float32))
    label = Tensor(np.zeros([32, 768]).astype(np.float32))
    net = Net()
    net.set_train()
    loss = nn.SoftmaxCrossEntropyWithLogits()
    optimizer = Lamb(net.trainable_params(), learning_rate=0.1)

    net_with_loss = WithLossCell(net, loss)
    train_network = TrainOneStepCell(net_with_loss, optimizer)
    _executor.compile(train_network, inputs, label)
    context.reset_auto_parallel_context()


def test_edge_case():
    """ test_edge_case """
    context.set_auto_parallel_context(enable_parallel_optimizer=True)
    net = Net()
    with pytest.raises(RuntimeError):
        context.set_auto_parallel_context(parallel_mode="stand_alone")
        Lamb(net.trainable_params(), learning_rate=0.1)
    with pytest.raises(RuntimeError):
        context.set_context(device_target="GPU")
        context.set_auto_parallel_context(parallel_mode="data_parallel")
        Lamb(net.trainable_params(), learning_rate=0.1)
    with pytest.raises(RuntimeError):
        context.set_context(device_target="Ascend")
        context.set_auto_parallel_context(parallel_mode="data_parallel")
        Adam(net.trainable_params(), learning_rate=0.1)
    with pytest.raises(RuntimeError):
        context.set_auto_parallel_context(device_num=16)
        Lamb(net.trainable_params(), learning_rate=0.1)
    context.reset_auto_parallel_context()
