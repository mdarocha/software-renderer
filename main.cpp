#include <iostream>
#include <fstream>
#include "ppm_image.h"
#include "obj_model.h"
#include "drawing_utils.h"

int main() {
    int width, height;
    width = height = 1000;

    PPMImage image(width, height);
    PPMColor white = {255,255,255};

    OBJModel model("../teapot.obj");
    model.normalize_model_scale();

    int nfaces = model.get_face_count();
    Vector3f v[3];
    Point2D p[3];
    for(int i = 0; i < nfaces; i++) {
        v[0] = model.get_face_vertex(i, 0);
        v[1] = model.get_face_vertex(i, 1);
        v[2] = model.get_face_vertex(i, 2);

        for(int j = 0; j < 3; j++) {
            p[j].x = (int) ((v[j].x + 1.0f) * width / 2.0f);
            p[j].y = (int) ((v[j].y + 1.0f) * height / 2.0f);
        }

        DrawingUtils::triangle(p[0], p[1], p[2], white, image);
    }

    image.write_to_file("test.ppm");
}
