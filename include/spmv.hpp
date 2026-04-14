#ifndef SPMV_HPP
#define SPMV_HPP

#include "common.hpp"
#include "dense_vector.hpp"
#include "csr_matrix.hpp"

void spmv(DenseVector& y, const DenseVector& x, const CsrMatrix& A, dtype alpha, dtype beta);

#endif