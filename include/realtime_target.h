#pragma once
#include <SDL2/SDL.h>
#include "drawing_target.h"

class RealtimeTarget : public DrawingTarget {
    int width, height;
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    void handle_event(SDL_Event *event);

    public:
        RealtimeTarget(int w, int h);

        virtual ~RealtimeTarget();

        virtual int get_height() const { return height; }
        virtual int get_width() const { return width; }

        virtual void set(int x, int y, DrawingColor color);

        bool is_running() { return running; }
        void start();
        void loop();
};
