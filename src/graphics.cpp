#include "graphics.hpp"

Graphics::Graphics()
{
    bool quit = false;
    SDL_Event e;
    if (!init())
    {
        printf("Failed init\n");
    }
    else
    {
        if (!load_media())
        {
            printf("Failed to load media\n");
        }
        else
        {
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                SDL_Rect stretch_rect;
				stretch_rect.x = 0;
				stretch_rect.y = 0;
				stretch_rect.w = SCREEN_WIDTH;
				stretch_rect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(image, NULL, surface, &stretch_rect);
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    close();
}

void Graphics::print_error(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    int length = vsnprintf(buffer, 255, format, args);
    if (length < 0)
    {
        return;
    }
    printf("%s: %s\n", buffer, SDL_GetError());
    va_end(args);
}

bool Graphics::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error("SDL could not initialize");
        return false;
    }

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        print_error("Window could not be created");
        return false;
    }

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        print_error("SDL_image could not initialize");
        return false;
    }
    
    surface = SDL_GetWindowSurface(window);

    return true;
}

bool Graphics::load_media()
{
    image = load_surface("../data/gfx/hello_world.bmp");
    if (image == NULL)
    {
        print_error("LoadSurface failed");
        return false;
    }
    return true;
}

SDL_Surface* Graphics::load_surface(std::string path)
{
    SDL_Surface* optimized_surface = NULL;
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        print_error("Unable to load image %s", path.c_str());
    }
    else
    {
        optimized_surface = SDL_ConvertSurface(loaded_surface, surface->format, 0);
        if (optimized_surface == NULL)
        {
            print_error("Unable to optimize image %s", path.c_str());
        }
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
}

void Graphics::close()
{
    SDL_FreeSurface(image);
    image = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}