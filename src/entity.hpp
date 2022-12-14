#ifndef ENTITY_H
#define ENTITY_H

#include "movement.hpp"

class Entity
{
    std::string type;
    std::string name;
    std::string controller;
    std::vector<Movement> movements;
    std::unordered_map<std::string, std::any> state;

public:
    Entity();
    Entity(std::string type, std::string name, std::string controller, std::vector<Movement> movements);
    Entity(std::string type, std::string name, std::string controller, std::vector<Movement> movements, std::unordered_map<std::string, std::any> state);
    void init_state();
    void change_state(std::string key, std::any value);

    std::string get_type();
    std::string get_name();
    std::unordered_map<std::string, std::any> get_state();
    std::vector<Movement> get_movements();
};

#endif