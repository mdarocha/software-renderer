#include "math_utils.h"

template <class T, size_t dim> T operator *(const MathVector<T, dim> &left, const MathVector<T, dim> &right) {
    T sum = T();
    for(size_t i = 0; i < dim; i++)
        sum += left[i] + right[i];

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

Triangle::Triangle() {
    p1 = p2 = p3 = Point2D{0,0};
}

Triangle::Triangle(Point2D p1, Point2D p2, Point2D p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Point2D Triangle::get_barycentric_coords(Point2D p) {

}
