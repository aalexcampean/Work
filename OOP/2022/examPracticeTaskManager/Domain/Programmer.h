//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Programmer {
private:
    int id;
    std::string name;
public:
    Programmer(){};
    Programmer(int id, const std::string &name);
    ~Programmer(){};

    int getId() const;
    void setId(int id);

    const std::string &getName() const;
    void setName(const std::string &name);

    friend std::ostream &operator<<(std::ostream &os, const Programmer &programmer);
    friend std::istream& operator>>(std::istream& in, Programmer &programmer);
};

inline std::ostream &operator<<(std::ostream &os, const Programmer &programmer) {
    os << std::to_string(programmer.id) << "," << programmer.name;
    return os;
}

inline std::istream &operator>>(std::istream &in, Programmer &programmer) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 2; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    programmer.id = std::stoi(fields[0]);
    programmer.name = fields[1];

    return in;
}