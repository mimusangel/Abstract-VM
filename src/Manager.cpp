#include <iostream>
#include "Manager.hpp"
#include "Exception.hpp"
#include "Operand.hpp"

void	    Manager::push(IOperand const *op)
{
    _stack.push(op);
}

IOperand const    *Manager::get(void)
{   
    if (_stack.size() <= 0)
        throw RuntimeException("Error: Stack is empty!");
    IOperand const    *top = _stack.top();
    _stack.pop();
    return (top);
}

void        Manager::pop(void)
{
    delete get();
}

void        Manager::dump(void)
{
    IOperand const *op;
    while (_stack.size())
    {
        op = get();
        std::cout << op->toString() << std::endl;
        delete op;
    }
}

void        Manager::add(void)
{
    if (_stack.size() < 2)
        throw RuntimeException("Error: Stack is empty or does not have enough!");
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one + *two);
    delete one;
    delete two;
}

void        Manager::sub(void)
{
    if (_stack.size() < 2)
        throw RuntimeException("Error: Stack is empty or does not have enough!");
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one - *two);
    delete one;
    delete two;
}

void        Manager::mul(void)
{
    if (_stack.size() < 2)
        throw RuntimeException("Error: Stack is empty or does not have enough!");
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one * *two);
    delete one;
    delete two;
}

void        Manager::div(void)
{
    if (_stack.size() < 2)
        throw RuntimeException("Error: Stack is empty or does not have enough!");
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one / *two);
    delete one;
    delete two;
}

void        Manager::mod(void)
{
    if (_stack.size() < 2)
        throw RuntimeException("Error: Stack is empty or does not have enough!");
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one % *two);
    delete one;
    delete two;
}

void		Manager::print(void)
{
    if (_stack.size() <= 0)
        throw RuntimeException("Error: Stack is empty!");
    std::cout << _stack.top().toString() << std::endl;
}
