#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "IOperand.hpp"
#include "Exception.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand {
private:
    eOperandType    _type;
    T               _value;
    int             _precision;
    T               _min;
    T               _max;

    std::string	    strValue;

public:
    Operand(eOperandType type, long double value, int precision) :
        _type(type), _value(0), _precision(precision),
        _min(std::numeric_limits<T>::min()),
        _max(std::numeric_limits<T>::max())
    {
        if (value >= _min)
        {
            if (value <= _max)
            {
                _value = (T)value;
                std::ostringstream ss;
                if (_type >= FLOAT)
                    ss << (double)_value;
                else
                    ss << (long)_value;
                strValue.append(ss.str());
            }
            else
                throw RuntimeException("Error: Overflow!");
        }
        else
            throw RuntimeException("Error: Underflow!");
    }

    int             getPrecision(void) const
    {
        return (_precision);
    }

    eOperandType    getType(void) const
    {
        return (_type);
    }
    
    T               getValue(void) const
    {
        return (_value);
    }
    
    T               getMin(void) const
    {
        return (_min);
    }
    
    T               getMax(void) const
    {
        return (_max);
    }

    
    template <typename U>
    IOperand const *createByValue(eOperandType type, int precision, long double value) const
    {
        return (new Operand<U>(type, value, precision));
    }

    IOperand const  *operator+(IOperand const &rhs) const
    {
        IOperand const        *result = NULL;
        eOperandType const    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        long double value = (long double)((double)this->getValue() + std::atof(rhs.toString().c_str()));

        if (nType == INT8)
            result = createByValue<char>(nType, 0, value);
        else if (nType == INT16)
            result = createByValue<int>(nType, 1, value);
        else if (nType == INT32)
            result = createByValue<long>(nType, 2, value);
        else if (nType == FLOAT)
            result = createByValue<float>(nType, 3, value);
        else if (nType == DOUBLE)
            result = createByValue<double>(nType, 4, value);
        return (result);
    }

    IOperand const  *operator-(IOperand const &rhs) const
    {
        IOperand const        *result = NULL;
        eOperandType const    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        long double value = (long double)((double)this->getValue() - std::atof(rhs.toString().c_str()));

        if (nType == INT8)
            result = createByValue<char>(nType, 0, value);
        else if (nType == INT16)
            result = createByValue<int>(nType, 1, value);
        else if (nType == INT32)
            result = createByValue<long>(nType, 2, value);
        else if (nType == FLOAT)
            result = createByValue<float>(nType, 3, value);
        else if (nType == DOUBLE)
            result = createByValue<double>(nType, 4, value);
        return (result);
    }

    IOperand const  *operator*(IOperand const &rhs) const
    {
        IOperand const        *result = NULL;
        eOperandType const   nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        long double value = (long double)((double)this->getValue() * std::atof(rhs.toString().c_str()));

        if (nType == INT8)
            result = createByValue<char>(nType, 0, value);
        else if (nType == INT16)
            result = createByValue<int>(nType, 1, value);
        else if (nType == INT32)
            result = createByValue<long>(nType, 2, value);
        else if (nType == FLOAT)
            result = createByValue<float>(nType, 3, value);
        else if (nType == DOUBLE)
            result = createByValue<double>(nType, 4, value);
        return (result);
    }

    IOperand const  *operator/(IOperand const &rhs) const
    {
        IOperand const        *result = NULL;
        eOperandType const   nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (std::atof(rhs.toString().c_str()) == 0)
            throw LogicException("Error: Divide by Zero!");
        long double value = (long double)((double)this->getValue() / std::atof(rhs.toString().c_str()));
        if (nType == INT8)
            result = createByValue<char>(nType, 0, value);
        else if (nType == INT16)
            result = createByValue<int>(nType, 1, value);
        else if (nType == INT32)
            result = createByValue<long>(nType, 2, value);
        else if (nType == FLOAT)
            result = createByValue<float>(nType, 3, value);
        else if (nType == DOUBLE)
            result = createByValue<double>(nType, 4, value);
        return (result);
    }

    IOperand const  *operator%(IOperand const &rhs) const
    {
        IOperand const        *result = NULL;
        eOperandType const   nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (std::atof(rhs.toString().c_str()) == 0)
            throw LogicException("Error: Divide by Zero!");
        if (this->getType() == FLOAT || rhs.getType() == FLOAT)
            throw LogicException("Error: Modulo with float");
        if (this->getType() == DOUBLE || rhs.getType() == DOUBLE)
            throw LogicException("Error: Modulo with double");
        long double value = (long double)((long int)this->getValue() % std::atol(rhs.toString().c_str()));
        if (nType == INT8)
            result = createByValue<char>(nType, 0, value);
        else if (nType == INT16)
            result = createByValue<int>(nType, 1, value);
        else if (nType == INT32)
            result = createByValue<long>(nType, 2, value);
        return (result);
    }

    std::string const &toString(void) const
    {
        return (strValue);
    }
};

#endif