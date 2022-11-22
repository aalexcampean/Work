//
// Created by Alex Campean on 27.05.2022.
//

#include "Service.h"
#include "../Exception/CustomException.h"

Equation &Service::operator[](int index) {
    return repository->operator[](index);
}

int Service::getEquationListLength() const {
    return repository->getRepoLength();
}

std::vector<Equation> Service::getEquationList() const {
    return repository->getEquations();
}

double Service::computeSolution(const std::string &coefficientA, const std::string &coefficientB,
                                const std::string &coefficientC) {
    double validatedCoefficientA;
    size_t pos1;
    try {
        validatedCoefficientA = std::stod(coefficientA, &pos1);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos1 != coefficientA.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    } else if (validatedCoefficientA == 0) {
        throw CustomException(ExceptionTypes::InvalidZeroCoefficient);
    }

    double validatedCoefficientB;
    size_t pos2;
    try {
        validatedCoefficientB = std::stod(coefficientB, &pos2);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos2 != coefficientB.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    }

    double validatedCoefficientC;
    size_t pos3;
    try {
        validatedCoefficientC = std::stod(coefficientC, &pos3);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos3 != coefficientC.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    }

    return 0;
}

void Service::addElementService(const std::string &coefficientA, const std::string &coefficientB,
                                const std::string &coefficientC) {
    double validatedCoefficientA;
    size_t pos1;
    try {
        validatedCoefficientA = std::stod(coefficientA, &pos1);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos1 != coefficientA.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    } else if (validatedCoefficientA == 0) {
        throw CustomException(ExceptionTypes::InvalidZeroCoefficient);
    }

    double validatedCoefficientB;
    size_t pos2;
    try {
        validatedCoefficientB = std::stod(coefficientB, &pos2);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos2 != coefficientB.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    }

    double validatedCoefficientC;
    size_t pos3;
    try {
        validatedCoefficientC = std::stod(coefficientC, &pos3);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos3 != coefficientC.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleCoefficient);
    }

    Equation newEquation(validatedCoefficientA, validatedCoefficientB, validatedCoefficientC);
    this->repository->addElementRepo(newEquation);
}
