#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
__global__ void dotProdVectorCu(float* out, const float* v1, const float* v2, int dims);
#ifdef __cplusplus
}
#endif
