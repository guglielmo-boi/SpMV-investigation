#include "cuda_event_chrono.cuh"

CudaEventChrono::CudaEventChrono() {
    cudaEventCreate(&this->start);
    cudaEventCreate(&this->stop);
    cudaEventRecord(this->start);
}

CudaEventChrono::~CudaEventChrono() {
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}

float CudaEventChrono::measure_elapsed_milliseconds() {
    cudaEventRecord(this->stop);
    cudaEventSynchronize(this->stop);

    float milliseconds = 0.0;
    cudaEventElapsedTime(&milliseconds, this->start, this->stop);

    return milliseconds;
}