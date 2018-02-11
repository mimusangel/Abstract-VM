#include <iostream>
#include "Manager.hpp"
#include "Exception.hpp"
#include "Operand.hpp"

Manager::~Manager(void)
{
	while (_stack.size())
	{
		delete _stack.top();
		_stack.pop();
	}
}

void	    Manager::push(IOperand const *op)
{
	_stack.push(op);
}

IOperand const    *Manager::get(void)
{   
	if (_stack.size() <= 0)
		throw RuntimeException("Stack is empty!");
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
	int i = _stack.size() - 1;
	while (i >= 0)
	{
		std::cout << _stack[i]->toString() << std::endl;
		i--;
	}
}

void        Manager::add(void)
{
	if (_stack.size() < 2)
		throw RuntimeException("Stack is empty or does not have enough!");
	IOperand const   *one = get();
	IOperand const   *two = get();
	push(*two + *one);
	delete one;
	delete two;
}

void        Manager::sub(void)
{
	if (_stack.size() < 2)
		throw RuntimeException("Stack is empty or does not have enough!");
	IOperand const   *one = get();
	IOperand const   *two = get();
	push(*two - *one);
	delete one;
	delete two;
}

void        Manager::mul(void)
{
	if (_stack.size() < 2)
		throw RuntimeException("Stack is empty or does not have enough!");
	IOperand const   *one = get();
	IOperand const   *two = get();
	push(*two * *one);
	delete one;
	delete two;
}

void        Manager::div(void)
{
	if (_stack.size() < 2)
		throw RuntimeException("Stack is empty or does not have enough!");
	IOperand const   *one = get();
	IOperand const   *two = get();
	push(*two / *one);
	delete one;
	delete two;
}

void        Manager::mod(void)
{
	if (_stack.size() < 2)
		throw RuntimeException("Stack is empty or does not have enough!");
	IOperand const   *one = get();
	IOperand const   *two = get();
	push(*two % *one);
	delete one;
	delete two;
}

void		Manager::print(void)
{
	if (_stack.size() <= 0)
		throw RuntimeException("Stack is empty!");
	IOperand const   *op = _stack.top();
	if (op->getType() == INT8)
	{
		char c = std::atoi(op->toString().c_str());
		std::cout << c;
	}
	else
		std::cout << op->toString();
}

bool	    Manager::assert(IOperand const *op)
{
	IOperand const    *top = _stack.top();
	return (op->getType() == top->getType() && op->toString() == top->toString());
}