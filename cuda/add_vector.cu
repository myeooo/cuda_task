#include "add_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>

__global__ void addVectorCu(float* c, const float* a, const float* b, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i< N){
        c[i] = a[i] + b[i];
    }
}

__global__ void addMultiDim(float* out, const float* in, int numberOfVectors, int dim) {
    int idx = blockIdx.x;
    float sum = 0.0f;
    for(int i = 0; i < numberOfVectors; i++){
        sum += in[i * dim + idx];
    }
    out[idx] = sum;
}


void addVectorMultiDimKernel(float* out, const float* input, int numberOfVectors, int dim){
    float *d_input, *d_out;
    size_t size_in = sizeof(float) * numberOfVectors * dim;
    size_t size_out = sizeof(float) * dim;
    cudaMalloc(&d_input, size_in);
    cudaMalloc(&d_out, size_out);
    cudaMemcpy(d_input, input, size_in, cudaMemcpyHostToDevice);

    int threads = 1;
    int blocks = dim;
    std::cout << "Blocks: " << blocks << ", Threads: " << threads << std::endl;
    addMultiDim<<<blocks,threads>>>(d_out, d_input, numberOfVectors, dim);
    cudaDeviceSynchronize();
    cudaMemcpy((void *)out, d_out, size_out, cudaMemcpyDeviceToHost);
    cudaFree(d_input);
    cudaFree(d_out);
}

void addVectorKernel(float* h_c, const float* h_a, const float* h_b, int N)
{
    float *d_a, *d_b, *d_c;
    size_t size = sizeof(float) * N;

    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);
    int threads = 256;
    int blocks = (N + threads - 1) / threads;
    printf("Blocks: %d, Threads: %d\n", blocks, threads);
    addVectorCu<<<blocks,threads>>>(d_c, d_a, d_b, N);
    cudaDeviceSynchronize();

    cudaMemcpy((void *)h_c, d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
