#include "vector_processing.h"
#include <iostream>

#include <chrono>
using namespace std;
namespace VectorAlgorithm{
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
    
}

void dotProductVectors() {
    const int dims = 1024;

    float vector1[dims];
    float vector2[dims];
    float output[dims];

    // ---- Random vector 1 & 2 từ 1 → 12 ----
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 12);

    for (int i = 0; i < dims; i++) {
        vector1[i] = dist(gen);
        vector2[i] = dist(gen);
    }

    cout << "Starting dot product on GPU..." << endl;

    // ---- GPU timing ----
    auto start_gpu = std::chrono::high_resolution_clock::now();

    float ret = dotProductVector(output, vector1, vector2, dims);
    auto end_gpu = std::chrono::high_resolution_clock::now();
    double ms_gpu = std::chrono::duration<double, std::milli>(end_gpu - start_gpu).count();
    float sumGpu = ret;

    cout << "End dot product on GPU... " << ms_gpu << " ms" << endl;


    // ---- CPU dot product ----
    cout << "Starting dot product on CPU..." << endl;

    auto start_cpu = std::chrono::high_resolution_clock::now();

    float sum = 0;
    for (int i = 0; i < dims; i++) {
        sum += vector1[i] * vector2[i];
    }

    auto end_cpu = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start_cpu).count();

    cout << "End dot product on CPU... " << ms_cpu << " ms" << endl;

    // In kết quả
    cout << "CPU result = " << sum << endl;

    cout << "GPU sample outputs: ";
    cout << "GPU result = " << sumGpu << endl;
    cout << "..." << endl;
}

}