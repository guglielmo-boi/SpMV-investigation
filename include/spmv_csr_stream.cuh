#ifndef SPMV_CSR_STREAM_HPP
#define SPMV_CSR_STREAM_HPP

#include "csr_matrix.hpp"
#include "dense_vector.hpp"
#include "spmv_common.cuh"

__global__
void csr_stream_kernel(int rows, int nnz, const int* row_ptr, const int* col_idx, const dtype* values, const dtype* x, dtype* y, const char* is_long);

void spmv_csr_stream(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif