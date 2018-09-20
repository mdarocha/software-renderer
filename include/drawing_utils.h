#pragma once

#include "drawing_target.h"
#include "image_buffer.h"
#include "math_vector.h"
#include "triangle.h"
#include "matrix.h"
#include "obj_model.h"
#include "camera.h"

struct Shader {
    Shader() {};
    virtual ~Shader() {};
    virtual Vector4f vertex(Vector3f pos, Vector3f normal, Vector2f uv, int n) = 0;
    virtual bool fragment(DrawingColor &color, Vector3f barycentric) = 0;
};

namespace DrawingUtils {
    void rasterize(OBJModel &model, DrawingTarget &image, Camera &camera, Shader &shader);
    void line(Point2D start, Point2D end, DrawingColor color, DrawingTarget &image);
    void triangle(Triangle2Di triangle, DrawingColor color, DrawingTarget &image);
    void shaded_triangle(Triangle4D &triangle, DrawingColor color, DrawingTarget &image, Camera &camera, Shader &shader);
}
