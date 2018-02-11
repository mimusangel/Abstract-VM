#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>
#include <stdexcept>

class RuntimeException : public std::runtime_error {
public:
    RuntimeException(const std::string &what_arg) :
        runtime_error(what_arg)
    {}
};
class LogicException : public std::logic_error {
public:
    LogicException(const std::string &what_arg) :
        logic_error(what_arg)
    {}
};

#endif