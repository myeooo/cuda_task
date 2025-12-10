#include "add_vector.h"
#include <iostream>
#include "cuda/add_vector.cuh"

#include <chrono>
using namespace std;
void addVector() {
    const int dims = 1024;
    const int vectors = 400000;
    VectorAddTest test(dims, vectors);
    VectorAddTest test2(dims, vectors);
    memcpy(test2.input.data(), test.input.data(), sizeof(float) * dims * vectors);
    cout << "Starting vector addition on GPU..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    addVectorMultiDimKernel(test.output.data(), test.input.data(), vectors, dims);
    auto end   = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    cout << "Starting vector addition on CPU..." << std::endl;
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < vectors; i++) {
        for (int j = 0; j < dims; j++) {
            test2.output[j] += test2.input[i * dims + j];
        }
    }
    auto end_cpu   = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    std::cout << "[";
    for (int i = 0; i < dims; i++) {
        std::cout << test.output[i] << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "---------CPU RESULT--------" << std::endl;
    std::cout << "[";
    for (int i = 0; i < dims; i++) {
        std::cout << test2.output[i] << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}