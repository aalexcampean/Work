//
// Created by Alex Campean on 04.04.2022.
//

#include "Repository.h"

Repository::Repository() {
}

Repository::Repository(const Repository &repository) {
    this->genes = repository.genes;
}

Repository::~Repository() {
}

int Repository::getRepositoryLength() {
    return this->genes.size();
}

std::vector<Gene> Repository::getAllRepository() {
    return this->genes;
}

void Repository::addGeneRepository(const Gene &gene) {
    auto it = find(this->genes.begin(), this->genes.end(), gene);
    if (it != this->genes.end()) {
        throw std::string("Gene already exists");
    }
    this->genes.push_back(gene);
}

Gene &Repository::operator[](int index) {
    return this->genes[index];
}
