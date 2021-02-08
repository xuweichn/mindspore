/**
 * Copyright 2021 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "micro/coder/opcoders/serializers/nnacl_serializer/nnacl_fp32_serializer.h"
#include "src/common/log_adapter.h"
#include "micro/coder/log.h"
#include "nnacl/pooling_parameter.h"

namespace mindspore::lite::micro::nnacl {

void NNaclFp32Serializer::CodeStruct(const std::string &name, const PoolingParameter &pooling_parameter) {
  CodeBaseStruct("PoolingParameter", name, pooling_parameter.op_parameter_, pooling_parameter.pool_mode_,
                 pooling_parameter.round_mode_, pooling_parameter.act_type_, pooling_parameter.avg_mode_,
                 pooling_parameter.global_, pooling_parameter.window_w_, pooling_parameter.window_h_,
                 pooling_parameter.stride_w_, pooling_parameter.stride_h_, pooling_parameter.input_w_,
                 pooling_parameter.input_w_, pooling_parameter.input_batch_, pooling_parameter.input_channel_,
                 pooling_parameter.output_w_, pooling_parameter.output_h_, pooling_parameter.output_batch_,
                 pooling_parameter.output_channel_, pooling_parameter.pad_u_, pooling_parameter.pad_d_,
                 pooling_parameter.pad_l_, pooling_parameter.pad_r_, pooling_parameter.thread_num_, "NULL",
                 pooling_parameter.quantize_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const BatchNormParameter &batch_norm_parameter) {
  CodeBaseStruct("BatchNormParameter", name, batch_norm_parameter.op_parameter_, batch_norm_parameter.epsilon_,
                 batch_norm_parameter.momentum_, batch_norm_parameter.unit_, batch_norm_parameter.units_,
                 batch_norm_parameter.channel_, batch_norm_parameter.fused_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const ArithmeticParameter &arithmetic_parameter) {
  CodeBaseStruct("ArithmeticParameter", name, arithmetic_parameter.op_parameter_, arithmetic_parameter.broadcasting_,
                 arithmetic_parameter.ndim_, arithmetic_parameter.activation_type_,
                 ToString(arithmetic_parameter.in_shape0_), arithmetic_parameter.in_elements_num0_,
                 ToString(arithmetic_parameter.in_shape1_), arithmetic_parameter.in_elements_num1_,
                 ToString(arithmetic_parameter.out_shape_), arithmetic_parameter.out_elements_num_,
                 ToString(arithmetic_parameter.in_strides0_), ToString(arithmetic_parameter.in_strides1_),
                 ToString(arithmetic_parameter.out_strides_), ToString(arithmetic_parameter.multiples0_),
                 ToString(arithmetic_parameter.multiples1_));
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const SoftmaxParameter &softmax_parameter) {
  CodeBaseStruct("SoftmaxParameter", name, softmax_parameter.op_parameter_, softmax_parameter.axis_,
                 ToString(softmax_parameter.input_shape_), softmax_parameter.element_size_, softmax_parameter.n_dim_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const ConvParameter &conv_parameter) {
  CodeBaseStruct("ConvParameter", name, conv_parameter.op_parameter_, "{NULL}", conv_parameter.kernel_h_,
                 conv_parameter.kernel_w_, conv_parameter.stride_h_, conv_parameter.stride_w_,
                 conv_parameter.dilation_h_, conv_parameter.dilation_w_, conv_parameter.pad_u_, conv_parameter.pad_d_,
                 conv_parameter.pad_l_, conv_parameter.pad_r_, conv_parameter.group_, conv_parameter.tile_num_,
                 conv_parameter.input_batch_, conv_parameter.input_h_, conv_parameter.input_w_,
                 conv_parameter.input_channel_, conv_parameter.output_batch_, conv_parameter.output_h_,
                 conv_parameter.output_w_, conv_parameter.output_channel_, conv_parameter.op_parameter_.thread_num_,
                 conv_parameter.input_unit_, conv_parameter.output_unit_, conv_parameter.act_type_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const ScaleParameter &scale_parameter) {
  CodeBaseStruct("ScaleParameter", name, scale_parameter.op_parameter_, scale_parameter.outer_size_,
                 scale_parameter.axis_size_, scale_parameter.inner_size_, scale_parameter.axis_,
                 scale_parameter.const_scale_, scale_parameter.const_offset_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const SliceParameter &slice_parameter) {
  CodeBaseStruct("SliceParameter", name, slice_parameter.op_parameter_, ToString(slice_parameter.shape_),
                 ToString(slice_parameter.begin_), ToString(slice_parameter.end_), ToString(slice_parameter.size_),
                 "{0}", slice_parameter.param_length_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const TileParameter &tile_parameter) {
  CodeBaseStruct("TileParameter", name, tile_parameter.op_parameter_, ToString(tile_parameter.multiples_),
                 ToString(tile_parameter.in_shape_), ToString(tile_parameter.out_shape_),
                 ToString(tile_parameter.in_strides_), ToString(tile_parameter.out_strides_), tile_parameter.in_dim_);
}

void NNaclFp32Serializer::CodeStruct(const std::string &name, const TransposeParameter &transpose_parameter) {
  CodeBaseStruct("TransposeParameter", name, transpose_parameter.op_parameter_, ToString(transpose_parameter.perm_),
                 transpose_parameter.conjugate_, ToString(transpose_parameter.strides_),
                 ToString(transpose_parameter.out_strides_), transpose_parameter.num_axes_,
                 transpose_parameter.data_size_);
}

}  // namespace mindspore::lite::micro::nnacl