#pragma once
#include "Line.h"

class ChecklistLine : public Line {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i = "", bool c = false) : item(i), checked(c) {}
    void print() const override { std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl; }
    std::string serialize() const override { return "CHECK|" + item + "|" + (checked ? "1" : "0"); }
    void deserialize(const std::string& s) override {
        auto sep = s.find('|');
        item = s.substr(0, sep);
        checked = (s.substr(sep+1) == "1");
    }
    std::string type() const override { return "CHECK"; }
};