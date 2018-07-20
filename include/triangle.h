#pragma once
#include <iostream>
#include <cassert>
#include "math_vector.h"
#include "matrix.h"

template<class T>
struct Rect {
    T a;
    T b;
};

template<class T, size_t dim>
class Triangle {
    private:
        Rect<MathVector<T,dim>> bounding_box;

        void calculate_bounding_box() {
            for(size_t i = 0; i < dim; i++) {
                bounding_box.a[i] = std::max(p1[i], std::max(p2[i], p3[i]));
                bounding_box.b[i] = std::min(p1[i], std::min(p2[i], p3[i]));
            }

        };

    public:
        MathVector<T,dim> p1, p2, p3;

        Triangle() : p1(MathVector<T,dim>()), p2(MathVector<T,dim>()), p3(MathVector<T,dim>()) {};
        Triangle(MathVector<T,dim> P1, MathVector<T,dim> P2, MathVector<T,dim> P3) : p1(P1), p2(P2), p3(P3) {};

        MathVector<T,dim>& operator [](const size_t i) {
            assert(i < 3);
            if(i == 0)
                return p1;
            else if(i == 1)
                return p2;
            else
                return p3;
        };

        const MathVector<T,dim>& operator [](const size_t i) const {
            assert(i < 3);
            if(i == 0)
                return p1;
            else if(i == 1)
                return p2;
            else
                return p3;
        };

        MathVector<T,3> get_barycentric_coords(MathVector<T, 3> p) {
            MathVector<T,3> v[3];

            for(size_t i = 0; i < 3; i++) {
                v[i][0] = p3[i] - p1[i];
                v[i][1] = p2[i] - p1[i];
                v[i][2] = p1[i] - p[i];
            }

            MathVector<T,3> u = v[0].cross(v[1]);

            if(std::abs(u[2]) < 1)
                return MathVector<T,3>(-1,1,1);

            return MathVector<T,3>(1.0f - (u.x + u.y)/u.z, u.y/u.z, u.x/u.z);
        }

        const Rect<MathVector<T,dim>> get_bounding_box() {
            calculate_bounding_box();
            return bounding_box;
        }

        operator Triangle<T,4>() {
            return Triangle<T,4>(p1, p2, p3);
        }

        operator Triangle<T,3>() {
            return Triangle<T,3>(p1, p2, p3);
        }

        Triangle<T,3>& round_down() {
            *this = Triangle<T,3>(p1.round_down(), p2.round_down(), p3.round_down());
            return *this;
        }
};

template <class T, size_t rows, size_t columns>
Triangle<T, rows> operator *(const Matrix<T, rows, columns> &left, const Triangle<T, columns> &right) {
    Triangle<T, rows> result;
    for(size_t i = 0; i < 3; i++)
        result[i] = left * right[i];
    return result;
}

template <class T, size_t dim>
std::ostream& operator <<(std::ostream& out, Triangle<T, dim> t) {
    out << "p1 " << t.p1;
    out << "p2 " << t.p2;
    out << "p3 " << t.p3;
    return out;
}
typedef Triangle<double, 4> Triangle4D;
typedef Triangle<double, 3> Triangle3D;
typedef Triangle<double, 2> Triangle2D;
typedef Triangle<int, 2> Triangle2Di;
