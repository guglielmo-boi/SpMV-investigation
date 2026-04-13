#include "spmv.hpp"
#include <cuda_runtime.h>
#include <iostream>

// Dummy CUDA kernel (does nothing meaningful yet)
__global__ void spmv_kernel(int n, const float* A, const float* x, float* y)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        y[i] = 0.0f; // placeholder
    }
}

void spmv(int n, const float* A, const float* x, float* y)
{
    float *d_A, *d_x, *d_y;

    // Allocate device memory
    cudaMalloc(&d_A, n * sizeof(float));
    cudaMalloc(&d_x, n * sizeof(float));
    cudaMalloc(&d_y, n * sizeof(float));

    // Copy input to device
    cudaMemcpy(d_A, A, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, n * sizeof(float), cudaMemcpyHostToDevice);

    // Launch kernel
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;
    spmv_kernel<<<gridSize, blockSize>>>(n, d_A, d_x, d_y);

    // Copy result back
    cudaMemcpy(y, d_y, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_x);
    cudaFree(d_y);
}