#pragma once

#include "ppm_image.h"
#include "math_utils.h"

namespace DrawingUtils {
    void line(Point2D start, Point2D end, PPMColor color, PPMImage &image);
    void triangle(Point2D a, Point2D b, Point2D c, PPMColor color, PPMImage &image);
}
