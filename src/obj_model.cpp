#include <string>
#include <sstream>
#include <limits>
#include "obj_model.h"

OBJModel::OBJModel() {

}

OBJModel::OBJModel(const char* filename) {
    std::ifstream file;
    file.open(filename);

    file >> (*this);

    file.close();
}

OBJModel::~OBJModel() {

}

int OBJModel::get_face_count() {
    return faces.size();
}

Triangle3D OBJModel::get_face_vertices(int n) {
    assert((size_t)n < faces.size());

    Triangle3D v;

    for(int i = 0; i < 3; i++) {
        if((size_t)faces[n].vertex[i] > vertices.size()) {
            std::cerr << "Warning: bad vertex indice in face " << n << std::endl;
        }

        v[i] = vertices[faces[n].vertex[i]];
    }

    return v;
}

Triangle3D OBJModel::get_face_normals(int n) {
    assert((size_t)n < faces.size());

    Triangle3D v;

    for(int i = 0; i < 3; i++) {
        if((size_t)faces[n].normal[i] > normals.size()) {
            std::cerr << "Warning: bad normal indice in face " << n << std::endl;
        }

        v[i] = normals[faces[n].normal[i]];
    }

    return v;
}

Triangle2D OBJModel::get_face_uv(int n) {
    assert((size_t)n < faces.size());
    Triangle2D v;

    for(int i = 0; i < 3; i++) {
        if((size_t)faces[n].uv[i] > uv.size()) {
            std::cerr << "Warning: bad uv indice in face: " << n << std::endl;
        }
        v[i] = uv[faces[n].uv[i]];
    }

    return v;
}
void OBJModel::compute_bounding_box() {
    Vector3f vmax, vmin;
    vmax.x = vmax.y = vmax.z = std::numeric_limits<float>::min();
    vmin.x = vmin.y = vmin.z = std::numeric_limits<float>::max();

    int nvec = vertices.size();
    for(int i = 0; i < nvec; i++) {
        vmax.x = std::max(vertices[i].x, vmax.x);
        vmax.y = std::max(vertices[i].y, vmax.y);
        vmax.z = std::max(vertices[i].z, vmax.z);

        vmin.x = std::min(vertices[i].x, vmin.x);
        vmin.y = std::min(vertices[i].y, vmin.y);
        vmin.z = std::min(vertices[i].z, vmin.z);
    }

    bounding_box.x = std::abs(vmax.x - vmin.x);
    bounding_box.y = std::abs(vmax.y - vmin.y);
    bounding_box.z = std::abs(vmax.z - vmin.z);
}

void OBJModel::normalize_model_scale() {
    float scale = std::max(bounding_box.x, std::max(bounding_box.y, bounding_box.z));
    int nvec = vertices.size();

    for(int i = 0; i < nvec; i++) {
        vertices[i].x /= scale;
        vertices[i].y /= scale;
        vertices[i].z /= scale;
    }
}
std::istream& operator >>(std::istream &input, OBJModel &object) {
    std::string line;
    std::string token;

    while(!input.eof()) {

        std::getline(input, line);
        std::istringstream line_s(line);

        token = "";
        line_s >> token;

        if(token == "v") {
            Vector3f vec3;
            line_s >> vec3.x >> vec3.y >> vec3.z;
            object.vertices.push_back(vec3);
        } else if(token == "vt") {
            Vector2f vec2;
            line_s >> vec2.x >> vec2.y;
            object.uv.push_back(vec2);
        } else if(token == "vn") {
            Vector3f vec3;
            line_s >> vec3.x >> vec3.y >> vec3.z;
            object.normals.push_back(vec3);
        } else if(token == "f") {
            OBJModel::FaceIndices face;
            char c;
            int i = 0;

            while(line_s >> face.vertex[i] >> c >> face.uv[i] >> c >> face.normal[i]) {
                face.vertex[i]--;
                face.uv[i]--;
                face.normal[i]--;
                i++;
            }

            object.faces.push_back(face);
        } else if(token == "#") {
            //comment, ignore
        } else {
            std::cerr << "Warning - unknown token when parsing .obj file: " << token << std::endl;
        }
    }

    object.compute_bounding_box();

    std::cout << "Loaded model, " << object.vertices.size() << " vertices, " << object.faces.size() << " faces\n";

    return input;
}
