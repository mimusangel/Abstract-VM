#include<iostream>
#include <stdexcept>
#include "Manager.hpp"
#include "Factory.hpp"

int main(int ac, char **av)
{
    // if (ac > 2)
    // {
    //     std::cout << "Usage: ./avm [file]" << std::endl;
    // }
    // else
    // {
    //     if (ac == 1)
    //     {
    //         (void)av;
    //     }
    //     else
    //     {

    //     }

    // }
    (void)ac;
    (void)av;
    try
    {
        Manager manager;
        manager.push(Factory::GetInstance().createOperand(INT32, "42"));
        manager.push(Factory::GetInstance().createOperand(INT32, "33"));
        manager.add();
        manager.push(Factory::GetInstance().createOperand(FLOAT, "44.55"));
        manager.mul();
        manager.push(Factory::GetInstance().createOperand(DOUBLE, "42.42"));
        manager.push(Factory::GetInstance().createOperand(INT32, "42"));
        manager.dump();
    }
    catch(std::exception const &e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}