#pragma once
#include <src/cuda/add_vector.cuh>
#include <iostream>
using namespace std;
namespace DataBinding {
extern void** dataInput_d;
extern void** dataOutput_d;

extern int numberOfInputArr_d;
extern int numberOfOutputArr_d;
extern int typeSize_d;

extern int* inputSize_d;
extern int* outputSize_d;

void initData(int numberOfInputArr, int numberOfOutputArr, int inputSize[], int outputSize[], int typeSize);
void clearData();
void setInput(int idx, const void* hostPtr);
void getOutput(int idx, void* hostPtr);
void setOutput(int idx, const void* hostPtr);
template<typename KernelFunc>
void launchKernel(KernelFunc kernel, dim3 grid, dim3 block, int size)
{
    if (numberOfOutputArr_d < 1) {
        std::cerr << "launchKernel: No output buffer!" << std::endl;
        return;
    }
    std::cout << "Launching kernel with grid (" << grid.x << ", " << grid.y << ", " << grid.z << ") "
         << "and block (" << block.x << ", " << block.y << ", " << block.z << ")" << std::endl;
    void* args[32];
    int index = 0;

    for (int i = 0; i < numberOfOutputArr_d; i++)
        args[index++] = &dataOutput_d[i];

    for (int i = 0; i < numberOfInputArr_d; i++)
        args[index++] = &dataInput_d[i];

    args[index++] = &size;

    cudaError_t err = cudaLaunchKernel(
        (void*)kernel,
        grid, block,
        args,
        0, nullptr
    );

    if (err != cudaSuccess) {
        std::cerr << "Kernel launch failed: "
                  << cudaGetErrorString(err) << std::endl;
    }

    cudaDeviceSynchronize();
}

template void launchKernel<void(*)(float*, float*, float*, int)>(
    void(*kernel)(float*, float*, float*, int),
    dim3, dim3, int
);


template<typename KernelFunc>
void launchKernel2(
    KernelFunc kernel,
    dim3 grid,
    dim3 block,
    size_t sharedMem,
    void** extraArgs,
    int numExtraArgs
) {
    if (numberOfOutputArr_d < 1) {
        std::cerr << "launchKernel2: No output buffer!" << std::endl;
        return;
    }
    std::cout << "Launching kernel with grid (" << grid.x << ", " << grid.y << ", " << grid.z << ") "
         << "and block (" << block.x << ", " << block.y << ", " << block.z << ")" << std::endl;
    void* args[32];
    int index = 0;

    // 1️⃣ output buffers (device pointers)
    for (int i = 0; i < numberOfOutputArr_d; i++)
        args[index++] = &dataOutput_d[i];

    // 2️⃣ input buffers (device pointers)
    for (int i = 0; i < numberOfInputArr_d; i++)
        args[index++] = &dataInput_d[i];

    // 3️⃣ scalar / extra arguments (HOST ADDRESSES)
    for (int i = 0; i < numExtraArgs; i++)
        args[index++] = extraArgs[i];

    cudaError_t err = cudaLaunchKernel(
        (void*)kernel,
        grid,
        block,
        args,
        sharedMem,
        nullptr
    );

    if (err != cudaSuccess) {
        std::cerr << "Kernel launch failed: "
                  << cudaGetErrorString(err) << std::endl;
    }

    cudaDeviceSynchronize();
}

template void launchKernel2<void(*)(float*, float*, float*, int)>(
    void(*kernel)(float*, float*, float*, int),
    dim3, dim3, size_t, void**, int
);

template void launchKernel2<void(*)(float*, float*, int, int)>(
    void(*kernel)(float*, float*, int, int),
    dim3, dim3, size_t, void**, int
);
}
