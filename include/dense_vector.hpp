#ifndef DENSE_VECTOR_HPP
#define DENSE_VECTOR_HPP

#include "common.hpp"

#include <vector>

class DenseVector
{
    friend bool operator==(const DenseVector& lhs, const DenseVector& rhs);
    friend bool operator!=(const DenseVector& lhs, const DenseVector& rhs);

public:
    DenseVector() = default;
    explicit DenseVector(int size, dtype value = 0.0);
    explicit DenseVector(std::initializer_list<dtype> list);

    int size() const;
    dtype* data();
    const dtype* data() const;
    dtype* copy_to_device() const;
    void copy_from_device(dtype* d_values);

    dtype& operator[](int idx);
    const dtype& operator[](int idx) const; 
    DenseVector& operator+=(const DenseVector& rhs);

private:
    std::vector<dtype> values; 
};

bool operator==(const DenseVector& lhs, const DenseVector& rhs);
bool operator!=(const DenseVector& lhs, const DenseVector& rhs);

DenseVector operator+(const DenseVector& lhs, const DenseVector& rhs);
DenseVector operator*(const DenseVector& dense_vector, dtype scalar);
DenseVector operator*(dtype scalar, const DenseVector& dense_vector);

#endif