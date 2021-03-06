#include<iostream>
#include <stdexcept>
#include "Manager.hpp"
#include "Factory.hpp"
#include "Parser.hpp"

int main(int ac, char **av)
{
    if (ac > 2)
    {
        std::cout << "Usage: ./avm [file]" << std::endl;
    }
    else
    {
        Manager manager;
        Parser *parser;
        if (ac == 1)
            parser = new Parser("");
        else
            parser = new Parser(av[1]);
        try
        {
            if (parser->interpret())
                parser->execute(manager);
        }
        catch(std::exception const &e)
        {
            std::cout << "ERROR: " << e.what() << std::endl;
        }
        delete parser;
    }
    // try
    // {
    //     Manager manager;
    //     manager.push(Factory::GetInstance().createOperand(INT8, "33"));
    //     manager.push(Factory::GetInstance().createOperand(INT8, "112"));
    //     manager.push(Factory::GetInstance().createOperand(INT8, "111"));
    //     manager.push(Factory::GetInstance().createOperand(INT8, "108"));
    //     manager.push(Factory::GetInstance().createOperand(INT8, "112"));
    //     manager.print();
    //     manager.pop();
    //     manager.print();
    //     manager.pop();
    //     manager.print();
    //     manager.pop();
    //     manager.print();
    //     manager.pop();
    //     manager.print();
    //     manager.pop();
    //     std::cout << std::endl;
        // manager.push(Factory::GetInstance().createOperand(INT32, "42"));
        // manager.push(Factory::GetInstance().createOperand(INT32, "33"));
        // manager.add();
        // manager.push(Factory::GetInstance().createOperand(FLOAT, "44.55"));
        // manager.mul();
        // manager.push(Factory::GetInstance().createOperand(DOUBLE, "42.42"));
        // manager.push(Factory::GetInstance().createOperand(INT32, "42"));
        // manager.dump();
    // }
    // catch(std::exception const &e)
    // {
    //     std::cout << e.what() << std::endl;
    // }
    return (0);
}