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

void addVectorMultipleDims() {
    int dims2 = 1024*32;
    int vectors = 12000;
    float* output = new float[dims2]{0};
    float* outputGpu = new float[dims2];
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
    // for (int i = 0; i < 20; i++) {
        DataBinding::launchKernel(addMultiDim, dim3(32), dim3(1024), vectors);
    // }
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
    int count = 0;
    for (int i = 0; i < dims2; i++) {
        if (abs(output[i] - outputGpu[i]) > 1e-5) {
            correct = false;
            cout << "Mismatch at index " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
            // break;
        }
        count++;
        if (count >= 100) break;
    }
    if (correct) {
        cout << "Outputs match!" << endl;
    } else {
        cout << "Outputs do not match!" << endl;
    }
    delete[] output;   
    delete[] outputGpu;
    delete[] input;
}

void dotProductVector() {
    int dims = 10240*10240;
    int totalThreads = 8092;
    int threads = 2048;
    // int vectors = 2;
    float output = 0;
    float* outputGpu = new float[threads];
    float* input = new float[dims];
    float* input2 = new float[dims];
    int inSize[2] = {dims ,dims};
    int outSize[1] = {threads};
    size_t freeMem, totalMem;
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    DataBinding::initData(
        2, 1,
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
    for (int i = 0; i < dims; i++) {
        input[i] = dist(gen);
        input2[i] = dist(gen);
    }
    DataBinding::setInput(0, input);
    cout << "Starting vector addition on GPU..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // for (int i = 0; i < 20; i++) {
        DataBinding::launchKernel(addMultiDim, dim3(totalThreads/threads), dim3(threads), dims);
    // }
    DataBinding::getOutput(0, outputGpu);
    auto end   = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    cout << "Starting vector addition on CPU..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < dims; i++) {
        // for(int j = 0; j < vectors; j++)  {
            output += input[i] * input2[i];
        // }
    }
    auto end_cpu   = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    cout << "compare outputs: ";
    bool correct = true;
    int count = 0;
    float retGpu = 0; 
    for (int i = 0; i< totalThreads ; i ++ ){
        retGpu += outputGpu[i];
    }
    // for (int i = 0; i < dims; i++) {
        if (abs(output - retGpu) > 1e-5) {
            correct = false;
            cout << "Mismatch at" <<" CPU = " << output << ", GPU = " <<retGpu << endl;
            // break;
        }
        // count++;
        // if (count >= 100) break;
    // }
    if (correct) {
        cout << "Outputs match!" << endl;
    } else {
        cout << "Outputs do not match!" << endl;
    }
    DataBinding::clearData();
    // delete[] output;   
    delete[] outputGpu;
    delete[] input;
    delete[] input2;
}


void scaleVectorWithConstants() {
    int dims = 10240;
    int vectors = 8000;
    float constants = 2;
    int totalThreads = 8092;
    int threads = 256;
    int size = dims * vectors; 
    float* outputGpu = new float[size];
    float* output = new float[size];
    float* input = new float[size];
    float* scaleMat = new float[1];
    int inSize[2] = {size ,1};
    int outSize[1] = {size};
    size_t freeMem, totalMem;
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    DataBinding::initData(
        2, 1,
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
    for (int i = 0; i < size; i++) {
        input[i] = dist(gen);
    }
    scaleMat[0] = constants;
    DataBinding::setInput(0, input);
    DataBinding::setInput(1, scaleMat);
    cout << "Starting vector addition on GPU..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // for (int i = 0; i < 20; i++) {
        DataBinding::launchKernel(scaleVec, dim3(totalThreads/threads), dim3(threads), size);
    // }
    DataBinding::getOutput(0, outputGpu);
    auto end   = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    cout << "Starting vector addition on CPU..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; i++) {
        // for(int j = 0; j < vectors; j++)  {
            output[i] = input[i] * scaleMat[0];
        // }
    }
    auto end_cpu   = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    cout << "compare outputs: ";
    bool correct = true;
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (abs(output[i] - outputGpu[i]) > 1e-5) {
            correct = false;
            cout << "Mismatch at index " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
//             break;
            break;
        }
        // if(i<100){
        //     cout << "tesst output " << i << ": CPU = " << output[i] << ", GPU = " << outputGpu[i] << endl;
        // }
        // count++;
        // if (count >= 100) break;
    }
    if (correct) {
        cout << "Outputs match!" << endl;
    } else {
        cout << "Outputs do not match!" << endl;
    }
    DataBinding::clearData();
    // delete[] output;   
    delete[] outputGpu;
    delete[] input;
    delete[] output;
    delete[] scaleMat;
}

