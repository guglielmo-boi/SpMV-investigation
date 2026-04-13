#ifndef CSR_MATRIX_HPP
#define CSR_MATRIX_HPP

#include <vector>
#include <string>

class CsrMatrix
{
public:
    CsrMatrix() = delete;
    CsrMatrix(const std::string& file_path);

private:
    int rows;
    int columns;
    int nnz;

    std::vector<int> row_ptr;
    std::vector<int> col_index;
    std::vector<double> values;
};

#endif