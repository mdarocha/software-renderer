#include <iostream>
#include <cstdio>
#include "ppm_image.h"
#include "obj_model.h"
#include "drawing_utils.h"
#include "camera.h"

int main(int argc, char *argv[]) {
    char *model_filename;
    char *output_filename = (char *)"o.ppm";

    int width, height;
    width = height = 1000;

    switch(argc) {
        default:
            std::cout << "Usage: softrender model.obj output.ppm [width] [height]" << std::endl;
            return 1;
        case 5:
            std::sscanf(argv[4], "%d", &height);
        case 4:
            std::sscanf(argv[3], "%d", &width);
        case 3:
            output_filename = argv[2];
        case 2:
            model_filename  = argv[1];
    }

    PPMImage image(width, height);

    OBJModel model(model_filename);
    model.normalize_model_scale();

    Camera camera(width, height, Vector3f(0.5f,2,3), 1.0f);
    camera.lookat(Vector3f(0,0,0));

    std::cout << camera.get_model() << std::endl << camera.get_viewport();
    std::cout << "Rendering image from model " << model_filename << " with resolution " << width << "x" << height << std::endl;
    DrawingUtils::rasterize(model, image, camera);

    image.write_to_file(output_filename);
    return 0;
}
