#pragma once
#include "Line.h"

class ContactLine : public Line {
    std::string name, surname, email;
public:
    ContactLine(const std::string& n = "", const std::string& s = "", const std::string& e = "") : name(n), surname(s), email(e) {}
    void print() const override { std::cout << "Contact: " << name << " " << surname << " <" << email << ">\n"; }
    std::string serialize() const override { return "CONTACT|" + name + "|" + surname + "|" + email; }
    void deserialize(const std::string& s) override {
        size_t p1 = s.find('|'), p2 = s.find('|', p1+1), p3 = s.find('|', p2+1);
        name = s.substr(0, p1);
        surname = s.substr(p1+1, p2-p1-1);
        email = s.substr(p2+1);
    }
    std::string type() const override { return "CONTACT"; }
};