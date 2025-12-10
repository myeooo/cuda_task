#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
void dotProductVector(float* c, const float* a, const float* b, int N);
#ifdef __cplusplus
}
#endif
