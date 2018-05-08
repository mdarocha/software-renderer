#pragma once

#include "ppm_image.h"
#include "math_utils.h"

namespace DrawingUtils {
    void line(Point2D start, Point2D end, PPMColor color, PPMImage &image);
    void triangle(Triangle triangle, PPMColor color, PPMImage &image);
}
