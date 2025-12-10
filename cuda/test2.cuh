#pragma once
#include <cuda_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

// Khai báo hàm wrapper chạy kernel
void launchSubKernel(int* h_c, const int* h_a, const int* h_b);

void checkCudaBlockAndThread();
#ifdef __cplusplus
}
#endif
