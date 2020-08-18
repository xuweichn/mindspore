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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_EXPANDDIMS_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_EXPANDDIMS_H_

#include <vector>
#include "src/lite_kernel.h"
#include "src/runtime/kernel/arm/nnacl/fp32/expandDims.h"
#include "schema/model_generated.h"

#include "include/context.h"

using mindspore::lite::Context;

namespace mindspore::kernel {
class ExpandDimsCPUKernel : public LiteKernel {
 public:
  ExpandDimsCPUKernel(OpParameter *parameter, const std::vector<lite::tensor::Tensor *> &inputs,
                      const std::vector<lite::tensor::Tensor *> &outputs, const lite::Context *ctx,
                      const mindspore::lite::PrimitiveC *primitive)
      : LiteKernel(parameter, inputs, outputs, ctx, primitive), ctx_(ctx), thread_count_(ctx->thread_num_) {}
  ~ExpandDimsCPUKernel() override = default;

  int Init() override;
  int ReSize() override;
  int Run() override;
  int DoExpandDims(int task_id);

 private:
  int thread_count_;
  int thread_sz_count_;
  int thread_sz_stride_;
  size_t data_size_;
  float *in_ptr_;
  float *out_ptr_;
  const Context *ctx_;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_CCSRC_KERNEL_CPU_ARM_FP32_EXPANDDIMS_H_
