/**
 * Copyright 2020 Huawei Technologies Co., Ltd
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
#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_FLATTEN_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_FLATTEN_H_

#include <vector>
#include "src/lite_kernel.h"
#include "ir/anf.h"
#include "include/context.h"
#include "src/runtime/kernel/arm/nnacl/flatten.h"

using mindspore::lite::Context;

namespace mindspore::kernel {
class FlattenCPUKernel : public LiteKernel {
 public:
  FlattenCPUKernel(OpParameter *parameter, const std::vector<lite::tensor::Tensor *> &inputs,
                   const std::vector<lite::tensor::Tensor *> &outputs, const lite::Context *ctx,
                   const lite::Primitive *primitive)
      : LiteKernel(parameter, inputs, outputs, ctx, primitive) {
    flatten_param_ = reinterpret_cast<FlattenParameter *>(parameter);
  }
  ~FlattenCPUKernel() override = default;

  int Init() override;
  int ReSize() override;
  int Run() override;

 private:
  FlattenParameter *flatten_param_;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_FLATTEN_H_