void minLengthVector() {
    // preset
    int dims = 200 << 5;
    int vectors = 8092 << 1;
    int totalThreads = vectors;
    int threadsPerBlock = 1024;
    int blocks = (totalThreads + threadsPerBlock - 1) / threadsPerBlock;
    int typeSize = sizeof(float);
    int size = dims * vectors; 
    float* input = new float[size];
    float* outputGpu = new float[1];
    outputGpu[0] = FLT_MAX;
    float* output = new float[vectors] {0};
    int inSize[1] = {size};
    int outSize[1] = {1};
    size_t freeMem, totalMem;
    void* args[32];
    int index = 0;
    args[index++] = &dims;
    args[index++] = &vectors;
    // check GPU info and reserve data
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    DataBinding::initData(
        1, 1,
        inSize,
        outSize,
        typeSize
    );
    cudaMemGetInfo(&freeMem, &totalMem);
    cout << "Free VRAM: " << freeMem / (1024*1024) << " MB\n";
    cout << "Total VRAM: " << totalMem / (1024*1024) << " MB\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-5.0f, 5.0f);
    for (int i = 0; i < size; i++) {
        input[i] = dist(gen);
    }
    cout<< endl;
    DataBinding::setInput(0, input);
    DataBinding::setOutput(0, outputGpu);
    cout << "Starting vector addition on GPU..." << std::endl;
    
    ///////////////////////////////////
    // start GPU acceleration        //
    ///////////////////////////////////

    auto start = std::chrono::high_resolution_clock::now();
    // for (int i = 0; i < 20; i++) {
    DataBinding::launchKernel2(minDistanceVector, dim3(totalThreads/threadsPerBlock), dim3(threadsPerBlock), threadsPerBlock * sizeof(float), args, index);
    // }
    DataBinding::getOutput(0, outputGpu);
    auto end   = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "End vector addition on GPU... " << ms << " ms" << std::endl;
    cout << "Starting vector addition on CPU..." << std::endl;
    ///////////////////////////////////
    // start CPU processing          //
    ///////////////////////////////////
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < vectors; i++) {
        int offset = i * dims;
        for(int j = 0; j < dims; j++)  {
            output[i] += input[offset + j] * input[offset + j];
        }
    }
    float minCpu = FLT_MAX;
    int count = 20;
    for (int i = 0; i < vectors; i++) {

        minCpu = min(minCpu, output[i]);      
    }
    cout<< "min: " << minCpu << endl;
    auto end_cpu   = std::chrono::high_resolution_clock::now();
    double ms_cpu = std::chrono::duration<double, std::milli>(end_cpu - start).count();
    cout << "End vector addition on CPU... " << ms_cpu << " ms" << std::endl;
    cout << "compare outputs: ";
    bool correct = true;

    if (abs(minCpu - outputGpu[0]) > 1e-3) {
        correct = false;
        cout << "Mismatch " << ": CPU = " << minCpu << ", GPU = " << outputGpu[0] << endl;
    }
    cout << "outputs " << ": CPU = " << minCpu << ", GPU = " << outputGpu[0] << endl;
    if (correct) {
        cout << "✅ Outputs match!" << endl;
    } else {
        cout << "❌ Outputs do not match!" << endl;
    }
    DataBinding::clearData();
    delete[] output;   
    delete[] outputGpu;
    delete[] input;
}

}