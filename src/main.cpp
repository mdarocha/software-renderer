#include <iostream>
#include <cstdio>
#include "ppm_image.h"
#include "obj_model.h"
#include "drawing_utils.h"
#include "camera.h"
#include "matrix.h"

struct GouraudShader : public Shader {
    //uniforms
    Mat4x4f model, viewport, projection;
    Vector3f light_dir;
    //varying
    Vector3f intensity;

    GouraudShader(Mat4x4f m, Mat4x4f v, Mat4x4f p, Vector3f light) : model(m), viewport(v), projection(p), light_dir(light.normalize()) {};

    virtual Vector4f vertex(Vector3f v, Vector3f normal, Vector2f uv, int n) {
        intensity[n] = normal*light_dir;
        if(intensity[n] < 0.0f)
            intensity[n] = 0.0f;

        Vector4f vertex = v;
        return viewport * projection * model * vertex;
    }

    virtual bool fragment(PPMColor &color, Vector3f bary) {
        double i = bary * intensity;
        color = color * i;
        return true;
    }

    virtual ~GouraudShader() {}
};

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

    Camera camera(width, height, Vector3f(0,2,1), 1.0f);
    camera.lookat(Vector3f(0,0,0));

    GouraudShader shader(camera.get_model(), camera.get_viewport(), camera.get_projection(), Vector3f(1,1,1));

    std::cout << "Rendering image from model " << model_filename << " with resolution " << width << "x" << height << std::endl;

    DrawingUtils::rasterize(model, image, camera, shader);

    image.write_to_file(output_filename);
    return 0;
}
