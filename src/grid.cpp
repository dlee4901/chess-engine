#include "grid.hpp"

Grid::Grid(int x, int y)
{
    max_x = x;
    max_y = y;
    for (int i = 0; i < max_x; i++)
    {
        std::vector<Entity> column;
        for (int j = 0; j < max_y; j++)
        {
            Entity entity;
            column.push_back(entity);
        }
        grid.push_back(column);
    }
}

void Grid::add_entity(int x, int y, Entity entity)
{
    grid[x][y] = entity;
}

void Grid::select(int x, int y)
{
    selected_x = x;
    selected_y = y;
}

std::vector< std::pair<int, int> > Grid::transform(std::vector< std::pair<int, int> > &squares, int x, int y)
{
    for (std::pair<int, int> square : squares)
    {
        square.first += x;
        square.second += y;
    }
    return squares;
}

std::vector< std::pair<int, int> > Grid::project(std::vector< std::pair<int, int> > &squares, std::string type, int distance)
{
    for (std::pair<int, int> square : squares)
    {
        int x = square.first;
        int y = square.second;
        int dist = 0;
        if (type == "step")
        {

        }
        else if (type == "orthogonal")
        {
            dist = 0;
            for (int i = x+1; i < max_x; i++)
            {
                if (dist > distance || get_entity(i, y).get_type() != "null") break;
                squares.push_back(std::pair(i, y));
                dist += 1;
            }
            
            dist = 0;
            for (int i = y+1; i < max_y; i++)
            {
                if (dist > distance || get_entity(x, i).get_type() != "null") break;
                squares.push_back(std::pair(x, i));
            }
            
            dist = 0;
            for (int i = x-1; i >= 0; i--)
            {
                if (dist > distance || get_entity(i, y).get_type() != "null") break;
                squares.push_back(std::pair(i, y));
            }
            
            dist = 0;
            for (int i = y-1; i >= 0; i--)
            {
                if (dist > distance || get_entity(x, i).get_type() != "null") break;
                squares.push_back(std::pair(x, i));
            }
        }
        else if (type == "diagonal")
        {
            dist = 0;
            x = square.first + 1;
            y = square.second + 1;
            while (x < max_x && y < max_y)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x += 1;
                y += 1;
            }
            
            dist = 0;
            x = square.first + 1;
            y = square.second - 1;
            while (x < max_x && y >= 0)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x += 1;
                y -= 1;
            }
            
            dist = 0;
            x = square.first - 1;
            y = square.second - 1;
            while (x >= 0 && y >= 0)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x -= 1;
                y -= 1;
            }
            
            dist = 0;
            x = square.first - 1;
            y = square.second + 1;
            while (x >= 0 && y < max_y)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x -= 1;
                y += 1;
            }
        }
        else if (type == "line")
        {
            dist = 0;
            for (int i = x+1; i < max_x; i++)
            {
                if (dist > distance || get_entity(i, y).get_type() != "null") break;
                squares.push_back(std::pair(i, y));
                dist += 1;
            }
            
            dist = 0;
            for (int i = y+1; i < max_y; i++)
            {
                if (dist > distance || get_entity(x, i).get_type() != "null") break;
                squares.push_back(std::pair(x, i));
            }
            
            dist = 0;
            for (int i = x-1; i >= 0; i--)
            {
                if (dist > distance || get_entity(i, y).get_type() != "null") break;
                squares.push_back(std::pair(i, y));
            }
            
            dist = 0;
            for (int i = y-1; i >= 0; i--)
            {
                if (dist > distance || get_entity(x, i).get_type() != "null") break;
                squares.push_back(std::pair(x, i));
            }
            
            dist = 0;
            x = square.first + 1;
            y = square.second + 1;
            while (x < max_x && y < max_y)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x += 1;
                y += 1;
            }
            
            dist = 0;
            x = square.first + 1;
            y = square.second - 1;
            while (x < max_x && y >= 0)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x += 1;
                y -= 1;
            }
            
            dist = 0;
            x = square.first - 1;
            y = square.second - 1;
            while (x >= 0 && y >= 0)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x -= 1;
                y -= 1;
            }
            
            dist = 0;
            x = square.first - 1;
            y = square.second + 1;
            while (x >= 0 && y < max_y)
            {
                if (dist > distance || get_entity(x, y).get_type() != "null") break;
                squares.push_back(std::pair(x, y));
                dist += 1;
                x -= 1;
                y += 1;
            }
        }
    }
    return squares;
}

std::vector< std::pair<int, int> > Grid::get_movement_options(int x, int y)
{
    std::vector< std::pair<int, int> > movement_options;
    Entity piece = grid[x][y]; 
    if (piece.get_type() == "null")
    {
        std::cout << "NULL piece" << std::endl;
        return movement_options;
    }
    movement_options.push_back(std::pair(x, y));
    std::vector<Movement> movements = piece.get_movements();
    for (Movement movement : movements)
    {
        std::string condition = movement.get_condition();
        std::string action = movement.get_action();
        std::string parameters = movement.get_parameters();

        std::unordered_map<std::string, bool> valid_directions = movement.get_valid_directions();
        std::vector<std::string> moves = split(action, " ");
        for (std::string move : moves)
        {
            int distance = 0;
            std::string direction = "";
            for (unsigned int i = 0; i < move.length(); i++)
            {
                if (distance == 0 && isalpha(move[i]))
                {
                    std::string dist = move.substr(0, i);
                    if (dist == "*") { distance = -1; }
                    else             { distance = std::stoi(dist); }
                    direction = move.substr(i);
                    break;
                }
            }
            if (distance < 0) distance = std::max(max_x, max_y);
            if (!valid_directions[direction]) { std::cout << "INVALID DIRECTION: " << direction << std::endl; }
            else if (direction == "N")  { transform(movement_options, 0, distance); }
            else if (direction == "E")  { transform(movement_options, distance, 0); }
            else if (direction == "S")  { transform(movement_options, 0, -distance); }
            else if (direction == "W")  { transform(movement_options, -distance, 0); }
            else if (direction == "NE") { transform(movement_options, distance, distance); }
            else if (direction == "SE") { transform(movement_options, distance, -distance); }
            else if (direction == "SW") { transform(movement_options, -distance, -distance); }
            else if (direction == "NW") { transform(movement_options, -distance, distance); }
            else                        { project(movement_options, direction, distance); }
        }
    }
    return movement_options;
}

Entity Grid::get_entity(int x, int y)
{
    return grid[x][y];
}

void Grid::print_grid()
{
    for (int j = max_y-1; j > -1; j--)
    {
        for (int i = 0; i < max_x; i++)
        {
            Entity entity = get_entity(i, j);
            if (entity.get_type() == "null")
            {
                std::cout << "*\t\t";
            }
            else
            {
                std::cout << entity.get_name() << "\t";
            }
        }
        std::cout << std::endl;
    }
}