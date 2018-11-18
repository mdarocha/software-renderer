#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "ppm_image.h"

ImageBuffer<DrawingColor> decode_stream(std::istream &stream) {
    std::string tag;
    int depth, width, height;

    stream >> tag;

    std::cout << tag << std::endl;
    if(tag == "P6") {
        stream >> width >> height >> depth;
        std::cout << width << " " << height << " " << depth << std::endl;
        DrawingColor* data = new DrawingColor[width * height];
        stream.read(reinterpret_cast<char*>(data), width * height * 3);

        return ImageBuffer<DrawingColor>(width, height, data);
    }

}

ImageBuffer<DrawingColor> PPMImage::load(std::string filename) {
    std::ifstream file;
    file.open(filename.c_str(), std::ios::binary);
    return decode_stream(file);
}

ImageBuffer<DrawingColor> PPMImage::load(unsigned char array[], unsigned int len) {
    std::stringstream s;
    s.write(reinterpret_cast<const char*>(array), len);
    return decode_stream(s);
}

bool PPMImage::write_to_file(std::string filename) const {
    std::ofstream file;
    file.open(filename.c_str(), std::ios::binary);

    file << "P6\n" << image.get_width() << " " << image.get_height() << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.get_data().get()), image.get_width() * image.get_height() * 3);
    file.close();

    return true;
}
