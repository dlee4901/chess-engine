#include <SDL.h>
#include <SDL_image.h>

class TextureHandler
{
    std::string filepath;

    SDL_Texture* texture;

public:
    SDL_Texture* load_texture();
};

