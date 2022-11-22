//
// Created by Alex Campean on 10.06.2022.
//

#include "Person.h"

Person::Person(const std::string &name) : name(name) {}

const std::string &Person::getName() const {
    return name;
}

void Person::setName(const std::string &name) {
    Person::name = name;
}
