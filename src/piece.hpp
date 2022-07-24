#include <string>

class Piece
{
    std::string name;
    std::string type;

public:
    Piece(std::string name, std::string type);
    bool HighlightMoves(int x, int y);
    bool MovePiece(int x, int y);
};