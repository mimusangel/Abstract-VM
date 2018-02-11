#include<iostream>
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
    Manager manager;
    manager.push(Factory::GetInstance().createOperand(INT8, "42"));
    manager.dump();
    return (0);
}