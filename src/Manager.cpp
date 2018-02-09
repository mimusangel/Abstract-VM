#include <iostream>
#include "Manager.hpp"

void	    Manager::push(IOperand const *op)
{
    _stack.push(op);
}

IOperand const    *Manager::get(void)
{   
    if (_stack.size() <= 0)
    {
        // EXEPTION STACK VIDE !
    }
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

IOperand const   *Manager::add(void)
{
    if (_stack.size() < 2)
    {
        // EXEPTION
    }
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one + *two);
    delete one;
    delete two;
    return (get());
}

IOperand const   *Manager::sub(void)
{
    if (_stack.size() < 2)
    {
        // EXEPTION
    }
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one - *two);
    delete one;
    delete two;
    return (get());
}

IOperand const   *Manager::mul(void)
{
    if (_stack.size() < 2)
    {
        // EXEPTION
    }
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one * *two);
    delete one;
    delete two;
    return (get());
}

IOperand const   *Manager::div(void)
{
    if (_stack.size() < 2)
    {
        // EXEPTION
    }
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one / *two);
    delete one;
    delete two;
    return (get());
}

IOperand const   *Manager::mod(void)
{
    if (_stack.size() < 2)
    {
        // EXEPTION
    }
    IOperand const   *one = get();
    IOperand const   *two = get();
    push(*one % *two);
    delete one;
    delete two;
    return (get());
}
