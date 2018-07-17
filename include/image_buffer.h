#pragma once

#include <cstring>

class ImageBuffer {
    protected:
        unsigned char* data;
        int width, height;
        size_t pixel_size;

    public:
        ImageBuffer(int w, int h, size_t pixel_size);
        ~ImageBuffer();
        bool set(int x, int y, const unsigned char* data);
        const unsigned char* get(int x, int y) const;
        int get_width() const;
        int get_height() const;
        const unsigned char* get_data() const;

        template<class T>
        static ImageBuffer create(int w, int h) {
            return ImageBuffer(w, h, sizeof(T));
        }

        template<class T>
        bool set(int x, int y, const T &input_data) {
            set(x, y, (const unsigned char*) &input_data);
        }

        template<class T>
        const T& get(int x, int y) const {
            return (T&) *get(x, y);
        }
};
