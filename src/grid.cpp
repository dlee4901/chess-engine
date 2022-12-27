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

std::vector< std::pair<int, int> > Grid::get_movement_options(int x, int y)
{
    std::vector< std::pair<int, int> > movement_options;
    movement_options.push_back(std::pair(x, y));
    Entity piece = grid[x][y]; 
    std::string name = piece.get_name();
    std::vector<Movement> movements = piece.get_movements();
    for (Movement movement : movements)
    {
        std::string action = movement.get_action();
        std::vector<std::string> moves = split(action, " ");
        for (std::string move : moves)
        {
            int loc_x = x;
            int loc_y = y;
            int distance = 0;
            std::string direction = "";
            for (int i = 0; i < move.length(); i++)
            {
                if (distance == 0 && isalpha(move[i]))
                {
                    std::string dist = move.substr(0, i);
                    if (dist == "*") { distance = -1; }
                    else             { distance = stoi(dist); }
                    direction = move.substr(i);
                    break;
                }
            }

            if (direction == "N")       { transform(movement_options, 0, distance); }
            else if (direction == "E")  { transform(movement_options, distance, 0); }
            else if (direction == "S")  { transform(movement_options, 0, -distance); }
            else if (direction == "W")  { transform(movement_options, -distance, 0); }
            else if (direction == "NE") { transform(movement_options, distance, distance); }
            else if (direction == "SE") { transform(movement_options, distance, -distance); }
            else if (direction == "SW") { transform(movement_options, -distance, -distance); }
            else if (direction == "NW") { transform(movement_options, -distance, distance); }
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
    for (int i = max_x-1; i > -1; i--)
    {
        for (int j = max_y-1; j > -1; j--)
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