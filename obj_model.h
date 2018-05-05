#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "math_utils.h"

class OBJModel {
    private:
        std::vector<Vector3f> vertices;
        std::vector<Vector2f> uv;
        std::vector<Vector3f> normals;
        std::vector<Point3D[3]> faces;

    public:
        OBJModel();
        ~OBJModel();
        friend std::istream& operator >>(std::istream &input, OBJModel &object);
};
