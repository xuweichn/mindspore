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

#ifndef MINDSPORE_CORE_MINDRT_INCLUDE_LITEBUS_H
#define MINDSPORE_CORE_MINDRT_INCLUDE_LITEBUS_H

#ifdef __cplusplus
#include <string>

extern "C" {
#endif

#define LITEBUS_URL_MAX_LEN 138

struct LitebusConfig {
  char tcpUrl[LITEBUS_URL_MAX_LEN];
  char tcpUrlAdv[LITEBUS_URL_MAX_LEN];
  char udpUrl[LITEBUS_URL_MAX_LEN];
  char udpUrlAdv[LITEBUS_URL_MAX_LEN];
  int threadCount;
  int httpKmsgFlag;
};

int LitebusInitializeC(const struct LitebusConfig *config);

void LitebusFinalizeC();

#ifdef __cplusplus
}
#endif

#endif