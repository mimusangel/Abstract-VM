#include "Factory.hpp"
/*
**  PRIVATE
*/
Factory::Factory(void)
{
    _typeCreate[0] = &Factory::createInt8;
    _typeCreate[1] = &Factory::createInt16;
    _typeCreate[2] = &Factory::createInt32;
    _typeCreate[3] = &Factory::createFloat;
    _typeCreate[4] = &Factory::createDouble;
}

IOperand const *Factory::createInt8(std::string const &value) const
{
    return (new Operand<char>(INT8, std::atoi(value.c_str()), 0, std::numeric_limits<char>::min(), std::numeric_limits<char>::max()));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
    return (new Operand<int>(INT16, std::atoi(value.c_str()), 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
    return (new Operand<long>(INT32, std::atol(value.c_str()), 2, std::numeric_limits<long>::min(), std::numeric_limits<long>::max()));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
    return (new Operand<float>(FLOAT, std::atof(value.c_str()), 3, std::numeric_limits<float>::min(), std::numeric_limits<float>::max()));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
    return (new Operand<double>(DOUBLE, std::atof(value.c_str()), 4, std::numeric_limits<double>::min(), std::numeric_limits<double>::max()));
}

/*
**  PUBLIC
*/
IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const
{
    return ((this->*_typeCreate[type])(value));
}

/*
**  STATIC PUBLIC
*/
Factory &Factory::GetInstance(void)
{
    static Factory instance;
    return (instance);
}