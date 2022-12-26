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

std::set< std::pair<int, int> > Grid::get_movement_options(int x, int y)
{
    std::set< std::pair<int, int> > movement_options;
    Entity piece = grid[x][y]; 
    std::string name = piece.get_name();
    std::vector<Movement> movements = piece.get_movements();
    for (Movement movement : movements)
    {
        std::string action = movement.get_action();
        std::vector<std::string> moves = split(action, " ");
        for (std::string move : moves)
        {
            int dist = -1;
            
            for (int i = 0; i < move.length(); i++)
            {
                if (dist < 0 && !isdigit(move[i]))
                {
                    dist = stoi(move.substr(0, i));
                }

            }
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