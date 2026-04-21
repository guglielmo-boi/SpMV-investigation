#ifndef SPMV_CPU_HPP
#define SPMV_CPU_HPP

#include "dense_vector.hpp"
#include "csr_matrix.hpp"

void spmv_cpu(DenseVector& y, const DenseVector& x, const CsrMatrix& A, dtype alpha, dtype beta);

#endif