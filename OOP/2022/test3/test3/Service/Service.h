//
// Created by Alex Campean on 27.05.2022.
//

#pragma once
#include "FileRepository.h"

class Service {
private:
    FileRepository *repository;
public:
    /// Constructors, Destructor
    Service(FileRepository* repository): repository(repository){};
    Service(const Service &service): repository(service.repository){};
    ~Service(){};

    /// Getters
    Equation& operator[](int index);
    int getEquationListLength() const;
    std::vector<Equation> getEquationList() const;

    /// Compute Solution
    double computeSolution(const std::string &coefficientA, const std::string &coefficientB, const std::string &coefficientC);

    /// Add
    void addElementService(const std::string &coefficientA, const std::string &coefficientB, const std::string &coefficientC);
};