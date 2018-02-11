#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "VMList.hpp"
#include "Manager.hpp"

class Parser {
private:
    std::string     _file;
    bool    line_interpret(int line, std::string &lineStr);

public:
    Parser(std::string const &file);
    bool    interpret(void);
    void    execute(Manager &manager);
};

#endif
//ofstream