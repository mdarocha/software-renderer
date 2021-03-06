#include <iostream>
#include <cstdio>
#include <cmath>

#include "ppm_image.h"
#include "realtime_target.h"

#include "obj_model.h"
#include "drawing_utils.h"
#include "camera.h"
#include "matrix.h"
#include "shader/gouraud.h"

#include "fallback_image.h"

void render_to_image(OBJModel &model, std::string &output, int width, int height);
void render_realtime(OBJModel &model, int width, int height);

int main(int argc, char *argv[]) {
    std::string model_filename;
    std::string output_filename("o.ppm");

    int width, height;
    width = height = 800;

    bool realtime = false;

    switch(argc) {
        default:
            std::cout << "Usage: softrender model.obj [output.ppm] [--realtime] [width] [height]" << std::endl;
            return 1;
        case 5:
            std::sscanf(argv[4], "%d", &height);
        case 4:
            std::sscanf(argv[3], "%d", &width);
        case 3:
            if(std::string(argv[2]) == "--realtime")
                realtime = true;
            else
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

    auto diffuse = PPMImage::load(fallback_ppm, fallback_ppm_len);
    GouraudShader shader(camera.get_model(), camera.get_viewport(), camera.get_projection(), Vector3f(1,1,1), diffuse);

    std::cout << "Rendering image with resolution " << width << "x" << height << std::endl;

    DrawingUtils::rasterize(model, image, camera, shader);
    image.write_to_file(output);
}

Vector3f spherical(double hor, double ver, double dist) {
    Vector3f pos;
    pos.x = dist * sin(hor) * sin(ver);
    pos.y = dist * cos(ver);
    pos.z = dist * cos(hor) * sin(ver);
    return pos;
}

void render_realtime(OBJModel &model, int width, int height) {
    double hor = 45, ver = 45, dist = 1;
    constexpr double move = 0.05;

    Camera camera(width, height, spherical(hor, ver, dist), 1.0f);
    camera.lookat(Vector3f(0,0,0));

    auto diffuse = PPMImage::load(fallback_ppm, fallback_ppm_len);
    GouraudShader shader(camera.get_model(), camera.get_viewport(), camera.get_projection(), Vector3f(1,1,1), diffuse);

    auto handler = [&](SDL_Event *event) {
        if(event->type == SDL_KEYDOWN) {
            switch(event->key.keysym.sym) {
                case SDLK_LEFT:
                    hor -= move; break;
                case SDLK_RIGHT:
                    hor += move; break;
                case SDLK_UP:
                    ver += move; break;
                case SDLK_DOWN:
                    ver -= move; break;
            }

            camera.position = spherical(hor, ver, dist);
            camera.lookat(Vector3f(0,0,0));
            shader.update_model(camera.get_model());
        }
    };

    RealtimeTarget image_target(width, height, handler);

    image_target.start();
    while(image_target.is_running()) {
        DrawingUtils::rasterize(model, image_target, camera, shader);
        image_target.loop();
    }
}
