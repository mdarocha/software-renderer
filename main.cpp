#include <iostream>
#include <fstream>
#include "ppm_image.h"
#include "obj_model.h"
#include "drawing_utils.h"

int main() {
    PPMImage image(1000,1000);

    PPMColor white = {255,255,255};

    OBJModel model("../teapot.obj");

    int nfaces = model.get_face_count();
    Vector3f v1, v2, v3;
    for(int i = 0; i < nfaces; i++) {
        v1 = model.get_face_vertex(i, 0);
        v2 = model.get_face_vertex(i, 1);
        v3 = model.get_face_vertex(i, 2);

        DrawingUtils::triangle(Point2D{(int)v1.x,(int)v1.y},Point2D{(int)v2.x,(int)v2.y},Point2D{(int)v3.x,(int)v3.y},white,image);
    }

    image.write_to_file("test.ppm");
}
