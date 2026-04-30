#include <gtest/gtest.h>

#include "csr_matrix.hpp"
#include "dense_vector.hpp"
#include "spmv_csr_vector.hpp"
#include "spmv_csr_stream.hpp"

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Helper: collect test files
std::vector<std::string> get_mtx_files(const std::string& data_dir) {
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(data_dir)) {
        if (entry.path().extension() == ".mtx") {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

// Test Fixture
class SpMVTest : public ::testing::TestWithParam<std::string>
{
protected:
    std::string filename;
    std::unique_ptr<CsrMatrix> A;
    DenseVector x;

    void SetUp() override {
        filename = GetParam();

        A = std::make_unique<CsrMatrix>(filename);
        x = DenseVector::random_vector(A->rows);
    }
};

// CSR Vector test
TEST_P(SpMVTest, CSRVectorMatchesCPU) {
    DenseVector y_cpu = (*A) * x;

    DenseVector y_gpu(A->rows);
    spmv_csr_vector(*A, x, y_gpu);

    EXPECT_TRUE(y_cpu.is_close(y_gpu)) << "CSR Vector mismatch for file: " << filename;
}

// CSR Stream test
TEST_P(SpMVTest, CSRStreamMatchesCPU) {
    // DenseVector y_cpu = (*A) * x;

    // DenseVector y_gpu(A->rows);
    // spmv_csr_stream(*A, x, y_gpu);

    // EXPECT_TRUE(y_cpu.is_close(y_gpu)) << "CSR Stream mismatch for file: " << filename;
}

// Instantiate test suite
INSTANTIATE_TEST_SUITE_P(
    MatrixTests,
    SpMVTest,
    ::testing::ValuesIn(get_mtx_files("./data"))
);