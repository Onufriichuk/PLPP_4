#pragma once
#include "Text.h"
#include "CaesarCipher.h"
#include <iostream>
#include <vector>
#include <memory>

class TextEditor {
    std::vector<std::unique_ptr<Text>> tabs;
    int currentTab = 0;

    Text& current() { return *tabs[currentTab]; }

public:
    TextEditor() { tabs.push_back(std::make_unique<Text>()); }

    void run() {
        std::cout << "Text Editor)\n";
        while (true) {
            std::cout << "\nTab " << (currentTab + 1) << "/" << tabs.size() << "\n";
            std::cout << "1. Add Text Line\n2. Add Checklist Line\n3. Add Contact Line\n4. Print All\n5. Save\n6. Load\n7. Encrypt & Save\n8. Load & Decrypt\n";
            std::cout << "9. New Tab\n10. Switch Tab\n11. Close Tab\n12. Exit\nChoice: ";
            int ch; std::cin >> ch; std::cin.ignore();
            if (ch == 1) {
                std::string t; std::cout << "Text: "; std::getline(std::cin, t);
                current().addLine(std::make_unique<TextLine>(t));
            } else if (ch == 2) {
                std::string i; char c;
                std::cout << "Item: "; std::getline(std::cin, i);
                std::cout << "Checked (y/n): "; std::cin >> c; std::cin.ignore();
                current().addLine(std::make_unique<ChecklistLine>(i, c == 'y' || c == 'Y'));
            } else if (ch == 3) {
                std::string n, s, e;
                std::cout << "Name: "; std::getline(std::cin, n);
                std::cout << "Surname: "; std::getline(std::cin, s);
                std::cout << "Email: "; std::getline(std::cin, e);
                current().addLine(std::make_unique<ContactLine>(n, s, e));
            } else if (ch == 4) {
                current().printAll();
            } else if (ch == 5) {
                std::string f; std::cout << "Filename: "; std::getline(std::cin, f);
                if (current().saveToFile(f)) std::cout << "Saved.\n"; else std::cout << "Error.\n";
            } else if (ch == 6) {
                std::string f; std::cout << "Filename: "; std::getline(std::cin, f);
                if (current().loadFromFile(f)) std::cout << "Loaded.\n"; else std::cout << "Error.\n";
            } else if (ch == 7) {
                std::string f, lib; int key;
                std::cout << "Filename: "; std::getline(std::cin, f);
                std::cout << "Library path: "; std::getline(std::cin, lib);
                std::cout << "Key: "; std::cin >> key; std::cin.ignore();
                CaesarCipher cipher(lib);
                std::string enc = cipher.encrypt(current().serialize(), key);
                std::ofstream out(f, std::ios::binary); out << enc; out.close();
                std::cout << "Encrypted and saved.\n";
            } else if (ch == 8) {
                std::string f, lib; int key;
                std::cout << "Filename: "; std::getline(std::cin, f);
                std::cout << "Library path: "; std::getline(std::cin, lib);
                std::cout << "Key: "; std::cin >> key; std::cin.ignore();
                CaesarCipher cipher(lib);
                std::ifstream in(f, std::ios::binary);
                std::string enc((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
                std::string dec = cipher.decrypt(enc, key);
                current().deserialize(dec);
                std::cout << "Loaded and decrypted.\n";
            } else if (ch == 9) { // New Tab
                tabs.push_back(std::make_unique<Text>());
                currentTab = tabs.size() - 1;
                std::cout << "New tab created. Switched to tab " << (currentTab + 1) << ".\n";
            } else if (ch == 10) { // Switch Tab
                std::cout << "Enter tab number (1-" << tabs.size() << "): ";
                int t; std::cin >> t; std::cin.ignore();
                if (t >= 1 && t <= (int)tabs.size()) {
                    currentTab = t - 1;
                    std::cout << "Switched to tab " << t << ".\n";
                } else {
                    std::cout << "Invalid tab number.\n";
                }
            } else if (ch == 11) { // Close Tab
                if (tabs.size() == 1) {
                    std::cout << "Cannot close the last tab.\n";
                } else {
                    tabs.erase(tabs.begin() + currentTab);
                    if (currentTab >= (int)tabs.size()) currentTab = tabs.size() - 1;
                    std::cout << "Tab closed. Now at tab " << (currentTab + 1) << ".\n";
                }
            } else if (ch == 12) {
                break;
            }
        }
    }
};