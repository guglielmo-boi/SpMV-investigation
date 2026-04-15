#include "mtx_parser.hpp"

#include <fstream>
#include <sstream>

MtxParser::MtxElement::MtxElement(int row, int col, dtype value) : row(row), col(col), value(value) {}

bool operator<(const MtxParser::MtxElement& lhs, const MtxParser::MtxElement& rhs) {
    if (lhs.row != rhs.row) {
        return lhs.row < rhs.row;
    }

    return lhs.col < rhs.col;
}

MtxParser::MtxMatrix MtxParser::parseMtxFile(const std::string& file_path) {
    std::ifstream ifs(file_path);

    bool parsed_first_line = false;
    std::string line;
    
    MtxParser::MtxMatrix ret;

    while (std::getline(ifs, line)) {
        if (line[0] != '%') {
            std::istringstream iss(line);

            if (!parsed_first_line) {
                iss >> ret.rows >> ret.cols >> ret.nnz;
                parsed_first_line = true;
            } else {
                int row, col;
                dtype value;
                iss >> row >> col >> value;
                ret.elements.emplace_back(row, col, value);
            }
        } 
    }

    return ret;
}