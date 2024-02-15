#ifndef TASK_HELPERS_HPP
#define TASK_HELPERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

struct Declaration
{
    std::string name;
    std::string short_type = "-";
    std::string value = "-";
    size_t line;
    size_t position;

    Declaration(std::string nm, size_t ln, size_t ps) : name(nm), line(ln), position(ps) {}
    Declaration() = default;
};

std::vector<Declaration> declarations;

std::vector<std::string> split_string(const std::string& line, char delimiter) 
{
    std::vector<std::string> parts;
    std::istringstream iss(line);
    std::string part;

    while (std::getline(iss, part, delimiter)) 
    {
        if (!part.empty()) 
        {
            parts.push_back(part);
        }
    }
    return parts;
}

bool find_var(std::string var_name)
{
    for(int i = 0; i < declarations.size(); ++i)
    {
        if(declarations[i].name == var_name)
        {
            return 1;
        }
    }
    return 0;
}

#endif