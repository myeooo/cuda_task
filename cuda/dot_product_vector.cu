#include "dot_product_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void dotProdVectorCu(float* out, const float* v1, const float* v2, int dims, int stride) {
    int th = threadIdx.x;
    out[th] = 0;
    int i = th;
    while (i < dims) {
        out[th] += v1[i] * v2[i];
        i += stride;
    }
}

float dotProductVector(float* c, const float* a, const float* b, int dims){
    int threads = 32;
    float retArr[32] = {0};
    float *vectorA,*vectorB, *d_out;
    size_t size_in = sizeof(float) * dims;
    size_t size_out = sizeof(float) * threads;
    cudaMalloc(&vectorA, size_in);
    cudaMalloc(&vectorB, size_in);
    cudaMalloc(&d_out, size_out);
    cudaMemcpy(vectorA, a, size_in, cudaMemcpyHostToDevice);
    cudaMemcpy(vectorB, b, size_in, cudaMemcpyHostToDevice);

    
    int blocks = 1;
    std::cout << "Blocks: " << blocks << ", Threads: " << threads << std::endl;
    dotProdVectorCu<<<blocks, threads>>>(d_out, vectorA, vectorB, dims, threads);
    cudaDeviceSynchronize();
    cudaMemcpy((void *)retArr, d_out, size_out, cudaMemcpyDeviceToHost);
    cudaFree(vectorA);
    cudaFree(vectorB);
    cudaFree(d_out);
    float sum = 0;
    for(int i = 0; i< threads; i++){
        sum += retArr[i];
    }
    return sum;
}

