#include<iostream>

int main(int ac, char **av)
{
    if (ac > 2)
    {
        std::cout << "Usage: ./avm [file]" << std::endl;
    }
    else
    {
        if (ac == 1)
        {
            (void)av;
        }
        else
        {

        }

    }
    return (0);
}