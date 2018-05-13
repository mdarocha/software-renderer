#pragma once

#include <fstream>

struct PPMColor {
    unsigned char r, g, b;
};

//This class allows creation and saving of images in the PPM file format
class PPMImage {
    private:
        unsigned char* data;
        int width, height;

    public:
        PPMImage(int w, int h);
        ~PPMImage();
        bool write_to_file(const char *filename) const;
        bool set(int x, int y, const PPMColor *color);
        int get_width() const;
        int get_height() const;
        const unsigned char* get_data() const;
        PPMColor* get(int x, int y) const;

        friend std::ostream& operator <<(std::ostream &output, const PPMImage &object);
};


