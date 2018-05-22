#include "drawing_utils.h"

namespace DrawingUtils {
    void rasterize(OBJModel &model, PPMImage &image) {
        int nfaces = model.get_face_count();

        Vector3f light_direction(0,0,1);
        double intensity;

        Triangle<Vector3f> v;
        Triangle<Vector3f> n;

        Triangle<Point2D> t;
        for(int i = 0; i < nfaces; i++) {
            v = model.get_face_vertices(i);
            n = model.get_face_normals(i);

            for(int j = 0; j < 3; j++) {
                t[j].x = (int) ((v[j].x + 1.0f) * image.get_width() / 2.0f);
                t[j].y = (int) ((v[j].y + 1.0f) * image.get_height() / 2.0f);
            }

            intensity = 0;
            for(int k = 0; k < 3; k++) {
                intensity += n[k] * light_direction;
            }
            intensity /= 3;

            if(intensity > 0) {
                if(intensity > 1)
                    intensity = 1;
                filled_triangle(t, PPMColor{(unsigned char)(intensity*255),(unsigned char)(intensity*255),(unsigned char)(intensity*255)}, image);
            }
        }
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

    void triangle(Triangle<Point2D> t, PPMColor color, PPMImage &image) {
        line(t[0], t[1], color, image);
        line(t[1], t[2], color, image);
        line(t[2], t[0], color, image);
    }

    void filled_triangle(Triangle<Point2D> t, PPMColor color, PPMImage &image) {
        Point2D bounding_box_min;
        Point2D bounding_box_max;

        bounding_box_max.x = std::max(t[0].x, std::max(t[1].x, t[2].x));
        bounding_box_max.y = std::max(t[0].y, std::max(t[1].y, t[2].y));

        bounding_box_min.x = std::min(t[0].x, std::min(t[1].x, t[2].x));
        bounding_box_min.y = std::min(t[0].y, std::min(t[1].y, t[2].y));

        Point2D p;
        Vector3f a;
        for(p.x = bounding_box_min.x; p.x < bounding_box_max.x; p.x++) {
            for(p.y = bounding_box_min.y; p.y < bounding_box_max.y; p.y++) {
                a = t.get_barycentric_coords(p);

                if(a.x < 0 || a.y < 0 || a.z < 0)
                    continue;

                image.set(p.x, p.y, color);
            }
        }
    }
}
