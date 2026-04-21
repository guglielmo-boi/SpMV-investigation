#include "spmv_cpu.hpp"

void spmv_cpu(DenseVector& y, const DenseVector& x, const CsrMatrix& A, dtype alpha, dtype beta) {
    DenseVector result = alpha * (A * x);
    result += (beta * y);
    y = std::move(result);
}