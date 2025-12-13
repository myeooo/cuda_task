#include "vector_processing.h"
#include <iostream>
#include <random>

#include <chrono>
using namespace std;
const int dims = 1;
float vector1[dims];
float vector2[dims];

namespace VectorAlgorithm{
// void addVector() {

//     int inSize[2] = {dims, dims};
//     int outSize[1] = {dims};

//     DataBinding::initData(
//         2, 1,
//         inSize,
//         outSize,
//         sizeof(float)
//     );
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<float> dist(1.0f, 12.0f);
//     for (int i = 0; i < dims; i++) {
//         vector1[i] = dist(gen);
//         vector2[i] = dist(gen);
//     }
//     DataBinding::setInput(0, vector1);
//     DataBinding::setInput(1, vector2);
//     cout << "Starting vector addition on GPU..." << std::endl;
//     auto start = std::chrono::high_resolution_clock::now();

//     DataBinding::launchKernel(addVectorCu, dim3((dims + 255) / 256), dim3(256), dims);
//     DataBinding::getOutput(0, outputGpu);
//     auto end   = std::chrono::high_resolution_clock::now();
//     double ms = std::chrono::duration<double, std::milli>(end - start).count();
//     cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
//     cout << "Starting vector addition on CPU..." << std::endl;
//     start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < dims; i++) {
//         output[i] = vector1[i] + vector2[i];
//     }
//     auto end_cpu   = std::chrono::high_resolution_clock::now();
//     double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
//     cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
//     cout << "compare outputs: ";
//     bool correct = true;
//     for (int i = 0; i < dims; i++) {
//         if (abs(output[i] - outputGpu[i]) > 1e-5) {
//             correct = false;
//             cout << "Mismatch at index " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
//             break;
//         }
//     }
//     if (correct) {
//         cout << "Outputs match!" << endl;
//     } else {
//         cout << "Outputs do not match!" << endl;
//     }

// }

// void addVector2() {

//     int inSize[2] = {dims, dims};
//     int outSize[1] = {dims};


//     DataBinding::initData(
//         2, 1,
//         inSize,
//         outSize,
//         sizeof(float)
//     );
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<float> dist(1.0f, 12.0f);
//     for (int i = 0; i < dims; i++) {
//         vector1[i] = dist(gen);
//         vector2[i] = dist(gen);
//     }
//     DataBinding::setInput(0, vector1);
//     DataBinding::setInput(1, vector2);
//     cout << "Starting vector addition on GPU..." << std::endl;
//     auto start = std::chrono::high_resolution_clock::now();

//     DataBinding::launchKernel(addVectorCu2, dim3(32), dim3(1024/32), dims);
//     auto end   = std::chrono::high_resolution_clock::now();
//     double ms = std::chrono::duration<double, std::milli>(end - start).count();
//     cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
//     DataBinding::getOutput(0, outputGpu);
//     cout << "Starting vector addition on CPU..." << std::endl;
//     start = std::chrono::high_resolution_clock::now();
    
//     for (int i = 0; i < dims; i++) {
//         output[i] = vector1[i] + vector2[i];
//     }
//     auto end_cpu   = std::chrono::high_resolution_clock::now();
//     double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
//     cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
//     cout << "compare outputs: ";
//     bool correct = true;
//     for (int i = 0; i < dims; i++) {
//         if (abs(output[i] - outputGpu[i]) > 1e-5) {
//             correct = false;
//             cout << "Mismatch at index " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
//             break;
//         }
//     }
//     if (correct) {
//         cout << "Outputs match!" << endl;
//     } else {
//         cout << "Outputs do not match!" << endl;
//     }

// }

const int dims2 = 1024*32;
int vectors = 2;
float output[dims2] = {0};
float outputGpu[dims2] = {0};
void addVectorMultipleDims() {
    float* input = new float[dims2 * vectors];
    int inSize[1] = {dims2 * vectors};
    int outSize[1] = {dims2};
    size_t freeMem, totalMem;
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    DataBinding::initData(
        1, 1,
        inSize,
        outSize,
        sizeof(float)
    );
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-12.0f, 12.0f);
    for (int i = 0; i < dims2 * vectors; i++) {
        input[i] = dist(gen);
    }
    DataBinding::setInput(0, input);
    cout << "Starting vector addition on GPU..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 20; i++) {
        DataBinding::launchKernel(addMultiDim, dim3(32), dim3(1024), vectors);
    }
    DataBinding::getOutput(0, outputGpu);
    auto end   = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    cout << "Starting vector addition on CPU..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < dims2; i++) {
        for(int j = 0; j < vectors; j++)  {
            output[i] += input[j * dims2 + i];
        }
    }
    auto end_cpu   = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    cout << "compare outputs: ";
    bool correct = true;
    for (int i = 0; i < dims; i++) {
        if (abs(output[i] - outputGpu[i]) > 1e-5) {
            correct = false;
            cout << "Mismatch at index " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
            break;
        }
    }
    if (correct) {
        cout << "Outputs match!" << endl;
    } else {
        cout << "Outputs do not match!" << endl;
    }

}

}