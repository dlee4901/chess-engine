#include "movement.hpp"

Movement::Movement(std::string condition, std::string action)
{
    this->condition = condition;
    this->action = action;
}

// movement types: step, orthogonal, diagonal, line, N, E, S, W, NE, SE, SW, NW
// rook: 
// *orthogonal
//
// knight: 
// 1N2E 1N2W 2N1E 2N1W 1S2E 1S2W 2S1E 2S1W
//
// bishop: 
// *diagonal
//
// queen: 
// *line
//
// king: 
// 1line
//
// pawn: 
// !has_moved | 1N 2N
// 1NE enemy | 1NE
// 1NW enemy | 1NW
// 1N