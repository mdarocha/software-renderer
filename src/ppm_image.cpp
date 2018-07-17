#include <iostream>
#include <fstream>
#include <cstring>
#include "ppm_image.h"

PPMImage::PPMImage(int w, int h) : ImageBuffer(w, h, 3) {};

bool PPMImage::write_to_file(const char *filename) const {
    std::ofstream file;
    file.open(filename, std::ios::binary);

    file << (*this);

    file.close();

    return true;
}

bool PPMImage::set(int x, int y, const PPMColor &color) {
    return ImageBuffer::set<PPMColor>(x, y, &color);
}

const PPMColor* PPMImage::get(int x, int y) const {
    return ImageBuffer::get<PPMColor>(x, y);
}

std::ostream& operator <<(std::ostream &output, const PPMImage &object) {
    output << "P6" << "\n" << object.get_width() << " " << object.get_height() << "\n" << "255\n";
    output.write(reinterpret_cast<const char*>(object.get_data()), object.get_width() * object.get_height() * 3);

    return output;
}
