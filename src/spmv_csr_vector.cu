#include "spmv_csr_vector.hpp"

#include <cuda_runtime.h>

#define WARP_SIZE 32

// Warp-level reduction
__inline__ __device__
dtype warp_reduce_sum(dtype val) {
    for (int offset = WARP_SIZE / 2; offset > 0; offset /= 2) {
        val += __shfl_down_sync(0xffffffff, val, offset);
    }
        
    return val;
}

// CSR-Vector kernel (1 warp = 1 row)
__global__
void csr_vector_kernel(
    int rows,
    const int* row_ptr,
    const int* col_idx,
    const dtype* values,
    const dtype* x,
    dtype* y)
{
    int global_thread_id = blockIdx.x * blockDim.x + threadIdx.x;

    int warp_id = global_thread_id / WARP_SIZE;
    int lane = threadIdx.x % WARP_SIZE;

    if (warp_id >= rows) {
        return;
    }

    int row_start = row_ptr[warp_id];
    int row_end = row_ptr[warp_id + 1];

    dtype sum = 0;

    // each thread processes one part of the row
    for (int j = row_start + lane; j < row_end; j += WARP_SIZE) {
        sum += values[j] * x[col_idx[j]];
    }

    sum = warp_reduce_sum(sum);

    if (lane == 0) {
        y[warp_id] = sum;
    }
}

void spmv_csr_vector(const CsrMatrix& A, const DenseVector& x, DenseVector& y) {
    auto view = A.copy_to_device();
    dtype* d_x = x.copy_to_device();

    dtype* d_y;
    cudaMalloc(&d_y, A.rows * sizeof(dtype));

    int threads = 128;
    int warps_per_block = threads / WARP_SIZE;

    int blocks = (A.rows + warps_per_block - 1) / warps_per_block;

    csr_vector_kernel<<<blocks, threads>>>(
        A.rows,
        view.d_row_ptr,
        view.d_col_index,
        view.d_values,
        d_x,
        d_y
    );

    y.copy_from_device(d_y);

    cudaFree(d_x);
    cudaFree(d_y);
}