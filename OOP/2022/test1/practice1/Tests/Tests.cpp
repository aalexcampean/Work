//
// Created by Alex Campean on 04.04.2022.
//

#include <iostream>
#include "Tests.h"
#include "../Service/Service.h"

void testAll() {
    testAddFunctionalityRepo();
    testAddFunctionalityService();
    testFilterBySequenceFunctionalityService();
}

void testAddFunctionalityRepo() {
    Repository repository;
    assert(repository.getRepositoryLength() == 0);

    Gene gene1("E_Coli_K12", "yqgE", "ATGAATTACAGCAT");
    Gene gene2("Mouse", "yqgE", "GTGACAGCGCCCTTCTTTCCACG");

    repository.addGeneRepository(gene1);
    assert(repository.getRepositoryLength() == 1);
    repository.addGeneRepository(gene2);
    assert(repository.getRepositoryLength() == 2);

    Gene gene3("E_Coli_K12", "yqgE", "HFJKKEVGHGNNMBE");
    try {
        repository.addGeneRepository(gene3);
    } catch (std::string error) {
//        std::cout << error;
    }
    assert(repository.getRepositoryLength() == 2);
}

void testAddFunctionalityService() {
    Service service;
    assert(service.getServiceLength() == 0);

    service.addGeneService("E_Coli_K12", "yqgE", "ATGAATTACAGCAT");
    assert(service.getServiceLength() == 1);
    service.addGeneService("Mouse", "yqgE", "GTGACAGCGCCCTTCTTTCCACG");
    assert(service.getServiceLength() == 2);

    try {
        service.addGeneService("E_Coli_K12", "yqgE", "HFJKKEVGHGNNMBE");
    } catch (std::string error) {
//        std::cout << error;
    }
    assert(service.getServiceLength() == 2);
}

void testFilterBySequenceFunctionalityService() {
    Service service;
    assert(service.getServiceLength() == 0);

    service.addFirstEntries();

    std::vector<Gene> allEntries;
    assert(allEntries.empty());

    std::vector<Gene> filteredEntries;
    assert(filteredEntries.empty());

    allEntries = service.getAllService();
    filteredEntries = service.getAllGenesContainingSequence("ATGAATTTACAGCAT");

    assert(allEntries.size() == 5);
    assert(filteredEntries.size() == 1);
}