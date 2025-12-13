#include "vector_binding.h"
#include <cuda_runtime.h>
#include <iostream>

namespace DataBinding {

void** dataInput_d = nullptr;
void** dataOutput_d = nullptr;

int numberOfInputArr_d = 0;
int numberOfOutputArr_d = 0;
int typeSize_d = 0;

int* inputSize_d = nullptr;
int* outputSize_d = nullptr;

void initData(int numberOfInputArr, int numberOfOutputArr, int inputSize[], int outputSize[], int typeSize) 
{
    numberOfInputArr_d = numberOfInputArr;
    numberOfOutputArr_d = numberOfOutputArr;
    typeSize_d = typeSize;

    dataInput_d  = new void*[numberOfInputArr];
    dataOutput_d = new void*[numberOfOutputArr];

    inputSize_d  = new int[numberOfInputArr];
    outputSize_d = new int[numberOfOutputArr];

    for (int i = 0; i < numberOfInputArr; i++) {
        inputSize_d[i] = inputSize[i];
        cudaMalloc(&dataInput_d[i], typeSize * inputSize[i]);
    }

    for (int i = 0; i < numberOfOutputArr; i++) {
        outputSize_d[i] = outputSize[i];
        cudaMalloc(&dataOutput_d[i], typeSize * outputSize[i]);
    }
}

void clearData() 
{
    for (int i = 0; i < numberOfInputArr_d; i++)
        cudaFree(dataInput_d[i]);

    for (int i = 0; i < numberOfOutputArr_d; i++)
        cudaFree(dataOutput_d[i]);

    delete[] dataInput_d;
    delete[] dataOutput_d;
    delete[] inputSize_d;
    delete[] outputSize_d;
    numberOfInputArr_d = 0;
    numberOfOutputArr_d = 0;
    typeSize_d = 0;
    dataInput_d = nullptr;
    dataOutput_d = nullptr;
    inputSize_d = nullptr;
    outputSize_d = nullptr;
}

void setInput(int idx, const void* hostPtr)
{
    if (idx < 0 || idx >= numberOfInputArr_d) {
        std::cerr << "setInput: invalid index " << idx << std::endl;
        return;
    }

    cudaMemcpy(
        dataInput_d[idx],
        hostPtr,
        inputSize_d[idx] * typeSize_d,
        cudaMemcpyHostToDevice
    );
}

void getOutput(int idx, void* hostPtr)
{   
    if (idx < 0 || idx >= numberOfOutputArr_d) {
        std::cerr << "getOutput: invalid index " << idx << std::endl;
        return;
    }

    cudaMemcpy(
        hostPtr,
        dataOutput_d[idx],
        outputSize_d[idx] * typeSize_d,
        cudaMemcpyDeviceToHost
    );
}

}
