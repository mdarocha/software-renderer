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
