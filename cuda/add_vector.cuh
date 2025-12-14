#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
__global__ void addVectorCu(float* c, const float* a, const float* b, int N);
__global__ void addVectorCu2(float* c, const float* a, const float* b, int N);
__global__ void scaleVec(float* out, const float* in,const float* scale, int size);
__global__ void addMultiDim(float* out, const float* in, int numberOfVectors);
__global__ void minDistanceVector(float* out, const float* in, int dims, int vectors);
#ifdef __cplusplus
}
#endif
