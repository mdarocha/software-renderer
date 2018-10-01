#pragma once
#include "matrix.h"
#include "math_vector.h"
#include "image_buffer.h"

class Camera {
    private:
        int screen_w, screen_h;
        Mat4x4f viewport;
        Mat4x4f model;
        Mat4x4f projection;
        double c;
        void setup_mat();
    public:
        Vector3f position;
        ImageBuffer<unsigned char> zbuffer;

        Camera(int w, int h, double cam_dist) : screen_w(w), screen_h(h), c(cam_dist), position(), zbuffer(w, h) {setup_mat();};
        Camera(int w, int h, Vector3f pos, double cam_dist) : screen_w(w), screen_h(h), c(cam_dist), position(pos), zbuffer(w, h) {setup_mat();};
        const Mat4x4f get_viewport() const { return viewport; }
        const Mat4x4f get_model() const { return model; }
        const Mat4x4f get_projection() const { return projection; }
        void lookat(Vector3f point);
};
