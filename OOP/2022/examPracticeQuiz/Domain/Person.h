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
    int score;
public:
    Person(){};
    Person(const std::string &name, int score);
    ~Person(){};

    const std::string &getName() const;
    void setName(const std::string &name);

    int getScore() const;
    void setScore(int score);

    friend std::ostream &operator<<(std::ostream &os, const Person &person);
    friend std::istream& operator>>(std::istream& in, Person &person);
};

inline std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << person.name << "," << std::to_string(person.score);
    return os;
}

inline std::istream &operator>>(std::istream &in, Person &person) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 2; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    person.name = fields[0];
    person.score = std::stoi(fields[1]);

    return in;
}

