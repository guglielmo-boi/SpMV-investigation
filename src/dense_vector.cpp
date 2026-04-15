#include "dense_vector.hpp"

DenseVector::DenseVector(int size, dtype value) : values(size, value) {}

DenseVector::DenseVector(std::initializer_list<dtype> list) : values(list) {}

int DenseVector::size() const {
    return this->values.size();
}

dtype& DenseVector::operator[](int idx) {
    return this->values[idx];
}

const dtype& DenseVector::operator[](int idx) const {
    return this->values[idx];
}

DenseVector& DenseVector::operator+=(const DenseVector& rhs) {
    for (int i = 0; i < this->size(); ++i) {
        (*this)[i] += rhs[i];
    }

    return *this;
}

bool operator==(const DenseVector& lhs, const DenseVector& rhs) {
    return lhs.values == rhs.values;
}

bool operator!=(const DenseVector& lhs, const DenseVector& rhs) {
    return !(lhs == rhs);
}

DenseVector operator+(const DenseVector& lhs, const DenseVector& rhs) {
    DenseVector ret = lhs;
    ret += rhs;
    return ret;
}

DenseVector operator*(const DenseVector& dense_vector, dtype scalar) {
    DenseVector ret = dense_vector;
    
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] *= scalar;
    }

    return ret;
}

DenseVector operator*(dtype scalar, const DenseVector& dense_vector) {
    return dense_vector * scalar;
}