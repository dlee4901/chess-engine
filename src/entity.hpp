#include <string>
#include <unordered_map>
#include <any>
#include <vector>

#include "movement.hpp"

class Entity
{
    std::string name;
    std::string controller;
    std::vector<Movement> movement;
    std::unordered_map<std::string, std::any> state;

public:
    Entity(std::string name, std::string controller, std::vector<Movement> movement);
    Entity(std::string name, std::string controller, std::vector<Movement> movement, std::unordered_map<std::string, std::any> state);
    void init_state();
    void change_state(std::string key, std::any value);

    std::string get_name() {return name;}
    std::unordered_map<std::string, std::any> get_state() {return state;}
    std::vector<Movement> get_movement() {return movement;}
};

