#pragma once
#include <memory>

template<class T>
class ImageBuffer {
    protected:
        std::unique_ptr<T[]> data;
        int width, height;

    public:
        ImageBuffer() : data(nullptr), width(), height() {}

        ImageBuffer(int w, int h) : data(new T[w * h]), width(w), height(h) {}

        ~ImageBuffer() {}

        void set(int x, int y, T input) {
            data[x + y * width] = input;
        };

        T get(int x, int y) const {
            return data[x + y * width];
        };

        int get_width() const { return width; }
        int get_height() const { return height; }

        const std::unique_ptr<T[]>& get_data() const { return data; }
};
