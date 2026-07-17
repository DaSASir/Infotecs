#ifndef IBUFFER_H
#define IBUFFER_H

#include <iostream>
#include <string>

class IBuffer {
public:
    virtual ~IBuffer() = default;
    virtual void push(const std::string& data) = 0;
    virtual std::string pop() = 0;
};

#endif // IBUFFER_H