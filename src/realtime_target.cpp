#include <SDL2/SDL.h>
#include "realtime_target.h";

RealtimeTarget::RealtimeTarget(int w, int h) : width(w), height(h), running(false) {}

RealtimeTarget::~RealtimeTarget() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RealtimeTarget::set(int x, int y, DrawingColor color) {

}

void RealtimeTarget::handle_event(SDL_Event *event) {
    if(event->type == SDL_QUIT)
        running = false;
}

void RealtimeTarget::start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    running = true;
}

void RealtimeTarget::loop() {
    while(SDL_PollEvent(&event))
        handle_event(&event);

    SDL_RenderPresent(renderer);
}
