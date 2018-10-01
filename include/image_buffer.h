#pragma once
#include <memory>
#include <cstring>
#include <cmath>
#include "drawing_target.h"
#include "math_vector.h"

template<class T>
class ImageBuffer {
    protected:
        std::unique_ptr<T[]> data;
        int width, height;

    public:
        ImageBuffer(int w, int h) : data(new T[w * h]), width(w), height(h) {}
        ImageBuffer(int w, int h, T *input) : data(input), width(w), height(h) {}

        ~ImageBuffer() {}

        void set(int x, int y, T input) {
            data[x + y * width] = input;
        };

        T get(int x, int y) const {
            return data[x + y * width];
        };

        T get(Vector2f uv) const {
            int x = std::abs(int(uv.x * width) % width);
            int y = std::abs(int(uv.y * height) % height);

            return data[x + y * width];
        }

        void clear() {
            std::memset(data.get(), 0, sizeof(T) * width * height);
        }

        int get_width() const { return width; }
        int get_height() const { return height; }

        const std::unique_ptr<T[]>& get_data() const { return data; }

        ImageBuffer(const ImageBuffer& img) : data(new T[img.width * img.height]), width(img.width), height(img.height) {
            std::memcpy(data.get(), img.data.get(), sizeof(T) * width * height);
        }
};

typedef ImageBuffer<DrawingColor> ColorBuffer;
