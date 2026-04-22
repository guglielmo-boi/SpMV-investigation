#ifndef SPMV_CSR_VECTOR_HPP
#define SPMV_CSR_VECTOR_HPP

#include "dense_vector.hpp"
#include "csr_matrix.hpp"

void spmv_csr_vector(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif