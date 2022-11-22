#include "Gene.h"
#include <string>
#include <iostream>

// Constructor, Destructor

Gene::Gene() {
    this->organism = "";
    this->name = "";
    this->sequence = "";

}

Gene::Gene(const std::string& organism, const std::string& name, const std::string& sequence){
    this->organism = organism;
    this->name = name;
    this->sequence = sequence;
}

Gene::Gene(Gene& g){
    this->organism = g.organism;
    this->name = g.name;
    this->sequence = g.sequence;
}


Gene::~Gene(){

}

//Operators Overload

Gene& Gene::operator=(const Gene& g) {
    this->organism = g.organism;
    this->name = g.name;
    this->sequence = g.sequence;

    return *this;
}

bool Gene::operator==(const Gene& g) const{
    return this->organism == g.organism;
}

bool Gene::checkIfEqual(const std::string &given_organism, const std::string &given_name) const {
    if (this->organism == given_organism && this->name == given_name) {
        return true;
    }

    return false;
}

// Getters

std::string Gene::getOrganism() const{
    return this->organism;
}

std::string Gene::getName() const{
    return this->name;
}

std::string Gene::getSequence() const{
    return this->sequence;
}

// Setters

void Gene::setSequence(const std::string& new_sequence) {
    this->sequence = new_sequence;
}

// String Representation

std::string Gene::toString() const{
    std::string destination_string =
            "Organism: " + this->organism + "  |  " +
            "Name: " + this->name + "  |  " +
            "Sequence: " + this->sequence;

    return destination_string;
}
