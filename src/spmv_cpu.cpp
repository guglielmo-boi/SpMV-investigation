#include "spmv_cpu.hpp"

void spmv_cpu(const CsrMatrix& A, const DenseVector& x, DenseVector& y) {
    y = A * x;
}