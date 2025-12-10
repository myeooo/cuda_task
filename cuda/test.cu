#include "test.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void addKernel(int* c, const int* a, const int* b) {
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

void launchAddKernel(int* h_c, const int* h_a, const int* h_b)
{
    int *d_a, *d_b, *d_c;
    size_t size = sizeof(int);

    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    addKernel<<<1,1>>>(d_c, d_a, d_b);
    cudaDeviceSynchronize();

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
