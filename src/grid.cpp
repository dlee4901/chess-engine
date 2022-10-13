#include "grid.hpp"

Grid::Grid(int x, int y)
{
    max_x = x;
    max_y = y;
    std::vector<Entity*> column(8, nullptr);
    for (int i = 0; i < max_y; i++)
    {
        grid.push_back(column);
    }
}

Grid::~Grid()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            delete grid[i][j];
        }
    }
}

void Grid::add_entity(int x, int y, Entity* entity)
{
    grid[x][y] = entity;
}

// std::vector< std::pair<int, int> > Grid::get_movement_options(int x, int y)
// {
//     Entity* piece = grid[x][y]; 
//     std::vector<Movement> movement = piece->get_movement();
// }

Entity* Grid::get_entity(int x, int y)
{
    return grid[x][y];
}

void Grid::print_grid()
{
    for (int i = 0; i < max_x; i++)
    {
        for (int j = 0; j < max_y; j++)
        {
            Entity* entity = get_entity(i, j);
            if (entity == nullptr)
            {
                std::cout << "*\t\t";
            }
            else
            {
                std::cout << entity->get_name() << "\t";
            }
        }
        std::cout << std::endl;
    }
}