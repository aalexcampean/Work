//
// Created by Alex Campean on 10.06.2022.
//

#include "Person.h"

Person::Person(const std::string &name, int score) : name(name), score(score) {}

const std::string &Person::getName() const {
    return name;
}

void Person::setName(const std::string &name) {
    Person::name = name;
}

int Person::getScore() const {
    return score;
}

void Person::setScore(int score) {
    Person::score = score;
}
