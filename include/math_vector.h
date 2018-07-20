#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>
#include <cmath>

template <class T, size_t dim>
class MathVector {
    private:
        T data[dim];

    public:
        MathVector() {
            for(size_t i = 0; i < dim; i++)
                data[i] = T();
        }

        T& operator [](const size_t i) {
            assert(i < dim);
            return data[i];
        }
        const T& operator [](const size_t i) const {
            assert(i < dim);
            return data[i];
        }
};

template <class T, size_t dim, class U> MathVector<T, dim> operator *(const MathVector<T, dim> &left, const U &right) {
    MathVector<T, dim> result;
    for(size_t i = 0; i < dim; i++)
        result[i] = left[i] * right;
    return result;
}
template <class T, size_t dim> T operator *(const MathVector<T, dim> &left, const MathVector<T, dim> &right) {
    T sum = T();
    for(size_t i = 0; i < dim; i++)
        sum += left[i] * right[i];

    return sum;
}

template <class T, size_t dim> MathVector<T, dim> operator +(MathVector<T, dim> left, const MathVector<T, dim>& right) {
    for(size_t i = 0; i < dim; i++)
        left[i] += right[i];
    return left;
}

template <class T, size_t dim> MathVector<T, dim> operator -(MathVector<T, dim> left, const MathVector<T, dim>& right) {
    for(size_t i = 0; i < dim; i++)
        left[i] -= right[i];
    return left;
}

template <class T, size_t dim>
std::ostream& operator <<(std::ostream &out, MathVector<T, dim> v) {
    for(size_t i = 0; i < dim; i++)
        out << v[i] << " ";
    return out;
}

template <class T>
class MathVector<T, 2> {
    public:
        T x, y;

        MathVector() : x(T()), y(T()) {};
        MathVector(T X, T Y) : x(X), y(Y) {}

        T& operator [](const size_t i) {
            assert(i < 2);
            return i == 0 ? x : y;
        }
        const T& operator [](const size_t i) const {
            assert(i < 2);
            return i == 0 ? x : y;
        }
};

template <class T>
class MathVector<T, 3> {
    public:
        T x, y, z;

        MathVector() : x(T()), y(T()), z(T()) {};
        MathVector(T X, T Y, T Z) : x(X), y(Y), z(Z) {};

        MathVector<T, 3> cross(MathVector<T, 3> v) {
            return MathVector<T, 3>(y * v.z - z * v.y, z * v.x - x * v.z,  x * v.y - y * v.x);
        };

        double length() {
            return std::sqrt(x*x + y*y + z*z);
        }

        MathVector<T,3>& normalize() {
            if(this->length() != 0)
                *this = *this * (1.0f/this->length());
            return *this;
        }

        MathVector<T,3>& round_down() {
            *this = MathVector<T,3>(std::floor(x), std::floor(y), std::floor(z));
            return *this;
        }

        operator MathVector<T, 4>() {
            return MathVector<T,4>(x, y, z);
        }

        T& operator [](const size_t i) {
            assert(i < 3);
            switch(i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
            }
        };

        const T& operator [](const size_t i) const {
            assert(i < 3);
            switch(i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
            }
        };
};

template<class T>
class MathVector<T, 4> {
    public:
        T x, y, z, w;

        MathVector() : x(T()), y(T()), z(T()) , w(T()){};
        MathVector(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {};
        MathVector(T X, T Y, T Z) : x(X), y(Y), z(Z), w(T(1)) {};

        operator MathVector<T, 3>() {
            return MathVector<T, 3>(x/w, y/w, z/w);
        };

        T& operator [](const size_t i) {
            assert(i < 4);
            switch(i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                case 3:
                    return w;
            }
        };

        const T& operator [](const size_t i) const {
            assert(i < 4);
            switch(i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                case 3:
                    return w;
            }
        };
};

typedef MathVector<int, 2> Point2D;
typedef MathVector<double, 2> Vector2f;
typedef MathVector<int, 3> Point3D;
typedef MathVector<double, 3> Vector3f;
typedef MathVector<double, 4> Vector4f;
