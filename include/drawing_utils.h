#pragma once

#include "ppm_image.h"
#include "math_utils.h"
#include "obj_model.h"

namespace DrawingUtils {
    void rasterize(OBJModel &model, PPMImage &image);
    void line(Point2D start, Point2D end, PPMColor color, PPMImage &image);
    void triangle(Triangle triangle, PPMColor color, PPMImage &image);
    void filled_triangle(Triangle triangle, PPMColor color, PPMImage &image);
}
