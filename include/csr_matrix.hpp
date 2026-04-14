#ifndef CSR_MATRIX_HPP
#define CSR_MATRIX_HPP

#include "common.hpp"
#include "dense_vector.hpp"

#include <vector>
#include <string>

class CsrMatrix
{
    friend DenseVector operator*(const CsrMatrix& csr_matrix, const DenseVector& dense_vector);

public:
    CsrMatrix() = delete;
    CsrMatrix(const std::string& file_path);

    int get_row_nnz_count(int row) const;
    bool is_close(const CsrMatrix& other, dtype epsilon = 1e-6) const;

private:
    int rows;
    int columns;
    int nnz;

    std::vector<int> row_ptr;
    std::vector<int> col_index;
    std::vector<dtype> values;
};

DenseVector operator*(const CsrMatrix& csr_matrix, const DenseVector& dense_vector);

#endif