#pragma once

#include <cstddef>
#include <cassert>

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

template <class T, size_t dim> T operator *(const MathVector<T, dim> &left, const MathVector<T, dim> &right);
template <class T, size_t dim> MathVector<T, dim> operator +(const MathVector<T, dim> &left, const MathVector<T, dim> &right);
template <class T, size_t dim> MathVector<T, dim> operator -(const MathVector<T, dim> &left, const MathVector<T, dim> &right);

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
        MathVector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

        MathVector<T, 3> cross(MathVector<T, 3> v);

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
        }
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
        }
};


typedef MathVector<int, 2> Point2D;
typedef MathVector<double, 2> Vector2f;
typedef MathVector<int, 3> Point3D;
typedef MathVector<double, 3> Vector3f;

template<class T>
class Triangle {
    public:
        T p1, p2, p3;

        Triangle() : p1(T()), p2(T()), p3(T()) {};
        Triangle(T P1, T P2, T P3) : p1(P1), p2(P2), p3(P3) {};

        Vector3f get_barycentric_coords(T p);

        T& operator [](const size_t i) {
            assert(i < 3);
            if(i == 0)
                return p1;
            else if(i == 1)
                return p2;
            else
                return p3;
        };
};
