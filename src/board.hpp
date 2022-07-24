#include <vector>
#include "piece.hpp"

class Board
{
    std::vector< std::vector<Piece> > board;
    int width;
    int height;

public:
    Board(int width, int height);
};