#ifndef SPMV_CSR_VECTOR_HPP
#define SPMV_CSR_VECTOR_HPP

#include "common.hpp"
#include "csr_matrix.hpp"
#include "dense_vector.hpp"

void spmv_csr_vector(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif