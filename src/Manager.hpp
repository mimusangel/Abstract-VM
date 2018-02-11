#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "VMList.hpp"
#include "IOperand.hpp"

class Manager {
private:
	VMList<IOperand const *> _stack;

public:
	Manager(void) {}
	~Manager(void);
	void	    	push(IOperand const *op);
	IOperand const	*get(void);
	void            pop(void);
	void            dump(void);
	void			add(void);
	void			sub(void);
	void			mul(void);
	void			div(void);
	void			mod(void);
	void			print(void);
	bool	    	assert(IOperand const *op);
};

#endif