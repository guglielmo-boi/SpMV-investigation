#ifndef DENSE_VECTOR_HPP
#define DENSE_VECTOR_HPP

#include "common.hpp"

#include <vector>
#include <cstddef>

class DenseVector
{
public:
    DenseVector() = default;
    explicit DenseVector(int size, dtype value = 0.0);
    explicit DenseVector(std::initializer_list<dtype> list);

    bool is_close(const DenseVector& other, dtype epsilon = 1e-6) const;

    std::size_t size() const;
    dtype* data();
    const dtype* data() const;
    dtype* copy_to_device() const;
    void copy_from_device(dtype* d_values);

    dtype& operator[](std::size_t idx);
    const dtype& operator[](std::size_t idx) const; 
    DenseVector& operator+=(const DenseVector& rhs);

private:
    std::vector<dtype> values; 
};

DenseVector operator+(const DenseVector& lhs, const DenseVector& rhs);
DenseVector operator*(const DenseVector& dense_vector, dtype scalar);
DenseVector operator*(dtype scalar, const DenseVector& dense_vector);

#endif