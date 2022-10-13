#include "entity.hpp"

Entity::Entity(std::string name, std::string controller, std::vector<Movement> movement)
{
    this->name = name;
    this->controller = controller;
    this->movement = movement;
    init_state();
}

Entity::Entity(std::string name, std::string controller, std::vector<Movement> movement, std::unordered_map<std::string, std::any> state)
{
    this->name = name;
    this->controller = controller;
    this->movement = movement;
    this->state = state;
}

void Entity::init_state()
{
    state["in_check"] = false;
    state["has_moved"] = false;
    state["just_moved"] = false;

    if (controller == "player2")
    {
        state["facing"] = "S";
    }
    else
    {
        state["facing"] = "N";
    }
}

void Entity::change_state(std::string key, std::any value)
{
    state[key] = value;
}