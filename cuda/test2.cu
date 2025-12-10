#include "test2.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void subKernel(int* c, const int* a, const int* b) {
    int i = threadIdx.x;
    c[i] = a[i] - b[i];
}

void launchSubKernel(int* h_c, const int* h_a, const int* h_b)
{
    int *d_a, *d_b, *d_c;
    size_t size = sizeof(int);

    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    subKernel<<<1,1>>>(d_c, d_a, d_b);
    cudaDeviceSynchronize();

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}

void checkCudaBlockAndThread()
{
    int device = 0;
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, device);

    printf("Max threads per block: %d\n", prop.maxThreadsPerBlock);
    printf("Max block dimensions: (%d, %d, %d)\n",
        prop.maxThreadsDim[0],
        prop.maxThreadsDim[1],
        prop.maxThreadsDim[2]);

    printf("Max grid dimensions: (%d, %d, %d)\n",
        prop.maxGridSize[0],
        prop.maxGridSize[1],
        prop.maxGridSize[2]);
}
