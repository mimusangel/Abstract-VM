#ifndef VMLIST_HPP
#define VMLIST_HPP

#include <stack>

template <typename T>
class VMList: public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator    iter;
	typedef typename std::stack<T>::reference                   ref;

	ref     operator[](size_t n)
    {
        return (this->c[n]);
    }
    
	iter    begin()
    {
        return (this->c.begin());
    }

	iter    end()
    {
        return (this->c.end());
    }
};

#endif