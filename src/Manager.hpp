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
	void			add(void);
	void			sub(void);
	void			mul(void);
	void			div(void);
	void			mod(void);
};

#endif