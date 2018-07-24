#pragma once

#include <fstream>
#include "image_buffer.h"
#include "math_vector.h"

struct PPMColor {
    unsigned char r, g, b;
};

template<class T>
PPMColor operator*(const PPMColor &left, const T &right) {
    PPMColor result;
    result.r = left.r * right;
    result.g = left.g * right;
    result.b = left.b * right;
    return result;
}

//This class allows creation and saving of images in the PPM file format
class PPMImage : public ImageBuffer {
    public:
        PPMImage(int w, int h) : ImageBuffer(w, h, 3) {};
        PPMImage(const char* filename);
        bool write_to_file(const char *filename) const;
        PPMImage& load_from_file(const char *filename);
        bool set(int x, int y, const PPMColor &color);
        const PPMColor& get(int x, int y) const;

        template<class T>
        const PPMColor& get(MathVector<T, 2> v) const {
            return get((int)v.x, (int)v.y);
        }

        friend std::ostream& operator <<(std::ostream &output, const PPMImage &object);
};
