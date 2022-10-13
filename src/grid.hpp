#include <vector>
#include <iostream>

#include "entity.hpp"

class Grid
{
    int max_x;
    int max_y;
    std::vector< std::vector<Entity*> > grid;
    
public:
    Grid(int x, int y);
    ~Grid();
    void add_entity(int x, int y, Entity* entity);

    Entity* get_entity(int x, int y);

    std::vector< std::pair<int, int> > get_movement_options(int x, int y);

    void print_grid();
};