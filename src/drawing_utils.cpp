#include "drawing_utils.h"

namespace DrawingUtils {
    void rasterize(OBJModel &model, PPMImage &image, Camera &camera) {
        int nfaces = model.get_face_count();

        ImageBuffer depth_buffer = ImageBuffer::create<double>(image.get_width(), image.get_height());

        Vector3f light_direction(0,0,1);
        double intensity;

        Triangle4D v;
        Triangle3D n;

        for(int i = 0; i < nfaces; i++) {
            v = model.get_face_vertices(i);

            n = model.get_face_normals(i);

            intensity = 0;
            for(int k = 0; k < 3; k++) {
                intensity += n[k] * light_direction;
            }
            intensity /= 3;

            if(intensity > 0) {
                if(intensity > 1)
                    intensity = 1;
                v = camera.get_projection() * (camera.get_model() * v);

                shaded_triangle(v, PPMColor{(unsigned char)(intensity*255),(unsigned char)(intensity*255),(unsigned char)(intensity*255)}, image, depth_buffer, camera);
            }
        }

        /*double depth;
        for(int x = 0; x < image.get_width(); x++) {
            for(int y = 0; y < image.get_height(); y++) {
                depth = depth_buffer.get<double>(x, y) / 2;
                image.set(x, y, PPMColor{(unsigned char)(depth*255),(unsigned char)(depth*255),(unsigned char)(depth*255)});
            }
        }*/
    }

    void line(Point2D start, Point2D end, PPMColor color, PPMImage &image) {
        bool is_steep = false;
        //if we are drawing a steep line, transpose the image
        if(std::abs(start.x - end.x) < std::abs(start.y - end.y)) {
            std::swap(start.x, start.y);
            std::swap(end.x, end.y);
            is_steep = true;
        }

        //make sure start is always to the left of end
        if(start.x > end.x) {
            std::swap(start, end);
        }

        int dx = end.x - start.x;
        int dy = end.y - start.y;

        int derror = std::abs(dy) * 2; //equal to abs(dy/dx) * dx * 2
        int error = 0;

        int y = start.y;

        for(int x = start.x; x < end.x; x++) {
            if(is_steep) {
                image.set(y, x, color);
            } else {
                image.set(x, y, color);
            }

            error += derror;
            if(error > dx) {
                y += (end.y > start.y ? 1 : -1);
                error -= dx * 2;
            }
        }
    }

    void triangle(Triangle2Di t, PPMColor color, PPMImage &image) {
        line(t[0], t[1], color, image);
        line(t[1], t[2], color, image);
        line(t[2], t[0], color, image);
    }

    void shaded_triangle(Triangle4D &triangle, PPMColor color, PPMImage &image, ImageBuffer &depth_buffer, Camera &camera) {
        Triangle4D triangle_viewport = camera.get_viewport() * triangle;
        Triangle3D triangle_screen = triangle_viewport;
        triangle_screen.round_down();

        Vector3f p;
        Vector3f a;
        Rect<Vector3f> bounding_box = triangle_screen.get_bounding_box();
        for(p.x = bounding_box.b.x; p.x < bounding_box.a.x; p.x++) {
            for(p.y = bounding_box.b.y; p.y < bounding_box.a.y; p.y++) {
                if(p.x < 0 || p.y < 0 || p.x > image.get_width() || p.y > image.get_height())
                    continue;

                a = triangle_screen.get_barycentric_coords(p);

                if(a.x < 0 || a.y < 0 || a.z < 0)
                    continue;

                p.z = 0;
                for(int i = 0; i < 3; i++)
                    p.z += triangle_screen[i].z * a[i];

                if(depth_buffer.get<double>((int)p.x, (int)p.y) < p.z) {
                    depth_buffer.set<double>((int)p.x, (int)p.y, p.z);
                    image.set(p.x, p.y, color);
                }
            }
        }
    }
}
