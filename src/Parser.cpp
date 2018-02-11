#include <iostream>
#include <fstream>
#include "Parser.hpp"

Parser::Parser(std::string const &file):
    _file(file)
{}

bool    Parser::line_interpret(int line, std::string &lineStr)
{
    std::cout << "Line " << line << " : " << lineStr << std::endl;
    return (true);
}

bool    Parser::interpret(void)
{
    std::string inStr;
    int line = 0;

    if (_file.length() <= 0)
    {
        while (std::getline(std::cin, inStr))
        {
            if (inStr == std::string(";;"))
                break;
            if (!line_interpret(line++, inStr))
                std::cerr << "" << std::endl;
        }
    }
    else
    {
        std::ifstream file(_file, std::ifstream::in);
        if (file.is_open())
        {
            while (std::getline(file, inStr))
                if (!line_interpret(line++, inStr))
                    std::cerr << "" << std::endl;
        }
        else
        {
            std::cerr << "File not found! " << _file << std::endl;
            return (false);
        }
    }
    return (true);
}

void    Parser::execute(Manager &manager)
{

}
