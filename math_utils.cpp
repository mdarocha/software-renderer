#include "math_utils.h"

Triangle::Triangle() {
    p1 = p2 = p3 = Point2D{0,0};
}

Triangle::Triangle(Point2D p1, Point2D p2, Point2D p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Triangle::~Triangle() {

}

Point2D Triangle::get_barycentric_coords(Point2D p) {

}
