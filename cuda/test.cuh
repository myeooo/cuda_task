#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
void launchAddKernel(int* h_c, const int* h_a, const int* h_b);

#ifdef __cplusplus
}
#endif
