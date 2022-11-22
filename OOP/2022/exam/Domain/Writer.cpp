//
// Created by Alex Campean on 11.06.2022.
//

#include "Writer.h"

Writer::Writer(const std::string &name, const std::string &expertise) : id(currentId++), name(name),
                                                                        expertise(expertise) {}

int Writer::getId() const {
    return id;
}

const std::string &Writer::getName() const {
    return name;
}

void Writer::setName(const std::string &name) {
    Writer::name = name;
}

const std::string &Writer::getExpertise() const {
    return expertise;
}

void Writer::setExpertise(const std::string &expertise) {
    Writer::expertise = expertise;
}

bool Writer::operator==(const Writer &writer) const {
    return id == writer.id;
}

std::string Writer::toString() {
    return "ID: " + std::to_string(id) + " -  Name: " + name + " -  Expertise: " + expertise;
}
