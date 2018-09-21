#pragma once
#include "matrix.h"
#include "math_vector.h"
#include "image_buffer.h"

struct GouraudShader : public Shader {
    //uniforms
    Mat4x4f model, viewport, projection;
    Vector3f light_dir;
    ColorBuffer &diffuse;
    //varying
    Vector3f intensity;
    Matrix<double,2,3> uvmat;

    GouraudShader(Mat4x4f m, Mat4x4f v, Mat4x4f p, Vector3f light, ColorBuffer &diff) : model(m), viewport(v), projection(p), light_dir(light.normalize()), diffuse(diff) {};

    virtual Vector4f vertex(Vector3f v, Vector3f normal, Vector2f uv, int n) {
        uvmat.set_column(n, uv);

        intensity[n] = normal*light_dir;
        if(intensity[n] < 0.0f)
            intensity[n] = 0.0f;

        Vector4f vertex = v;
        return viewport * projection * model * vertex;
    }

    virtual bool fragment(DrawingColor &color, Vector3f bary) {
        Vector2f uv = uvmat * bary;
        double i = bary * intensity;

        color = diffuse.get(uv) * i;
        return true;
    }

    virtual ~GouraudShader() {}
};


