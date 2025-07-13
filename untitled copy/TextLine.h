#pragma once
#include "Line.h"

class TextLine : public Line {
    std::string text;
public:
    TextLine(const std::string& t = "") : text(t) {}
    void print() const override { std::cout << text << std::endl; }
    std::string serialize() const override { return "TEXT|" + text; }
    void deserialize(const std::string& s) override { text = s; }
    std::string type() const override { return "TEXT"; }
};