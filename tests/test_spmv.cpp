#include <gtest/gtest.h>

#include "csr_matrix.hpp"
#include "spmv_cpu.hpp"

TEST(SpMVTests, CsrMatrixTest)
{
    const std::string file_path = "../tests/simple.mtx";
    auto A = CsrMatrix(file_path);

    DenseVector x1(4, 1.0);
    auto y1 = A * x1;

    EXPECT_DOUBLE_EQ(y1[0], 3.0);
    EXPECT_DOUBLE_EQ(y1[1], 3.0);
    EXPECT_DOUBLE_EQ(y1[2], 15.0);
    EXPECT_DOUBLE_EQ(y1[3], 7.0);

    DenseVector x2({1.0, 2.0, 3.0, 4.0});
    auto y2 = A * x2;

    EXPECT_DOUBLE_EQ(y2[0], 7.0);
    EXPECT_DOUBLE_EQ(y2[1], 6.0);
    EXPECT_DOUBLE_EQ(y2[2], 43.0);
    EXPECT_DOUBLE_EQ(y2[3], 28.0);
}

TEST(SpMVTests, SpMVTest)
{
    const std::string file_path = "../tests/simple.mtx";
    auto A = CsrMatrix(file_path);

    DenseVector y(4, 1.0);
    DenseVector x({1.0, 2.0, 3.0, 4.0});

    dtype alpha = 1.0;
    dtype beta = 2.0;

    spmv_cpu(y, x, A, alpha, beta);

    EXPECT_DOUBLE_EQ(y[0], 9.0);
    EXPECT_DOUBLE_EQ(y[1], 8.0);
    EXPECT_DOUBLE_EQ(y[2], 45.0);
    EXPECT_DOUBLE_EQ(y[3], 30.0);
}