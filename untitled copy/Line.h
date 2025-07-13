#pragma once
#include <string>
#include <iostream>

class Line {
public:
    virtual ~Line() {}
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string&) = 0;
    virtual std::string type() const = 0;
};