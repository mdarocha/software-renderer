#include <iostream>
#include "ppm_image.h"
#include "drawing_utils.h"

int main() {
    PPMImage image(100,100);

    PPMColor white = {255,255,255};
    PPMColor red   = {255,0,0};

    DrawingUtils::line(Point2D{13,20}, Point2D{80,40}, white, image);
    DrawingUtils::line(Point2D{20,13}, Point2D{40,80}, white, image);
    DrawingUtils::line(Point2D{80,40}, Point2D{13,20}, red  , image);

    image.write_to_file("test.ppm");
}
