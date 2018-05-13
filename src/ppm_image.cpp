#include <iostream>
#include <fstream>
#include <cstring>
#include "ppm_image.h"

PPMImage::PPMImage(int w, int h) {
    data = new unsigned char[w * h * 3];
    std::memset(data, 0, w * h * 3);

    this->width = w;
    this->height = h;
}

PPMImage::~PPMImage() {
    if(data != nullptr) {
        delete [] data;
    }
}

int PPMImage::get_height() const {
    return this->height;
}

int PPMImage::get_width() const {
    return this->width;
}

const unsigned char*  PPMImage::get_data() const {
    return this->data;
}

bool PPMImage::write_to_file(const char *filename) const {
    std::ofstream file;
    file.open(filename, std::ios::binary);

    file << (*this);

    file.close();

    return true;
}

bool PPMImage::set(int x, int y, const PPMColor *color) {
    if(!data || x < 0 || y < 0 || x > width || y > height) {
        std::cerr << "Error setting pixel " << x << " " << y << std::endl;
        return false;
    }

    std::memcpy(data + (x + y * width) * 3, color, 3);
    return true;
}

PPMColor* PPMImage::get(int x, int y) const {
    if(!data || x < 0 || y < 0 || x > width || y > height) {
        std::cerr << "Error getting pixel " << x << " " << y << std::endl;
        return nullptr;
    }

    PPMColor* temp = new PPMColor();
    std::memcpy(temp, data + (x + y * width) * 3, 3);
    return temp;
}

std::ostream& operator <<(std::ostream &output, const PPMImage &object) {
    output << "P6" << "\n" << object.get_width() << " " << object.get_height() << "\n" << "255\n";
    output.write(reinterpret_cast<const char*>(object.get_data()), object.get_width() * object.get_height() * 3);

    return output;
}
