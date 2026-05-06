#include "metrics.hpp"

const std::string Metrics::header = "matrix_id,total_execution_time,csr_stream_kernel_execution_time,csr_vector_kernel_execution_time,gflops";

std::ostream& operator<<(std::ostream& os, const Metrics& metrics) {
    os << metrics.matrix_id << "," << metrics.total_execution_time << "," << metrics.csr_stream_kernel_execution_time << "," << 
    metrics.csr_vector_kernel_execution_time << "," << metrics.gflops;

    return os;
}