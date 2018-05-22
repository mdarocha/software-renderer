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

        struct FaceIndices {
            int vertex[3], uv[3], normal[3];
        };
        std::vector<FaceIndices> faces;

        Vector3f bounding_box;
        void compute_bounding_box();

    public:
        OBJModel();
        OBJModel(const char* filename);
        ~OBJModel();
        friend std::istream& operator >>(std::istream &input, OBJModel &object);

        void normalize_model_scale();

        int get_face_count();
        bool get_face_vertices(Vector3f *v, int nface);
};
