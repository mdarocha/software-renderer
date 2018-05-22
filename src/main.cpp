#include <iostream>
#include <fstream>
#include "ppm_image.h"
#include "obj_model.h"
#include "drawing_utils.h"

int main() {
    int width, height;
    width = height = 1000;

    PPMImage image(width, height);

    OBJModel model("../teapot.obj");
    model.normalize_model_scale();

    DrawingUtils::rasterize(model, image);

    image.write_to_file("test.ppm");
}
