#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include "IOperand.hpp"

class Factory {
private:
    typedef IOperand const *(Factory::*ptrCreate)(std::string const &) const;

    ptrCreate    _typeCreate[5];

    Factory(void);
    ~Factory(void) {}
    IOperand const *createInt8(std::string const &value) const;
    IOperand const *createInt16(std::string const &value) const;
    IOperand const *createInt32(std::string const &value) const;
    IOperand const *createFloat(std::string const &value) const;
    IOperand const *createDouble(std::string const &value) const;

    template <typename T>
    IOperand const *createByValue(eOperandType type, int precision, long double &value) const
    {
        return (new Operand<T>(type, value, precision, std::numeric_limits<T>::min(), std::numeric_limits<T>::max()));
    }

public:
    IOperand const *createOperand(eOperandType type, std::string const &value) const;

    static Factory &GetInstance(void);
};

#endif