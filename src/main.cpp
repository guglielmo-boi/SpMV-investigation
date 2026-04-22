#include "csr_matrix.hpp"
#include "dense_vector.hpp"
#include "spmv_csr_vector.hpp"

#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main() {
    std::string data_dir = "./data";

    int passed = 0;
    int total = 0;

    for (const auto& entry : fs::directory_iterator(data_dir)) {
        if (entry.path().extension() != ".mtx") {
            continue;
        }

        std::string filename = entry.path().string();

        std::cout << "Testing: " << filename << std::endl;

        CsrMatrix A(filename);

        DenseVector x = DenseVector::random_vector(A.rows);
        DenseVector y_cpu = A * x;
        DenseVector y_gpu(A.rows);
        spmv_csr_vector(A, x, y_gpu);

        bool ok = y_cpu.is_close(y_gpu);

        if (ok) {
            std::cout << "  OK\n";
            passed += 1;
        } else {
            std::cout << "  FAILED\n";
        }

        total += 1;
    }

    std::cout << "\nSummary: " << passed << " / " << total << " passed\n";

    return (passed == total) ? 0 : 1;
}