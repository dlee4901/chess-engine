#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "util.hpp"

class Movement
{
    std::string condition;
    std::string action;
    std::string parameters;
public:
    Movement(std::string condition, std::string action);
    Movement(std::string condition, std::string action, std::string parameters);

    std::string get_condition();
    std::string get_action();
    std::string get_parameters();
};

#endif