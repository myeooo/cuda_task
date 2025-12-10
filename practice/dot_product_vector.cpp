#include "dot_product_vector.h"
#include <iostream>
#include "cuda/dot_product_vector.cuh"

#include <chrono>
using namespace std;
void dotProductVector() {
    

    // auto end   = std::chrono::high_resolution_clock::now();
    // double ms = std::chrono::duration<double, std::milli>(end - start).count();
    // cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    // cout << "Starting vector addition on CPU..." << std::endl;
    // start = std::chrono::high_resolution_clock::now();

    // for (int i = 0; i < vectors; i++) {
    //     for (int j = 0; j < dims; j++) {
    //         test2.output[j] += test2.input[i * dims + j];
    //     }
    // }
    // auto end_cpu   = std::chrono::high_resolution_clock::now();
    // double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    // cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    // std::cout << "[";
    // for (int i = 0; i < dims; i++) {
    //     std::cout << test.output[i] << ", ";
    // }
    // std::cout << "]" << std::endl;
    // std::cout << "---------CPU RESULT--------" << std::endl;
    // std::cout << "[";
    // for (int i = 0; i < dims; i++) {
    //     std::cout << test2.output[i] << ", ";
    // }
    // std::cout << "]" << std::endl;

}