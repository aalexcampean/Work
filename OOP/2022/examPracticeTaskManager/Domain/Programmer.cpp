//
// Created by Alex Campean on 10.06.2022.
//

#include "Programmer.h"

Programmer::Programmer(int id, const std::string &name) : id(id), name(name) {}

int Programmer::getId() const {
    return id;
}

void Programmer::setId(int id) {
    Programmer::id = id;
}

const std::string &Programmer::getName() const {
    return name;
}

void Programmer::setName(const std::string &name) {
    Programmer::name = name;
}
