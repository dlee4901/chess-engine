#include "util.hpp"

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> out;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        out.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    return out;
}