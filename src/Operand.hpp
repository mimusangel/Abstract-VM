#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include "IOperand.hpp"
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
    Operand(eOperandType type, long double value, int precision, T min, T max) :
        _type(type), _value(0), _precision(precision), _min(min), _max(max)
    {
        if (value >= min)
        {
            if (value <= max)
            {
                _value = (T)value;
                std::ostringstream ss;
                ss << _value;
                strValue.append(ss.str());
            }
            else
            {
                // EXEPTION ! Overflow
            }
        }
        else
        {
            // EXEPTION ! Underflow
        }
    }

    int             Operand::getPrecision(void) const
    {
        return (_precision);
    }

    eOperandType    Operand::getType(void) const
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

    IOperand const  *operator+(IOperand const &rhs) const
    {
        IOperand        *result;
        eOperandType    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

        if (nType == INT8)
            result = Factory::GetInstance().createByValue<char>(nType, 0, this->getValue() + rhs->getValue());
        else if (nType == INT16)
            result = Factory::GetInstance().createByValue<int>(nType, 1, this->getValue() + rhs->getValue());
        else if (nType == INT32)
            result = Factory::GetInstance().createByValue<long>(nType, 2, this->getValue() + rhs->getValue());
        else if (nType == FLOAT)
            result = Factory::GetInstance().createByValue<float>(nType, 3, this->getValue() + rhs->getValue());
        else if (nType == DOUBLE)
            result = Factory::GetInstance().createByValue<double>(nType, 4, this->getValue() + rhs->getValue());
        return (result);
    }

    IOperand const  *operator-(IOperand const &rhs) const
    {
        IOperand        *result;
        eOperandType    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (nType == INT8)
            result = Factory::GetInstance().createByValue<char>(nType, 0, this->getValue() - rhs->getValue());
        else if (nType == INT16)
            result = Factory::GetInstance().createByValue<int>(nType, 1, this->getValue() - rhs->getValue());
        else if (nType == INT32)
            result = Factory::GetInstance().createByValue<long>(nType, 2, this->getValue() - rhs->getValue());
        else if (nType == FLOAT)
            result = Factory::GetInstance().createByValue<float>(nType, 3, this->getValue() - rhs->getValue());
        else if (nType == DOUBLE)
            result = Factory::GetInstance().createByValue<double>(nType, 4, this->getValue() - rhs->getValue());
        return (result);
    }

    IOperand const  *operator*(IOperand const &rhs) const
    {
        IOperand        *result;
        eOperandType    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (nType == INT8)
            result = Factory::GetInstance().createByValue<char>(nType, 0, this->getValue() * rhs->getValue());
        else if (nType == INT16)
            result = Factory::GetInstance().createByValue<int>(nType, 1, this->getValue() * rhs->getValue());
        else if (nType == INT32)
            result = Factory::GetInstance().createByValue<long>(nType, 2, this->getValue() * rhs->getValue());
        else if (nType == FLOAT)
            result = Factory::GetInstance().createByValue<float>(nType, 3, this->getValue() * rhs->getValue());
        else if (nType == DOUBLE)
            result = Factory::GetInstance().createByValue<double>(nType, 4, this->getValue() * rhs->getValue());
        return (result);
    }

    IOperand const  *operator/(IOperand const &rhs) const
    {
        IOperand        *result;
        eOperandType    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (rhs->getValue() == 0)
        {
            // EXEPTION ! DIVISION PAR 0
        }
        if (nType == INT8)
            result = Factory::GetInstance().createByValue<char>(nType, 0, this->getValue() / rhs->getValue());
        else if (nType == INT16)
            result = Factory::GetInstance().createByValue<int>(nType, 1, this->getValue() / rhs->getValue());
        else if (nType == INT32)
            result = Factory::GetInstance().createByValue<long>(nType, 2, this->getValue() / rhs->getValue());
        else if (nType == FLOAT)
            result = Factory::GetInstance().createByValue<float>(nType, 3, this->getValue() / rhs->getValue());
        else if (nType == DOUBLE)
            result = Factory::GetInstance().createByValue<double>(nType, 4, this->getValue() / rhs->getValue());
        return (result);
    }

    IOperand const  *operator%(IOperand const &rhs) const
    {
        IOperand        *result;
        eOperandType    nType = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();
        
        if (rhs->getValue() == 0)
        {
            // EXEPTION ! DIVISION PAR 0
        }
        if (this->getType() == FLOAT || this->getType() == DOUBLE
            || rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
        {
            // EXEPTION MODULO Impossible sur nombre flotant
        }
        if (nType == INT8)
            result = Factory::GetInstance().createByValue<char>(nType, 0, this->getValue() % rhs->getValue());
        else if (nType == INT16)
            result = Factory::GetInstance().createByValue<int>(nType, 1, this->getValue() % rhs->getValue());
        else if (nType == INT32)
            result = Factory::GetInstance().createByValue<long>(nType, 2, this->getValue() % rhs->getValue());
        return (result);
    }

    std::string const &toString(void) const
    {
        return (strValue);
    }
};

#endif