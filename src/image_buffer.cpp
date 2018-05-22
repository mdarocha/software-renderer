#include <iostream>
#include "image_buffer.h"

ImageBuffer::ImageBuffer(int w, int h, int pixel_size) {
    data = new unsigned char[w * h * pixel_size];
    std::memset(data, 0, w * h * pixel_size);

    width = w;
    height = h;
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

    std::memcpy(data + (x + y * width) * 3, pixel_data, 3);

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
