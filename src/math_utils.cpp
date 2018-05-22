#include "math_utils.h"
#include <iostream>

template <class T, size_t dim> T operator *(const MathVector<T, dim> &left, const MathVector<T, dim> &right) {
    T sum = T();
    for(size_t i = 0; i < dim; i++)
        sum += left[i] * right[i];

    return sum;
}

template <class T, size_t dim> MathVector<T, dim> operator +(MathVector<T, dim> &left, const MathVector<T, dim> &right) {
    for(size_t i = 0; i < dim; i++)
        left[i] += right[i];
    return left;
}
template <class T, size_t dim> MathVector<T, dim> operator -(MathVector<T, dim> &left, const MathVector<T, dim> &right) {
    for(size_t i = 0; i < dim; i++)
        left[i] -= right[i];
    return left;
}

template <class T> MathVector<T, 3> MathVector<T, 3>::cross(MathVector<T, 3> v) {
    return MathVector<T, 3>(y * v.z - z * v.y, z * v.x - x * v.z,  x * v.y - y * v.x);
}

template <>
Vector3f Triangle<Point2D>::get_barycentric_coords(Point2D p) {
    Vector3f v[2];

    for(int i = 0; i < 2; i++) {
        v[i][0] = p3[i] - p1[i];
        v[i][1] = p2[i] - p1[i];
        v[i][2] = p1[i] - p[i];
    }

    Vector3f u = v[0].cross(v[1]);

    if(std::abs(u[2]) < 1)
        return Vector3f(-1,1,1);

    return Vector3f(1.0f - (u.x + u.y)/u.z, u.y/u.z, u.x/u.z);
}
