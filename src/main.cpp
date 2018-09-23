#include <iostream>
#include <cstdio>

#include "ppm_image.h"
#include "realtime_target.h"

#include "obj_model.h"
#include "drawing_utils.h"
#include "camera.h"
#include "matrix.h"
#include "shader/gouraud.h"

void render_to_image(OBJModel &model, std::string &output, int width, int height);
void render_realtime(OBJModel &model, int width, int height);

int main(int argc, char *argv[]) {
    std::string model_filename;
    std::string output_filename("o.ppm");

    int width, height;
    width = height = 1000;

    bool realtime = false;

    switch(argc) {
        default:
            std::cout << "Usage: softrender model.obj output.ppm [width] [height] [--realtime]" << std::endl;
            return 1;
        case 6:
            if(std::strcmp(argv[5], "--realtime"));
                realtime = true;
        case 5:
            std::sscanf(argv[4], "%d", &height);
        case 4:
            std::sscanf(argv[3], "%d", &width);
        case 3:
            output_filename = argv[2];
        case 2:
            model_filename  = argv[1];
    }

    OBJModel model(model_filename);
    model.normalize_model_scale();

    if(realtime)
        render_realtime(model, width, height);
    else
        render_to_image(model, output_filename, width, height);

    return 0;
}

void render_to_image(OBJModel &model, std::string &output, int width, int height) {
    PPMImage image(width, height);

    Camera camera(width, height, Vector3f(0,1,0.1), 1.0f);
    camera.lookat(Vector3f(0,0,0));

    auto diffuse = PPMImage::load("../grid.ppm");
    GouraudShader shader(camera.get_model(), camera.get_viewport(), camera.get_projection(), Vector3f(1,1,1), diffuse);

    std::cout << "Rendering image with resolution " << width << "x" << height << std::endl;

    DrawingUtils::rasterize(model, image, camera, shader);
    image.write_to_file(output);
}

void render_realtime(OBJModel &model, int width, int height) {
    RealtimeTarget image_target(width, height);

    Camera camera(width, height, Vector3f(0,1,0.1), 1.0f);
    camera.lookat(Vector3f(0,0,0));

    auto diffuse = PPMImage::load("../grid.ppm");
    GouraudShader shader(camera.get_model(), camera.get_viewport(), camera.get_projection(), Vector3f(1,1,1), diffuse);

    DrawingUtils::rasterize(model, image_target, camera, shader);
}
