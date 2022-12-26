#include "graphics.hpp"
#include "grid.hpp"

std::vector<Entity> create_pieces();
Grid create_chess_game(std::vector<Entity> pieces);

int main() 
{
    std::vector<Entity> pieces = create_pieces();
    Grid board = create_chess_game(pieces);
    board.print_grid();

    //Graphics test;

    return 0;
}

std::vector<Entity> create_pieces()
{
    std::vector<Entity> pieces;

    std::vector<Movement> rook_move{Movement("", "*orthogonal")};
    std::vector<Movement> knight_move{Movement("", "1N 2E", "leap"), Movement("", "1N 2W", "leap"), Movement("", "2N 1E", "leap"), Movement("", "2N 1W", "leap"),
        Movement("", "1S 2E", "leap"), Movement("", "1S 2W", "leap"), Movement("", "2S 1E", "leap"), Movement("", "2S 1W", "leap")};
    std::vector<Movement> bishop_move{Movement("", "*diagonal")};
    std::vector<Movement> queen_move{Movement("", "*line")};
    std::vector<Movement> king_move{Movement("", "1line")};
    std::vector<Movement> pawn_move{Movement("!has_moved", "2N"), Movement("1NE enemy", "1NE"), Movement("1NW enemy", "1NW"), Movement("", "1N")};
    
    pieces.push_back(Entity("piece", "rook_white", "player1", rook_move));
    pieces.push_back(Entity("piece", "knight_white", "player1", knight_move));
    pieces.push_back(Entity("piece", "bishop_white", "player1", bishop_move));
    pieces.push_back(Entity("piece", "king_white", "player1", king_move));
    pieces.push_back(Entity("piece", "queen_white", "player1", queen_move));
    pieces.push_back(Entity("piece", "bishop_white", "player1", bishop_move));
    pieces.push_back(Entity("piece", "knight_white", "player1", knight_move));
    pieces.push_back(Entity("piece", "rook_white", "player1", rook_move));
    for (int i = 0; i < 8; i++)
    {
        pieces.push_back(Entity("piece", "pawn_white", "player1", pawn_move));
    }

    pieces.push_back(Entity("piece", "rook_black", "player2", rook_move));
    pieces.push_back(Entity("piece", "knight_black", "player2", knight_move));
    pieces.push_back(Entity("piece", "bishop_black", "player2", bishop_move));
    pieces.push_back(Entity("piece", "king_black", "player2", king_move));
    pieces.push_back(Entity("piece", "queen_black", "player2", queen_move));
    pieces.push_back(Entity("piece", "bishop_black", "player2", bishop_move));
    pieces.push_back(Entity("piece", "knight_black", "player2", knight_move));
    pieces.push_back(Entity("piece", "rook_black", "player2", rook_move));
    for (int i = 0; i < 8; i++)
    {
        pieces.push_back(Entity("piece", "pawn_black", "player2", pawn_move));
    }

    return pieces;
}

Grid create_chess_game(std::vector<Entity> pieces)
{
    Grid board(8, 8);
    
    // white non-pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(0, i, pieces[i]);
    }
    // white pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(1, i, pieces[i+8]);
    }
    // black non-pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(7, i, pieces[i+16]);
    }
    // black pawns
    for (int i = 0; i < 8; i++)
    {
        board.add_entity(6, i, pieces[i+24]);
    }

    return board;
}