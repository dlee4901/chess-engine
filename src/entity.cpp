#include "entity.hpp"

Entity::Entity(std::string type, std::string name, std::string controller, std::vector<Movement> movements)
{
    this->type = type;
    this->name = name;
    this->controller = controller;
    this->movements = movements;
    init_state();
}

Entity::Entity(std::string type, std::string name, std::string controller, std::vector<Movement> movements, std::unordered_map<std::string, std::any> state)
{
    this->type = type;
    this->name = name;
    this->controller = controller;
    this->movements = movements;
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

std::string Entity::get_type()
{
    return type;
}

std::string Entity::get_name()
{
    return name;
}

std::unordered_map<std::string, std::any> Entity::get_state()
{
    return state;
}

std::vector<Movement> Entity::get_movements()
{
    return movements;
}