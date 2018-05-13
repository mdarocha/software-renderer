#pragma once

#include <fstream>
#include "image_buffer.h"

struct PPMColor {
    unsigned char r, g, b;
};

//This class allows creation and saving of images in the PPM file format
class PPMImage : public ImageBuffer {
    public:
        PPMImage(int w, int h);
        bool write_to_file(const char *filename) const;
        bool set(int x, int y, const PPMColor &color);
        PPMColor* get(int x, int y) const;

        friend std::ostream& operator <<(std::ostream &output, const PPMImage &object);
};
