#include <iostream>
#include <fstream>
#include <cstring>
#include "ppm_image.h"

ImageBuffer<DrawingColor> PPMImage::load(std::string filename) {
    std::ifstream file;
    file.open(filename.c_str(), std::ios::binary);

    std::string tag;
    int depth, width, height;

    file >> tag;
    if(tag == "P6") {
        file >> width >> height >> depth;
        DrawingColor* data = new DrawingColor[width * height];
        file.read(reinterpret_cast<char*>(data), width * height * 3);

        return ImageBuffer<DrawingColor>(width, height, data);
    }
}

bool PPMImage::write_to_file(std::string filename) const {
    std::ofstream file;
    file.open(filename.c_str(), std::ios::binary);

    file << "P6\n" << image.get_width() << " " << image.get_height() << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.get_data().get()), image.get_width() * image.get_height() * 3);
    file.close();

    return true;
}
