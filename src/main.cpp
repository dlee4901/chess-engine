#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "grid.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_texture = NULL;

SDL_Surface* g_surface = NULL;
SDL_Surface* g_image = NULL;

bool init();
bool load_media();
SDL_Surface* load_surface(std::string path);
SDL_Texture* load_texture(std::string path);
void close();

void print_error(const char * format, ...);

std::vector<Entity> create_pieces();
Grid create_chess_game(std::vector<Entity> pieces);

int main(int argc, char** argv) 
{
    std::vector<Entity> pieces = create_pieces();
    Grid board = create_chess_game(pieces);
    board.print_grid();

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
				SDL_BlitScaled(g_image, NULL, g_surface, &stretch_rect);
                SDL_UpdateWindowSurface(g_window);
            }
        }
    }
    close();

    return 0;
}

std::vector<Entity> create_pieces()
{
    std::vector<Entity> pieces;

    std::vector<Movement> rook_move{Movement("", "*orthogonal")};
    std::vector<Movement> knight_move{Movement("", "1N2E 1N2W 2N1E 2N1W 1S2E 1S2W 2S1E 2S1W")};
    std::vector<Movement> bishop_move{Movement("", "*diagonal")};
    std::vector<Movement> queen_move{Movement("", "*line")};
    std::vector<Movement> king_move{Movement("", "1line")};
    std::vector<Movement> pawn_move{Movement("!has_moved", "2N"), Movement("1NE enemy", "1NE"), Movement("1NW enemy", "1NW"), Movement("", "1N")};
    
    pieces.push_back(Entity("rook_white", "player1", rook_move));
    pieces.push_back(Entity("knight_white", "player1", knight_move));
    pieces.push_back(Entity("bishop_white", "player1", bishop_move));
    pieces.push_back(Entity("queen_white", "player1", queen_move));
    pieces.push_back(Entity("king_white", "player1", king_move));
    pieces.push_back(Entity("bishop_white", "player1", bishop_move));
    pieces.push_back(Entity("knight_white", "player1", knight_move));
    pieces.push_back(Entity("rook_white", "player1", rook_move));
    for (int i = 0; i < 8; i++)
    {
        pieces.push_back(Entity("pawn_white", "player1", pawn_move));
    }

    pieces.push_back(Entity("rook_black", "player2", rook_move));
    pieces.push_back(Entity("knight_black", "player2", knight_move));
    pieces.push_back(Entity("bishop_black", "player2", bishop_move));
    pieces.push_back(Entity("queen_black", "player2", queen_move));
    pieces.push_back(Entity("king_black", "player2", king_move));
    pieces.push_back(Entity("bishop_black", "player2", bishop_move));
    pieces.push_back(Entity("knight_black", "player2", knight_move));
    pieces.push_back(Entity("rook_black", "player2", rook_move));
    for (int i = 0; i < 8; i++)
    {
        pieces.push_back(Entity("pawn_black", "player2", pawn_move));
    }

    return pieces;
}

Grid create_chess_game(std::vector<Entity> pieces)
{
    Grid board(8, 8);
    
    // white non-pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(0, i, &pieces[i]);
    }
    // white pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(1, i, &pieces[i+8]);
    }
    // black non-pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(7, i, &pieces[i+16]);
    }
    // black pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(6, i, &pieces[i+24]);
    }

    return board;
}

void print_error(const char* format, ...)
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

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error("SDL could not initialize");
        return false;
    }

    g_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
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
    
    g_surface = SDL_GetWindowSurface(g_window);

    return true;
}

bool load_media()
{
    g_image = load_surface("../data/gfx/hello_world.bmp");
    if (g_image == NULL)
    {
        print_error("LoadSurface failed");
        return false;
    }
    return true;
}

SDL_Surface* load_surface(std::string path)
{
    SDL_Surface* optimized_surface = NULL;
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        print_error("Unable to load image %s", path.c_str());
    }
    else
    {
        optimized_surface = SDL_ConvertSurface(loaded_surface, g_surface->format, 0);
        if (optimized_surface == NULL)
        {
            print_error("Unable to optimize image %s", path.c_str());
        }
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
}

void close()
{
    SDL_FreeSurface(g_image);
    g_image = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    SDL_Quit();
}