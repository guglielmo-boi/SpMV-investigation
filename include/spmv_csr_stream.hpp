#ifndef SPMV_CSR_STREAM_HPP
#define SPMV_CSR_STREAM_HPP

#include "common.hpp"
#include "csr_matrix.hpp"
#include "dense_vector.hpp"

void spmv_csr_stream(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif