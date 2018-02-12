#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Exception.hpp"
#include "Parser.hpp"
#include "Factory.hpp"

Parser::Parser(std::string const &file):
    _file(file)
{}

std::string     Parser::trim(std::string const &str)
{
    size_t startpos = str.find_first_not_of(" \t");
    size_t endpos = str.find_last_not_of(" \t");
    if(std::string::npos != endpos)
        return (str.substr(startpos, endpos - startpos + 1));
    else
        return (std::string());
}

void            Parser::replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void                    Parser::norme(std::string &str)
{
    replaceAll(str, "(", "( ");
    replaceAll(str, ")", " )");
}

VMList<std::string>      Parser::split(std::string const &str)
{
    VMList<std::string> list;
    std::string out;
    std::istringstream   iss(str);
    while (getline(iss, out, ' '))
    {
        if (out.length())
            list.push(out);
    }
    return (list);
}

bool                    Parser::arg_type_test(std::string const &arg)
{
    if (arg == std::string("int8(") || arg == std::string("int16(")
        || arg == std::string("int32(") || arg == std::string("float(")
        || arg == std::string("double("))
        return (true);
    return (false);
}

bool                    Parser::arg_digit_test(std::string const &type, std::string const &arg)
{
    if (type == std::string("int8(") || type == std::string("int16(") || type == std::string("int32("))
    {
        return (std::regex_match(arg, std::regex("^[+-]?([0-9]+)?$")));
    }
    else if (type == std::string("float(") || type == std::string("double("))
    {
        return (std::regex_match(arg, std::regex("^[+-]?([0-9]*[.])?[0-9]+$")));
    }
    return (false);
}

bool                    Parser::arg_end_test(std::string const &arg)
{
    if (arg != std::string(")"))
        return(false);
    return (true);
}

eOperandType			Parser::arg_get_type(std::string const &type)
{
    if (type == std::string("int8("))
        return (INT8);
    else if (type == std::string("int16("))
        return (INT16);
    else if (type == std::string("int32("))
        return (INT32);
    else if (type == std::string("float("))
        return (FLOAT);
    else if (type == std::string("double("))
        return (DOUBLE);
     return (INT8);
}

int    Parser::line_interpret(int line, std::string &lineStr)
{
    std::string cmd = trim(lineStr.substr(0, lineStr.find(";")));
    if (cmd.length() > 0)
    {
        norme(cmd);
        VMList<std::string> cmdList = split(cmd);
        if (cmdList.size() > 0)
        {
            if (cmdList[0] == "push")
            {
                if (cmdList.size() != 4)
                    return (1);
                if (!arg_type_test(cmdList[1]) || !arg_digit_test(cmdList[1], cmdList[2]) || !arg_end_test(cmdList[3]))
                    return (3);
                _instruction.push(Instruction(PUSH, arg_get_type(cmdList[1]), cmdList[2]));
            }
            else if (cmdList[0] == "pop")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(POP));
            }
            else if (cmdList[0] == "dump")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(DUMP));
            }
            else if (cmdList[0] == "assert")
            {
                if (cmdList.size() != 4)
                    return (1);
                if (!arg_type_test(cmdList[1]) || !arg_digit_test(cmdList[1], cmdList[2]) || !arg_end_test(cmdList[3]))
                    return (3);
                std::string type = cmdList[1].substr(0, cmdList[1].find("("));
                _instruction.push(Instruction(ASSERT, arg_get_type(cmdList[1]), cmdList[2]));
            }
            else if (cmdList[0] == "add")
            {
                if (cmdList.size() != 1)
                    return (1);
                    _instruction.push(Instruction(ADD));
            }
            else if (cmdList[0] == "sub")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(SUB));
            }
            else if (cmdList[0] == "mul")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(MUL));
            }
            else if (cmdList[0] == "div")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(DIV));
            }
            else if (cmdList[0] == "mod")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(MOD));
            }
            else if (cmdList[0] == "print")
            {
                if (cmdList.size() != 1)
                    return (1);
                _instruction.push(Instruction(PRINT));
            }
            else if (cmdList[0] == "exit")
            {
                run = false;
            }
            else
            {
                std::cerr << "Error Instruction not Found:" << std::endl;
                std::cerr << "=> Line: " << line << std::endl;
                std::cerr << "=> " << lineStr << std::endl;
                return (2);
            }
        }
    }
    return (0);
}

void    Parser::lines_interpret(std::ifstream *ifs, bool in)
{
    std::string inStr;
    int line = 0;
    run = true;
    int throwError = 0;
    int throwErrorLine = 0;
    int error;
    while (std::getline(in ? std::cin : *ifs, inStr) && run)
    {
        if (inStr == std::string(";;") && in)
            break;
        if ((error = line_interpret(line++, inStr)) == 1)
        {
            std::cerr << "Error Syntax:" << std::endl;
            std::cerr << "=> Line: " << line << std::endl;
            std::cerr << "=> " << inStr << std::endl;
            throwError = throwError ? throwError : 1; 
        }
        else if (error == 2)
            throwError = throwError ? throwError : 2;
        else if (error == 3)
        {
            std::cerr << "Error Syntax, the argument is not valid:" << std::endl;
            std::cerr << "Valid Type: int8(...), int16(...), int32(...), float(...) and double(...)" << std::endl;
            std::cerr << "=> Line: " << line << std::endl;
            std::cerr << "=> " << inStr << std::endl;
            throwError = throwError ? throwError : 3;
        }
        if (throwError)
            throwErrorLine = throwErrorLine ? throwErrorLine : line;
    }
    if (throwError == 1 || throwError == 3)
        throw RuntimeException("Syntax Error!");
    if (throwError == 2)
        throw RuntimeException("Instruction Error!");
}

bool    Parser::interpret(void)
{
    
    if (_file.length() <= 0)
    {
        lines_interpret(NULL, true);
    }
    else
    {
        std::ifstream ifs(_file, std::ifstream::in);
        if (ifs.is_open())
        {
            lines_interpret(&ifs, false);
            ifs.close();
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
    if (_instruction.size() <= 0)
        throw RuntimeException("Is empty program!");
    VMList<Instruction>::iter it = _instruction.begin();
    while (it != _instruction.end())
    {
        if ((*it).execute(manager) == false)
            return ;
        it++;
    }
}


bool    Parser::Instruction::execute(Manager &manager)
{
    if (type == PUSH)
        manager.push(Factory::GetInstance().createOperand(valueType, value));
    else if (type == POP)
        manager.pop();
    else if (type == DUMP)
        manager.dump();
    else if (type == ASSERT)
    {
        IOperand const *op = Factory::GetInstance().createOperand(valueType, value);
        if (manager.assert(op) == false)
        {
            delete op;
            throw LogicException("Assert isn't equal!");
        }
        else
            delete op;
    }
    else if (type == ADD)
        manager.add();
    else if (type == SUB)
        manager.sub();
    else if (type == MUL)
        manager.mul();
    else if (type == DIV)
        manager.div();
    else if (type == MOD)
        manager.mod();
    else if (type == PRINT)
        manager.print();
    else if (type == EXIT)
        return (false);
    return (true);
}