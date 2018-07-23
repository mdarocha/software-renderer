#include "camera.h"

void Camera::setup_mat() {
    model.identity();

    double depth = 255;
    viewport.identity();

    viewport[0][3] = screen_w / 2.0f;
    viewport[1][3] = screen_h / 2.0f;
    viewport[2][3] = depth / 2.0f;

    viewport[0][0] = screen_w / 2.0f;
    viewport[1][1] = screen_h / 2.0f;
    viewport[2][2] = depth / 2.0f;

    projection.identity();
    projection[3][2] = -1.0f / c;
}

const Mat4x4f Camera::get_viewport() const {
    return viewport;
}

const Mat4x4f Camera::get_model() const {
    return model;
}

const Mat4x4f Camera::get_projection() const {
    return projection;
}

void Camera::lookat(Vector3f p) {
    Vector3f up(0,1,0);
    Vector3f z = (position - p).normalize();
    Vector3f x = up.cross(z).normalize();
    Vector3f y = z.cross(x).normalize();

    Mat4x4f m, t;
    m.identity();
    t.identity();

    for(int i = 0; i < 3; i++) {
        m[0][i] = x[i];
        m[1][i] = y[i];
        m[2][i] = z[i];
        t[i][3] = -p[i];
    }

    model = m * t;
}
