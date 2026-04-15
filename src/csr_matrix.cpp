#include "csr_matrix.hpp"

#include "mtx_parser.hpp"

#include <algorithm>
#include <cmath>

CsrMatrix::CsrMatrix(const std::string& file_path) {
    auto mtx_matrix = MtxParser::parseMtxFile(file_path);

    this->rows = mtx_matrix.rows;
    this->cols = mtx_matrix.cols;
    this->nnz = mtx_matrix.cols;

    this->row_ptr.resize(mtx_matrix.rows + 1, 0);
    this->col_index.resize(mtx_matrix.nnz, 0);
    this->values.resize(mtx_matrix.nnz, 0.0);

    std::sort(mtx_matrix.elements.begin(), mtx_matrix.elements.end());
    
    int counter = 0;

    for (const auto& e : mtx_matrix.elements) {
        this->row_ptr[e.row] += 1;
        this->col_index[counter] = e.col - 1;
        this->values[counter++] = e.value;
    }

    for (int r = 1; r <= this->rows; ++r) {
        this->row_ptr[r] += this->row_ptr[r - 1];
    }
}

bool CsrMatrix::is_close(const CsrMatrix& other, dtype epsilon) const {
    if (this->rows != other.rows || this->cols != other.cols || this->nnz != other.nnz) {
        return false;
    }

    if (this->row_ptr != other.row_ptr) {
        return false;
    }

    for (int i = 0; i < this->nnz; ++i) {
        if (this->col_index[i] != other.col_index[i] || abs(this->values[i] - other.values[i]) > epsilon) {
            return false;
        }
    }

    return true;
}

DenseVector operator*(const CsrMatrix& csr_matrix, const DenseVector& dense_vector) {
    DenseVector ret = DenseVector(dense_vector.size(), 0.0);

    for (int r = 0; r < csr_matrix.rows; ++r) {
        for (int i = csr_matrix.row_ptr[r]; i < csr_matrix.row_ptr[r + 1]; ++i) {
            ret[r] += csr_matrix.values[i] * dense_vector[csr_matrix.col_index[i]]; 
        } 
    }

    return ret;
}