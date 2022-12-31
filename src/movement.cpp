#include "movement.hpp"

Movement::Movement(std::string condition, std::string action)
{
    this->condition = condition;
    this->action = action;
    parameters = "";
}

Movement::Movement(std::string condition, std::string action, std::string parameters)
{
    this->condition = condition;
    this->action = action;
    this->parameters = parameters;
}

std::string Movement::get_condition()
{
    return condition;
}

std::string Movement::get_action()
{
    return action;
}

std::string Movement::get_parameters()
{
    return parameters;
}

std::unordered_map<std::string, bool> Movement::get_valid_directions()
{
    std::vector<std::string> valid_directions {"step", "orthogonal", "diagonal", "line", "N", "E", "S", "W", "NE", "SE", "SW", "NW"};
    std::unordered_map<std::string, bool> map_valid_directions;
    for (std::string i : valid_directions)
    {
        map_valid_directions[i] = true;
    }
    return map_valid_directions;
}

// movement types: step, orthogonal, diagonal, line, N, E, S, W, NE, SE, SW, NW
// rook: 
// *orthogonal
//
// knight: 
// 1N 2E 
// 1N 2W
// 2N 1E
// 2N 1W 
// 1S 2E 
// 1S 2W 
// 2S 1E 
// 2S 1W
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