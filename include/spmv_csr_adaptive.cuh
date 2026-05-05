#ifndef SPMV_CSR_ADAPTIVE_HPP
#define SPMV_CSR_ADAPTIVE_HPP

#include "csr_matrix.hpp"
#include "dense_vector.hpp"
#include "spmv_common.cuh"

void spmv_csr_adaptive(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif