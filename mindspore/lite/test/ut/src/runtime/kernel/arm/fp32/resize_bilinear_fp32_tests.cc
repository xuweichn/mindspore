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
#include <iostream>
#include <vector>
#include "common/common_test.h"
#include "mindspore/lite/src/runtime/kernel/arm/nnacl/fp32/resize.h"

namespace mindspore {

class TestResizeBilinearFp32 : public mindspore::CommonTest {
 public:
  TestResizeBilinearFp32() = default;

 public:
  int tid = 0;
  int thread_num = 1;
  float err_tol = 1e-5;
};

// 1*1 -> 1*1
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest1) {
  std::vector<float> input = {1.0};
  std::vector<int> input_shape = {1, 1, 1, 1};
  std::vector<int> output_shape = {1, 1, 1, 1};
  std::vector<float> expect = {1.0};
  bool align_corners = false;

  auto output_size = 1;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 1*1
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest2) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 1, 1, 1};
  std::vector<float> expect = {0.0};
  bool align_corners = false;

  int output_size = 1;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 1*2
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest3) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 1, 2, 1};
  std::vector<float> expect = {0.0, 1.0};
  bool align_corners = false;

  auto output_size = 2;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 2*1
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest4) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 2, 1, 1};
  std::vector<float> expect = {0.0, 2.0};
  bool align_corners = false;

  auto output_size = 2;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 2*2
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest5) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 2, 2, 1};
  std::vector<float> expect = {0.0, 1.0, 2.0, 3.0};
  bool align_corners = false;

  auto output_size = 4;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 1*4
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest6) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 1, 4, 1};
  std::vector<float> expect = {0.0, 0.5, 1.0, 1.0};
  bool align_corners = false;

  auto output_size = 4;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 4*1
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest7) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 4, 1, 1};
  std::vector<float> expect = {0.0, 1.0, 2.0, 2.0};
  bool align_corners = false;

  auto output_size = 4;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 2*4
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest8) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 2, 4, 1};
  std::vector<float> expect = {0.0, 0.5, 1.0, 1.0, 2.0, 2.5, 3.0, 3.0};
  bool align_corners = false;

  auto output_size = 8;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 4*2
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest9) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 4, 2, 1};
  std::vector<float> expect = {0.0, 1.0, 1.0, 2.0, 2.0, 3.0, 2.0, 3.0};
  bool align_corners = false;

  auto output_size = 8;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 3*3
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest10) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 3, 3, 1};
  std::vector<float> expect = {0.0, 0.6666667, 1.0, 1.3333334, 2.0, 2.3333335, 2.0, 2.6666667, 3.0};
  bool align_corners = false;

  auto output_size = 9;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2 -> 4*4
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest11) {
  std::vector<float> input = {0.0, 1.0, 2.0, 3.0};
  std::vector<int> input_shape = {1, 2, 2, 1};
  std::vector<int> output_shape = {1, 4, 4, 1};
  std::vector<float> expect = {0.0, 0.5, 1.0, 1.0, 1.0, 1.5, 2.0, 2.0, 2.0, 2.5, 3.0, 3.0, 2.0, 2.5, 3.0, 3.0};
  bool align_corners = false;

  auto output_size = 16;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2*2*5 -> 2*4*4*5
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest12) {
  std::vector<float> input = {0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0, 13.0,
                              14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0,
                              28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  std::vector<int> input_shape = {2, 2, 2, 5};
  std::vector<int> output_shape = {2, 4, 4, 5};
  std::vector<float> expect = {
    0.0,  1.0,  2.0,  3.0,  4.0,  2.5,  3.5,  4.5,  5.5,  6.5,  5.0,  6.0,  7.0,  8.0,  9.0,  5.0,  6.0,  7.0,
    8.0,  9.0,  5.0,  6.0,  7.0,  8.0,  9.0,  7.5,  8.5,  9.5,  10.5, 11.5, 10.0, 11.0, 12.0, 13.0, 14.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0, 17.0, 18.0,
    19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0,
    17.0, 18.0, 19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 22.5, 23.5, 24.5, 25.5, 26.5,
    25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 27.5, 28.5, 29.5,
    30.5, 31.5, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 32.5,
    33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0, 30.0, 31.0, 32.0, 33.0,
    34.0, 32.5, 33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  bool align_corners = false;

  auto output_size = 160;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2*2*5 -> 2*4*4*5 align corners
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest13) {
  std::vector<float> input = {0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0, 13.0,
                              14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0,
                              28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  std::vector<int> input_shape = {2, 2, 2, 5};
  std::vector<int> output_shape = {2, 4, 4, 5};
  std::vector<float> expect = {
    0.0,       1.0,       2.0,       3.0,       4.0,       1.6666667, 2.6666667, 3.6666667, 4.666667,  5.666667,
    3.3333335, 4.3333335, 5.3333335, 6.3333335, 7.3333335, 5.0,       6.0,       7.0,       8.0,       9.0,
    3.3333335, 4.3333335, 5.3333335, 6.3333335, 7.3333335, 5.0,       6.0,       7.0,       8.0,       9.0,
    6.666667,  7.666667,  8.666667,  9.666667,  10.666667, 8.333334,  9.333334,  10.333334, 11.333334, 12.333334,
    6.666667,  7.666667,  8.666667,  9.666667,  10.666667, 8.333334,  9.333334,  10.333334, 11.333334, 12.333334,
    10.0,      11.0,      12.0,      13.0,      14.0,      11.666667, 12.666667, 13.666667, 14.666667, 15.666667,
    10.0,      11.0,      12.0,      13.0,      14.0,      11.666667, 12.666667, 13.666667, 14.666667, 15.666667,
    13.333334, 14.333334, 15.333334, 16.333334, 17.333334, 15.0,      16.0,      17.0,      18.0,      19.0,
    20.0,      21.0,      22.0,      23.0,      24.0,      21.666666, 22.666666, 23.666666, 24.666666, 25.666666,
    23.333334, 24.333334, 25.333334, 26.333334, 27.333334, 25.0,      26.0,      27.0,      28.0,      29.0,
    23.333334, 24.333334, 25.333334, 26.333334, 27.333334, 25.0,      26.0,      27.0,      28.0,      29.0,
    26.666666, 27.666666, 28.666666, 29.666666, 30.666666, 28.333334, 29.333334, 30.333334, 31.333334, 32.333332,
    26.666668, 27.666668, 28.666668, 29.666668, 30.666668, 28.333332, 29.333334, 30.333334, 31.333334, 32.333336,
    30.0,      31.0,      32.0,      33.0,      34.0,      31.666668, 32.666668, 33.666668, 34.666668, 35.666668,
    30.0,      31.0,      32.0,      33.0,      34.0,      31.666666, 32.666668, 33.666668, 34.666668, 35.666668,
    33.333332, 34.333332, 35.333332, 36.333332, 37.333332, 35.0,      36.0,      37.0,      38.0,      39.0};
  bool align_corners = true;

  auto output_size = 160;
  std::vector<float> output(output_size, 0.0);

  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2*2*5 -> 2*4*4*5 thread_num 2
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest14) {
  std::vector<float> input = {0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0, 13.0,
                              14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0,
                              28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  std::vector<int> input_shape = {2, 2, 2, 5};
  std::vector<int> output_shape = {2, 4, 4, 5};
  std::vector<float> expect = {
    0.0,  1.0,  2.0,  3.0,  4.0,  2.5,  3.5,  4.5,  5.5,  6.5,  5.0,  6.0,  7.0,  8.0,  9.0,  5.0,  6.0,  7.0,
    8.0,  9.0,  5.0,  6.0,  7.0,  8.0,  9.0,  7.5,  8.5,  9.5,  10.5, 11.5, 10.0, 11.0, 12.0, 13.0, 14.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0, 17.0, 18.0,
    19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0,
    17.0, 18.0, 19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 22.5, 23.5, 24.5, 25.5, 26.5,
    25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 27.5, 28.5, 29.5,
    30.5, 31.5, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 32.5,
    33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0, 30.0, 31.0, 32.0, 33.0,
    34.0, 32.5, 33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  bool align_corners = false;

  auto output_size = 160;
  std::vector<float> output(output_size, 0.0);
  thread_num = 2;
  tid = 0;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  tid = 1;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}

// 2*2*2*5 -> 2*4*4*5 thread_num 4
TEST_F(TestResizeBilinearFp32, ResizeBilinearTest15) {
  std::vector<float> input = {0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0, 13.0,
                              14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0,
                              28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  std::vector<int> input_shape = {2, 2, 2, 5};
  std::vector<int> output_shape = {2, 4, 4, 5};
  std::vector<float> expect = {
    0.0,  1.0,  2.0,  3.0,  4.0,  2.5,  3.5,  4.5,  5.5,  6.5,  5.0,  6.0,  7.0,  8.0,  9.0,  5.0,  6.0,  7.0,
    8.0,  9.0,  5.0,  6.0,  7.0,  8.0,  9.0,  7.5,  8.5,  9.5,  10.5, 11.5, 10.0, 11.0, 12.0, 13.0, 14.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0, 17.0, 18.0,
    19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 10.0, 11.0, 12.0, 13.0, 14.0, 12.5, 13.5, 14.5, 15.5, 16.5, 15.0, 16.0,
    17.0, 18.0, 19.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 22.5, 23.5, 24.5, 25.5, 26.5,
    25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 25.0, 26.0, 27.0, 28.0, 29.0, 27.5, 28.5, 29.5,
    30.5, 31.5, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 30.0, 31.0, 32.0, 33.0, 34.0, 32.5,
    33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0, 30.0, 31.0, 32.0, 33.0,
    34.0, 32.5, 33.5, 34.5, 35.5, 36.5, 35.0, 36.0, 37.0, 38.0, 39.0, 35.0, 36.0, 37.0, 38.0, 39.0};
  bool align_corners = false;

  auto output_size = 160;
  std::vector<float> output(output_size, 0.0);
  thread_num = 4;
  tid = 0;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  tid = 1;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  tid = 2;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  tid = 3;
  ResizeBilinear(input.data(), output.data(), input_shape.data(), output_shape.data(), align_corners, tid,
                 thread_num);
  CompareOutputData(output.data(), expect.data(), output_size, err_tol);
}
}  // namespace mindspore
