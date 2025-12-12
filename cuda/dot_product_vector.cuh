#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
float dotProductVector(float* c, const float* a, const float* b, int dims);
#ifdef __cplusplus
}
#endif
