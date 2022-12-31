#ifndef GRID_H
#define GRID_H

#include "entity.hpp"

class Grid
{
    int max_x;
    int max_y;
    std::vector< std::vector<Entity> > grid;
    int selected_x;
    int selected_y;
    
public:
    Grid() {};
    Grid(int x, int y);
    void add_entity(int x, int y, Entity entity);
    void select(int x, int y);

    std::vector< std::pair<int, int> > project(std::vector< std::pair<int, int> > &grid, std::string type, int distance);
    std::vector< std::pair<int, int> > transform(std::vector< std::pair<int, int> > &grid, int x, int y);
    std::vector< std::pair<int, int> > get_movement_options(int x, int y);
    Entity get_entity(int x, int y);
    
    void print_grid();
};

#endif