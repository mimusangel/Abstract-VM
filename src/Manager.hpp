#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <stack>
#include "IOperand.hpp"

class Manager {
private:
	std::stack<IOperand const *> _stack;

public:
	Manager(void) {}
	void	    	push(IOperand const *op);
	IOperand const	*get(void);
	void            pop(void);
	void            dump(void);
	IOperand const	*add(void);
	IOperand const	*sub(void);
	IOperand const	*mul(void);
	IOperand const	*div(void);
	IOperand const	*mod(void);
};

#endif