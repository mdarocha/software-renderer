#pragma once
#include "math_vector.h"

template <class T, size_t rows, size_t columns>
class Matrix {
    private:
        MathVector<T, columns> data[rows];

    public:
        Matrix() {
            for(size_t i = 0; i < rows; i++)
                data[i] = MathVector<T, columns>();
        }

        MathVector<T, columns>& operator[](const size_t i) {
            assert(i < rows);
            return data[i];
        }

        const MathVector<T, columns>& operator[](const size_t i) const {
            assert(i < rows);
            return data[i];
        }

        MathVector<T, rows> get_column(const size_t i) const {
            assert(i < columns);
            MathVector<T, rows> result;

            for(int j = 0; j < rows; j++)
                result[j] = data[j][i];

            return result;
        }

        void set_column(const size_t i, const MathVector<T, columns> &input) const {
            assert(i < columns);
            for(int j = 0; j < rows; j++)
                data[j][i] = input[i];
        }

        void identity() {
            for(size_t i = 0; i < rows; i++) {
                for(size_t j = 0; j < columns; j++) {
                    if(i == j)
                        data[i][j] = 1;
                    else
                        data[i][j] = 0;
                }
            }
        }
};

template <class T, size_t rows, size_t columns>
Matrix<T, rows, columns> operator +(const Matrix<T, rows, columns> &left, const Matrix<T, rows, columns> &right) {
    Matrix<T, rows, columns> result;
    for(size_t i = 0; i < rows; i++)
        result[i] = left[i] + right[i];
    return result;
};

template <class T, size_t rows, size_t columns>
Matrix<T, rows, columns> operator -(const Matrix<T, rows, columns> &left, const Matrix<T, rows, columns> &right) {
    Matrix<T, rows, columns> result;
    for(size_t i = 0; i < rows; i++)
        result[i] = left[i] - right[i];
    return result;
};

template <class T, size_t rows, size_t columns>
MathVector<T, rows> operator *(const Matrix<T, rows, columns> &left, const MathVector<T, columns> &right) {
    MathVector<T, rows> result;
    for(size_t i = 0; i < rows; i++)
        result[i] = left[i] * right;

    return result;
};

template <class T, size_t m, size_t p, size_t n>
Matrix<T, m, p> operator *(const Matrix<T, m, p> &left, const Matrix<T, p, n> &right) {
    Matrix<T, m, p> result;
    for(size_t i = 0; i < m; i++)
        for(size_t j = 0; j < p; j++)
            result[i][j] = left[i] * right.get_column(i);
    return result;
}

template <class T, size_t rows, size_t columns>
std::ostream& operator <<(std::ostream &out, Matrix<T, rows, columns> m) {
    for(size_t i = 0; i < rows; i++)
        out << m[i] << std::endl;
    return out;
}

typedef Matrix<double, 4, 4> Mat4x4f;
