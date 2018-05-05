#include <string>
#include <sstream>
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
    return vertices.size();
}

Vector3f OBJModel::get_face_vertex(int n, int nvertex) {
    if(nvertex > 3) return Vector3f{0,0,0};

    return vertices[faces[n].vertex[nvertex]];
}

std::istream& operator >>(std::istream &input, OBJModel &object) {
    std::string line;
    std::string token;

    while(!input.eof()) {
        std::getline(input, line);
        std::istringstream line_s(line);

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

    std::cout << "Loaded model, " << object.vertices.size() << " vertices, " << object.faces.size() << " faces\n";

    return input;
}
