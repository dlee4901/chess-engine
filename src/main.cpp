#include <string>

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* image = NULL;

bool Init();
bool LoadMedia();
SDL_Surface* LoadSurface(std::string path);
void Close();

void PrintError(char * format, ...);

int main(int argc, char** argv) 
{
    bool quit = false;
    SDL_Event e;
    if (!Init())
    {
        printf("Failed init\n");
    }
    else
    {
        if (!LoadMedia())
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
                SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(image, NULL, surface, &stretchRect);
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    Close();

    return 0;
}


void PrintError(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, format, args);
    //perror(buffer);
    printf("%s: %s\n", buffer, SDL_GetError());
    va_end(args);
}

bool Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        PrintError("SDL could not initialize");
        return false;
    }

    window = SDL_CreateWindow("Test", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        PrintError("Window could not be created");
        return false;
    } 
    
    surface = SDL_GetWindowSurface(window);

    return true;
}

bool LoadMedia()
{
    image = LoadSurface("../data/gfx/hello_world.bmpm");
    if (image == NULL)
    {
        PrintError("LoadSurface failed");
        return false;
    }
    return true;
}

SDL_Surface* LoadSurface(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        PrintError("Image could not be loaded");
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);
        if (optimizedSurface == NULL)
        {
            PrintError("Unable to optimize image %s", path.c_str());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

void Close()
{
    SDL_FreeSurface(image);
    image = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}