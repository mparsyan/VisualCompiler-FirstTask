#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

struct Declaration
{
    std::string name;
    std::string type;
    std::string value;
    size_t line;
    size_t position;
};

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

int main()
{
    std::ifstream input_file("text.txt");
    std::ofstream result_file("result.txt");
    std::ofstream type_info_file("typeInfo.txt");

    std::vector<Declaration> declarations;
    std::map<std::string, std::string> values;

    if (!input_file.is_open() || !result_file.is_open() || !type_info_file.is_open())
    {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    std::string line;
    size_t current_line = 0;

    while (std::getline(input_file, line))
    {
        current_line++;

        if (!line.empty())
        {
            std::vector<std::string> tokens = split_string(line, ';');
            
            for (const auto& token : tokens)
            {
                std::istringstream iss(token);
                std::string word;
                while (iss >> word)
                {
                    Declaration decl;
                    decl.line = current_line;
                    decl.position = iss.tellg();

                    if (word == "int" || word == "double" || word == "char" || word == "float" || word == "short" || word == "bool") 
                    {
                        decl.type = word;
                        iss >> decl.name;
                        declarations.push_back(decl);
                    }
                    else if (word == "const")
                    {
                        iss >> decl.type;
                        if (iss >> decl.name)
                        {
                            // Check if there's an equal sign indicating a value
                            if (iss >> word && word == "=")
                            {
                                iss >> decl.value;
                                values[decl.name] = decl.value;
                            }
                            declarations.push_back(decl);
                        }
                    }
                }
            }
        }
    }

    result_file << std::setw(12) << std::left << "Type"
                << std::setw(15) << std::left << "Value"
                << std::setw(15) << std::left << "Name"
                << std::setw(15) << std::left << "Line"
                << "Position" << std::endl;

    type_info_file << std::setw(12) << std::left << "Type"
                   << std::setw(15) << std::left << "Value"
                   << std::setw(15) << std::left << "Name" << std::endl;

    for (const auto& decl : declarations)
    {
        result_file << std::setw(12) << std::left << decl.type
                    << std::setw(15) << std::left << (values.count(decl.name) ? values[decl.name] : "GARBAGE")
                    << std::setw(15) << std::left << decl.name
                    << std::setw(15) << std::left << decl.line
                    << decl.position << std::endl;

        type_info_file << std::setw(12) << std::left << decl.type
                       << std::setw(15) << std::left << (values.count(decl.name) ? values[decl.name] : "")
                       << std::setw(15) << std::left << decl.name << std::endl;
    }

    input_file.close();
    result_file.close();
    type_info_file.close();

    return 0;
}
