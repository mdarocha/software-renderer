#pragma once

#include <fstream>
#include "image_buffer.h"
#include "math_vector.h"
#include "drawing_target.h"

//This class allows creation and saving of images in the PPM file format
class PPMImage : public DrawingTarget {
    ImageBuffer<DrawingColor> image;

    public:
        PPMImage(int w, int h) : image(w, h) {};

        virtual ~PPMImage() {};

        virtual int get_height() const { return image.get_height(); };
        virtual int get_width() const { return image.get_width(); };

        virtual void set(int x, int y, DrawingColor color) { image.set(x, y, color); };

        bool write_to_file(std::string filename) const;
        static ImageBuffer<DrawingColor> load(std::string filename);
};
