#include <string>
#include <sstream>
#include "obj_model.h"

OBJModel::OBJModel() {

}

OBJModel::~OBJModel() {

}

std::istream& operator >>(std::istream &input, OBJModel &object) {
    std::string line;
    std::string token;

    while(!input.eof()) {
        std::getline(input, line);
        std::istringstream line_s(line);

        line_s >> token;

        if(token == "v") {
            Vector3f vec;
            line_s >> vec.x >> vec.y >> vec.z;
            object.vertices.push_back(vec);
        } else if(token == "#") {
            //comment, ignore
        } else {
            std::cerr << "Warning - unknown token when parsing .obj file: " << token << std::endl;
        }
    }

    return input;
}
