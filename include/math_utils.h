#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>

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

        size_t get_dim();
};

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

        size_t get_dim() {
            return 2;
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

        size_t get_dim() {
            return 3;
        }
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

        size_t get_dim() {
            return 4;
        }
};

typedef MathVector<int, 2> Point2D;
typedef MathVector<double, 2> Vector2f;
typedef MathVector<int, 3> Point3D;
typedef MathVector<double, 3> Vector3f;
typedef MathVector<double, 4> Vector4f;

template<class T>
struct Rect {
    T a;
    T b;
};

template<class T>
class Triangle {
    private:
        Rect<T> bounding_box;

        void calculate_bounding_box() {
            size_t dim = p1.get_dim();
            for(size_t i = 0; i < dim; i++) {
                bounding_box.a[i] = std::max(p1[i], std::max(p2[i], p3[i]));
                bounding_box.b[i] = std::min(p1[i], std::min(p2[i], p3[i]));
            }

        };

    public:
        T p1, p2, p3;

        Triangle() : p1(T()), p2(T()), p3(T()) {};
        Triangle(T P1, T P2, T P3) : p1(P1), p2(P2), p3(P3) {};

        T& operator [](const size_t i) {
            assert(i < 3);
            if(i == 0)
                return p1;
            else if(i == 1)
                return p2;
            else
                return p3;
        };

        Vector3f get_barycentric_coords(T p) {
            size_t dim = p.get_dim();
            Vector3f* v = new Vector3f[dim];

            for(size_t i = 0; i < dim; i++) {
                v[i][0] = p3[i] - p1[i];
                v[i][1] = p2[i] - p1[i];
                v[i][2] = p1[i] - p[i];
            }

            Vector3f u = v[0].cross(v[1]);

            if(std::abs(u[2]) < 1)
                return Vector3f(-1,1,1);

            delete [] v;
            return Vector3f(1.0f - (u.x + u.y)/u.z, u.y/u.z, u.x/u.z);
        }

        const Rect<T> get_bounding_box() {
            calculate_bounding_box();
            return bounding_box;
        }
};
