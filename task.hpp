#include "task_helpers.hpp"

void write_to_res(Declaration ob,std::ofstream& result_file);

void write()
{
    std::ifstream input_file("text.txt");
    std::ofstream result_file("result.txt");
    //std::ofstream type_info_file("typeInfo.txt");
    std::map<std::string, std::string> values;

    if (!input_file.is_open() || !result_file.is_open())
    {
        std::cerr << "Error opening files!" << std::endl;
        return exit(-1);
    }

    result_file << std::setw(12) << std::left << "Type"
                << std::setw(15) << std::left << "Value"
                << std::setw(15) << std::left << "Name"
                << std::setw(15) << std::left << "Line"
                << "Position" << std::endl;

    std::string line;
    size_t current_line = 0;

    while (std::getline(input_file, line))
    {
        if (!line.empty())
        {
            std::vector<std::string> tokens = split_string(line, ';');
            for(size_t i = 0 ; i < tokens.size(); ++i)
            {
                std::vector<std::string> decs =  split_string(tokens[i], ' ');
                if(decs.size() == 1)
                {
                    if(!find_var(decs[0]))
                    {
                        Declaration ob(decs[0], current_line, i);
                        write_to_res(ob,result_file);
                    }

                    else
                    {
                        for(size_t j = 0; j < declarations.size(); ++j)
                        {
                            if(decs[0] == declarations[j].name)
                            {
                                write_to_res(declarations[j],result_file);
                            }
                        }
                    }            
                }

                else
                {
                    Declaration ob;
                    if(decs.size() > 3 && (decs[decs.size() - 2] == "="))
                    {
                        ob.name = decs[decs.size() - 3];
                        ob.value = decs[decs.size() - 1];
                        ob.short_type = "";
                        for(size_t k = 0; k < decs.size() - 3; ++k)
                        {
                            ob.short_type += decs[k][0];
                        }
                        ob.line = current_line;
                        ob.position = i;
                    }

                    else
                    {
                        ob.name = decs[decs.size() - 1];
                        ob.value = "GARBAGE";
                        ob.short_type = "";
                        for(size_t z = 0; z < decs.size() - 1; ++z)
                        {
                            ob.short_type += decs[z][0];
                        }
                        ob.line = current_line;
                        ob.position = i;
                    }
                    declarations.push_back(ob);
                }
            }
        }
        current_line++;
    }

    input_file.close();
    result_file.close();
}

void write_to_res(Declaration ob , std::ofstream& result_file)
{
    result_file << std::setw(12) << std::left << ob.short_type
                << std::setw(15) << std::left << ob.value
                << std::setw(15) << std::left << ob.name
                << std::setw(15) << std::left << ob.line
                << std::setw(15) << std::left<< ob.position 
                << std::endl;
}