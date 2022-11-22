//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Person {
private:
    std::string name;
public:
    Person(){};
    Person(const std::string &name);
    ~Person(){};

    const std::string &getName() const;
    void setName(const std::string &name);

    friend std::ostream &operator<<(std::ostream &os, const Person &person);
    friend std::istream& operator>>(std::istream& in, Person &person);

};

inline std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << person.name;
    return os;
}

inline std::istream &operator>>(std::istream &in, Person &person) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 1; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    person.name = fields[0];
    return in;
}