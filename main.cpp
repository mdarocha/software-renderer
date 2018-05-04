#include <iostream>
#include "ppm_image.h"
#include "drawing_utils.h"

int main() {
    PPMImage image(100,100);

    PPMColor white = {255,255,255};

    DrawingUtils::triangle(Point2D{10,10},Point2D{90,20},Point2D{50, 45}, white, image);

    image.write_to_file("test.ppm");
}
