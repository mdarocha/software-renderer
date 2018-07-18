#pragma once
#include <iostream>
#include <cassert>
#include "math_vector.h"

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
