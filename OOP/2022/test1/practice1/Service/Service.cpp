//
// Created by Alex Campean on 04.04.2022.
//

#include "Service.h"

Service::Service() {
    this->repository = new Repository;
}

Service::Service(Repository *inputRepository) {
    this->repository = inputRepository;
}

Service::Service(const Service &service) {
    this->repository = service.repository;
}

Service::~Service() {
}

int Service::getServiceLength() {
    return this->repository->getRepositoryLength();
}

std::vector<Gene> Service::getAllService() {
    return this->repository->getAllRepository();
}

std::vector<Gene> Service::getAllSortedAscendingByOrganism() {
    std::vector<Gene> allGenes = this->repository->getAllRepository();
    std::sort(allGenes.begin(), allGenes.end());
    return allGenes;
}

std::vector<Gene> Service::getAllGenesContainingSequence(const std::string &inputSequence) {
    std::vector<Gene> allGenes = this->repository->getAllRepository();
    std::vector<Gene> filteredGenes;
    std::copy_if (allGenes.begin(), allGenes.end(), std::back_inserter(filteredGenes), [inputSequence](auto &it){
        return it.getSequence().find(inputSequence) != std::string::npos;
    });
    return filteredGenes;
}

void Service::addGeneService(const std::string &inputOrganism, const std::string &inputName,
                             const std::string &inputSequence) {
    Gene inputGene(inputOrganism, inputName, inputSequence);
    this->repository->addGeneRepository(inputGene);
}

Gene &Service::operator[](int index) {
    return this->repository->operator[](index);
}

void Service::addFirstEntries() {
    this->addGeneService("E_Coli_K12", "yqgE", "ATGAATTTACAGCAT");
    this->addGeneService("Bacillus_subtilis", "ppiA", "TTTTCATCACCGTCGG");
    this->addGeneService("Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG");
    this->addGeneService("Human", "yqgE", "GTGACAGCGCCCTTCTTTCCACG");
    this->addGeneService("E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC");
}
