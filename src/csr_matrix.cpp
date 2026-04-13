#include "csr_matrix.hpp"

#include <fstream>

CsrMatrix::CsrMatrix(const std::string& file_path) {
    std::ifstream ifs(file_path);

    bool parsed_first_line = false;
    int counter = 0;
    std::string line;

    while (std::getline(ifs, line)) {
        if (line[0] != '%') {
            if (!parsed_first_line) {
                ifs >> this->rows;
                ifs >> this->columns;
                ifs >> this->nnz;

                this->row_ptr.resize(this->rows, 0);
                this->col_index.resize(this->nnz, 0);
                this->values.resize(this->nnz, 0.0);

                parsed_first_line = true;
            } else {
                int row, column, value;
                ifs >> row >> column >> value;

                this->row_ptr[row - 1] += 1;
                this->col_index[counter] = column - 1;
                this->values[counter++] = value;
            }
        } 
    }
}