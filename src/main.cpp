#include "spmv.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    int n = 4;
    CsrMatrix A("/home/guglielmo/Uni/SpMV-investigation/tests/simple.mtx");
    DenseVector x(n, 1.0);
    DenseVector y = A * x;

    return 0;
}