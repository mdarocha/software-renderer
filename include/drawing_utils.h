#pragma once

#include "ppm_image.h"
#include "image_buffer.h"
#include "math_vector.h"
#include "triangle.h"
#include "matrix.h"
#include "obj_model.h"

namespace DrawingUtils {
    void rasterize(OBJModel &model, PPMImage &image);
    void line(Point2D start, Point2D end, PPMColor color, PPMImage &image);
    void triangle(Triangle2Di triangle, PPMColor color, PPMImage &image);
    void shaded_triangle(Triangle3D &triangle, PPMColor color, PPMImage &image, ImageBuffer &depth_buffer);
}
