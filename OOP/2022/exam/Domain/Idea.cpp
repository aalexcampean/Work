//
// Created by Alex Campean on 11.06.2022.
//

#include "Idea.h"

Idea::Idea(const std::string &description, const std::string &creator, int act) : id(currentId++), description(
        description), status("proposed"), creator(creator), act(act) {}

int Idea::getId() const {
    return id;
}

const std::string &Idea::getDescription() const {
    return description;
}

void Idea::setDescription(const std::string &description) {
    Idea::description = description;
}

const std::string &Idea::getStatus() const {
    return status;
}

void Idea::setStatus(const std::string &status) {
    Idea::status = status;
}

const std::string &Idea::getCreator() const {
    return creator;
}

void Idea::setCreator(const std::string &creator) {
    Idea::creator = creator;
}

int Idea::getAct() const {
    return act;
}

void Idea::setAct(int act) {
    Idea::act = act;
}

std::string Idea::toString() {
    return "ID: " + std::to_string(id) + " -  Description: " + description + " -  Status: " + status + " -  Creator: " +
           creator + " -  Act: " + std::to_string(act);
}

bool Idea::operator==(Idea &idea) const {
    return id == idea.id;
}

bool Idea::operator==(int inputId) const {
    return id == inputId;;
}
