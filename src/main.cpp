#include "spmv_csr_adaptive.cuh"
#include "spmv_csr_stream.cuh"
#include "spmv_csr_vector.cuh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

std::vector<std::filesystem::path> get_matrix_files(const std::filesystem::path& data_dir) {
    std::vector<std::filesystem::path> files;

    if (!std::filesystem::exists(data_dir) || !std::filesystem::is_directory(data_dir)) {
        std::cerr << "Input directory does not exist!" << std::endl;

        return {};
    }

    for (const auto& entry : std::filesystem::directory_iterator(data_dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mtx") {
            files.push_back(entry.path());
        }
    }

    std::sort(files.begin(), files.end());

    return files;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./spmv <input_directory_path> <output_log_path>" << std::endl;
        return 1;
    }

    std::filesystem::path data_dir(argv[1]);
    auto run_id = std::to_string(std::time(nullptr));

    std::filesystem::path log_dir = std::filesystem::path(argv[2]) / run_id;
    std::filesystem::create_directories(log_dir);

    std::ofstream adaptive_log(log_dir / "csr_adaptive.log");
    std::ofstream stream_log(log_dir / "csr_stream.log");
    std::ofstream vector_log(log_dir / "csr_vector.log");

    adaptive_log << Metrics::header << std::endl;
    stream_log << Metrics::header << std::endl;
    vector_log << Metrics::header << std::endl;

    auto matrix_files = get_matrix_files(data_dir);

    for (const auto& matrix_path : matrix_files) {
        CsrMatrix A(matrix_path);
        DenseVector x = DenseVector::random_vector(A.rows);
        DenseVector y;

        // CSR-Adaptive
        {
            Metrics metrics = spmv_csr_adaptive(A, x, y);
            metrics.matrix_id = matrix_path.filename().stem();
            adaptive_log << metrics << std::endl;
        }

        // CSR-Stream
        {
            Metrics metrics = spmv_csr_stream(A, x, y);
            metrics.matrix_id = matrix_path.filename().stem();
            stream_log << metrics << std::endl;
        }

        // CSR-Vector
        {
            Metrics metrics = spmv_csr_vector(A, x, y);
            metrics.matrix_id = matrix_path.filename().stem();
            vector_log << metrics << std::endl;
        }
    }

    return 0;
}