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

#ifndef LITE_MICRO_CODER_OPCODERS_SERIALIZERS_NNACL_STREAM_UTILS_H_
#define LITE_MICRO_CODER_OPCODERS_SERIALIZERS_NNACL_STREAM_UTILS_H_
#include <sstream>
#include <string>
#include "nnacl/pooling_parameter.h"
#include "nnacl/softmax_parameter.h"
#include "nnacl/int8/quantize.h"

namespace mindspore::lite::micro {

inline std::ostream &operator<<(std::ostream &code, const ::QuantArg &quant_arg) {
  code << "{" << static_cast<float>(quant_arg.scale_) << ", " << quant_arg.zp_ << "}";
  return code;
}

inline std::ostream &operator<<(std::ostream &code, const OpParameter &tile) {
  code << "{ \"\""
       << ", " << tile.type_ << ", " << tile.thread_num_ << "}";
  return code;
}

inline std::ostream &operator<<(std::ostream &code, PoolMode pool_mode) {
  code << "(PoolMode)"
       << "(" << static_cast<int>(pool_mode) << ")";
  return code;
}

inline std::ostream &operator<<(std::ostream &code, RoundMode round_mode) {
  code << "(RoundMode)"
       << "(" << static_cast<int>(round_mode) << ")";
  return code;
}

inline std::ostream &operator<<(std::ostream &code, ActType act_type) {
  code << "(ActType)"
       << "(" << static_cast<int>(act_type) << ")";
  return code;
}

inline std::ostream &operator<<(std::ostream &code, DataOrder data_order) {
  if (data_order == RowMajor) {
    code << "RowMajor";
  } else {
    code << "ColMajor";
  }
  return code;
}
}  // namespace mindspore::lite::micro
#endif  // LITE_MICRO_CODER_OPCODERS_SERIALIZERS_NNACL_STREAM_UTILS_H_
