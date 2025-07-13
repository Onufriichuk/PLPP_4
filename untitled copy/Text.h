#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "Line.h"
#include "TextLine.h"
#include "ChecklistLine.h"
#include "ContactLine.h"

class Text {
    std::vector<std::unique_ptr<Line>> lines;
public:
    void addLine(std::unique_ptr<Line> line) { lines.push_back(std::move(line)); }
    void printAll() const { for (const auto& l : lines) l->print(); }
    void clear() { lines.clear(); }
    std::string serialize() const {
        std::string out;
        for (const auto& l : lines) out += l->serialize() + "\n";
        return out;
    }
    void deserialize(const std::string& data) {
        clear();
        size_t start = 0, end;
        while ((end = data.find('\n', start)) != std::string::npos) {
            std::string line = data.substr(start, end - start);
            if (line.rfind("TEXT|", 0) == 0) {
                auto l = std::make_unique<TextLine>();
                l->deserialize(line.substr(5));
                addLine(std::move(l));
            } else if (line.rfind("CHECK|", 0) == 0) {
                auto l = std::make_unique<ChecklistLine>();
                l->deserialize(line.substr(6));
                addLine(std::move(l));
            } else if (line.rfind("CONTACT|", 0) == 0) {
                auto l = std::make_unique<ContactLine>();
                l->deserialize(line.substr(8));
                addLine(std::move(l));
            }
            start = end + 1;
        }
    }
    bool saveToFile(const std::string& filename) {
        std::ofstream f(filename);
        if (!f) return false;
        f << serialize();
        return true;
    }
    bool loadFromFile(const std::string& filename) {
        std::ifstream f(filename);
        if (!f) return false;
        std::string data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        deserialize(data);
        return true;
    }
};