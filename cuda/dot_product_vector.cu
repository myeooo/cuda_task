#include "dot_product_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void dotProdVectorCu(float* out, const float* v1, const float* v2, int dims) {
    int stride = blockDim.x * gridDim.x;
    int th = threadIdx.x;
    out[th] = 0;
    int i = th;
    while (i < dims) {
        out[th] += v1[i] * v2[i];
        i += stride;
    }
}


