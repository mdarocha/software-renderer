#include <iostream>
#include "image_buffer.h"

ImageBuffer::ImageBuffer() {
    data = nullptr;
    width = 0;
    height = 0;
    pixel_size = 0;
}
ImageBuffer::ImageBuffer(int w, int h, size_t pixel_size) {
    data = new unsigned char[w * h * pixel_size];
    std::memset(data, 0, w * h * pixel_size);

    width = w;
    height = h;
    this->pixel_size = pixel_size;
}

ImageBuffer::~ImageBuffer() {
    if(data != nullptr) {
        delete [] data;
    }
}

int ImageBuffer::get_height() const {
    return height;
}

int ImageBuffer::get_width() const {
    return width;
}

const unsigned char*  ImageBuffer::get_data() const {
    return data;
}

bool ImageBuffer::set(int x, int y, const unsigned char* pixel_data) {
    if(!data || x < 0 || y < 0 || x > width || y > height) {
        std::cerr << "Error setting pixel " << x << " " << y << std::endl;
        return false;
    }

    std::memcpy(data + (x + y * width) * pixel_size, pixel_data, pixel_size);

    return true;
}

const unsigned char* ImageBuffer::get(int x, int y) const {
    if(!data || x < 0 || y < 0 || x > width || y > height) {
        std::cerr << "Error getting pixel " << x << " " << y << std::endl;
        return nullptr;
    }

    unsigned char* temp = new unsigned char[pixel_size];
    std::memcpy(temp, data + (x + y * width) * pixel_size, pixel_size);

    return temp;
}
