//
// Created by Alex Campean on 04.04.2022.
//

#include "Gene.h"

Gene::Gene() {
    this->organism = "";
    this->name = "";
    this->sequence = "";
}

Gene::Gene(const std::string &inputOrganism, const std::string &inputName, const std::string &inputSequence) {
    this->organism = inputOrganism;
    this->name = inputName;
    this->sequence = inputSequence;
}

Gene::Gene(const Gene &gene) {
    this->organism = gene.organism;
    this->name = gene.name;
    this->sequence = gene.sequence;
}

Gene::~Gene() {
}

std::string Gene::getOrganism() {
    return this->organism;
}

std::string Gene::getName() {
    return this->name;
}

std::string Gene::getSequence() {
    return this->sequence;
}

void Gene::setOrganism(const std::string &inputOrganism) {
    this->organism = inputOrganism;
}

void Gene::setName(const std::string &inputName) {
    this->name = inputName;
}

void Gene::setSequence(const std::string &inputSequence) {
    this->sequence = inputSequence;
}

bool Gene::operator==(const Gene &gene) const {
    return (this->organism == gene.organism && this->name == gene.name);
}

bool Gene::operator<(const Gene &gene) const {
    return (this->organism < gene.organism);
}

Gene &Gene::operator=(const Gene &gene) {
    this->organism = gene.organism;
    this->name = gene.name;
    this->sequence = gene.sequence;
    return *this;
}

std::string Gene::toString() {
    std::string stringBuilder;
    stringBuilder += this->organism + " | " +
            this->name + " | " +
            this->sequence;

    return stringBuilder;
}
