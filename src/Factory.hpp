#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <limits>
#include <string>
#include "IOperand.hpp"
#include "Operand.hpp"

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

public:
    IOperand const *createOperand(eOperandType type, std::string const &value) const;

    static Factory &GetInstance(void);
};

#endif