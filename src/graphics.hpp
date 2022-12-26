#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "util.hpp"

class Graphics
{
    SDL_Surface* surface;
    SDL_Surface* image;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
public:
    Graphics();
    bool init();
    bool load_media();
    SDL_Surface* load_surface(std::string path);
    SDL_Texture* load_texture(std::string path);
    void close();
    void print_error(const char * format, ...);
};

#endif