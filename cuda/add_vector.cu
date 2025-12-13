#include "add_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void addVectorCu(float* c, const float* a, const float* b, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i< N){
        c[i] = a[i] + b[i];
    }
}

__global__ void addMultiDim(float* out, const float* in, int numberOfVectors) {
    int dims = blockDim.x * gridDim.x;
    int idx = (blockIdx.x * blockDim.x + threadIdx.x);
    for(int i = 0; i < numberOfVectors; i++){
        out[idx] += in[i * dims + idx];
    }
}

__global__ void addVectorCu2(float* c, const float* a, const float* b, int N) {
    int i = threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    while(i < N){
        c[i] = a[i] + b[i];
        i += stride;
    }
}