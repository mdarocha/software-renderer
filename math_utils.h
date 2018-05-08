#pragma once

#include <cstddef>
#include <cassert>

struct Point2D {
    int x, y;
};

struct Point3D {
    int x, y, z;
};

struct Vector2f {
    double x, y;
};

struct Vector3f {
    double x, y, z;
};

class Triangle {
    public:
        Point2D p1, p2, p3;

        Triangle();
        Triangle(Point2D p1, Point2D p2, Point2D p3);
        ~Triangle();

        Point2D get_barycentric_coords(Point2D p);

        Point2D& operator[](std::size_t i) {
            assert(i < 3);
            if(i == 0)
                return p1;
            else if(i == 1)
                return p2;
            else if(i == 2)
                return p3;
        };
};
