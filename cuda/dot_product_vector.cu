#include "dot_product_vector.cuh"
#include <cuda_runtime.h>
#include <iostream>



void dotProductVector(float* c, const float* a, const float* b, int N){
    // float *d_input, *d_out;
    // size_t size_in = sizeof(float) * numberOfVectors * dim;
    // size_t size_out = sizeof(float) * dim;
    // cudaMalloc(&d_input, size_in);
    // cudaMalloc(&d_out, size_out);
    // cudaMemcpy(d_input, input, size_in, cudaMemcpyHostToDevice);

    // int threads = 1;
    // int blocks = dim;
    // std::cout << "Blocks: " << blocks << ", Threads: " << threads << std::endl;
    // addMultiDim<<<blocks,threads>>>(d_out, d_input, numberOfVectors, dim);
    // cudaDeviceSynchronize();
    // cudaMemcpy((void *)out, d_out, size_out, cudaMemcpyDeviceToHost);
    // cudaFree(d_input);
    // cudaFree(d_out);
}

