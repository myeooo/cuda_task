#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
void addVectorKernel(float* c, const float* a, const float* b, int N);
void addVectorMultiDimKernel(float* out, const float* input, int numberOfVectors, int dim);
#ifdef __cplusplus
}
#endif
