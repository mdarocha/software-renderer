#pragma once

struct DrawingColor {
    unsigned char r, g, b;
};

template<class T>
DrawingColor operator *(const DrawingColor &left, const T &right) {
    return { left.r * right, left.g * right, left.b * right };
}

class DrawingTarget {
    public:
        DrawingTarget() {};
        virtual ~DrawingTarget() {};

        virtual void set(int x, int y, DrawingColor color) = 0;

        virtual int get_height() const = 0;
        virtual int get_width() const = 0;
};
