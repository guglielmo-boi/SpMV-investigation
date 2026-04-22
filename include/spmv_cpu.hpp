#ifndef SPMV_CPU_HPP
#define SPMV_CPU_HPP

#include "dense_vector.hpp"
#include "csr_matrix.hpp"

void spmv_cpu(const CsrMatrix& A, const DenseVector& x, DenseVector& y);

#endif