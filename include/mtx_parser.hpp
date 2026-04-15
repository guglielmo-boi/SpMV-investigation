#ifndef MTX_PARSER_HPP
#define MTX_PARSER_HPP

#include "common.hpp"

#include <vector>
#include <string>

class MtxParser
{
public:
    struct MtxElement
    {
        MtxElement(int row, int col, dtype value);

        int row;
        int col;
        dtype value;
    };

    struct MtxMatrix
    {
        int rows;
        int cols;
        int nnz;

        std::vector<MtxParser::MtxElement> elements;
    };
    
    static MtxParser::MtxMatrix parseMtxFile(const std::string& file_path);
};

bool operator<(const MtxParser::MtxElement& lhs, const MtxParser::MtxElement& rhs);

#endif