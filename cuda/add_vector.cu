#include "add_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>
#include <float.h>
__device__ float atomicMinFloat(float* addr, float value) {
    int* addr_i = (int*)addr;
    int old = *addr_i, assumed;
    do {
        assumed = old;
        old = atomicCAS(
            addr_i,
            assumed,
            __float_as_int(fminf(value, __int_as_float(assumed)))
        );
    } while (assumed != old);
    return __int_as_float(old);
}

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

__global__ void scaleVec(float* out, const float* in, const float* scale, int size) {
    int stride = blockDim.x * gridDim.x;
    int idx = (blockIdx.x * blockDim.x + threadIdx.x);
    while (idx < size){
        out[idx] = in[idx] * scale[0];
        idx+=stride;
    }

    
}

__global__ void minDistanceVector(
    float* out,
    const float* in,
    int dims,
    int vectors
) {
    extern __shared__ float sdata[];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + tid;

    float val = FLT_MAX;

    // ✅ không return, chỉ gán giá trị an toàn
    if (idx < vectors) {
        int offset = idx * dims;
        float sum = 0.0f;
        for (int i = 0; i < dims; i++) {
            float x = in[offset + i];
            sum += x * x;
        }
        val = sum;
    }

    sdata[tid] = val;
    __syncthreads();

    // block reduction (min)
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            sdata[tid] = fminf(sdata[tid], sdata[tid + stride]);
        }
        __syncthreads();
    }

    // global reduction
    if (tid == 0) {
        atomicMinFloat(&out[0], sdata[0]);
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

