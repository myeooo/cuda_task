#pragma once

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
}
