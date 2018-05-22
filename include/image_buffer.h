#pragma once

#include <cstring>

class ImageBuffer {
    protected:
        unsigned char* data;
        int width, height, pixel_size;

    public:
        ImageBuffer(int w, int h, int pixel_size);
        ~ImageBuffer();
        bool set(int x, int y, const unsigned char* data);
        const unsigned char* get(int x, int y) const;
        int get_width() const;
        int get_height() const;
        const unsigned char* get_data() const;
};
