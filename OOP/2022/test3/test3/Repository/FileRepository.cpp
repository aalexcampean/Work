//
// Created by Alex Campean on 27.05.2022.
//

#include "FileRepository.h"
#include "../Exception/CustomException.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileRepository::FileRepository(const std::string &inputFileName) : fileName(inputFileName) {
    this->load();
}


int FileRepository::getRepoLength() const {
    return this->equations.size();
}

std::vector<Equation> FileRepository::getEquations() const {
    return this->equations;
}

void FileRepository::addElementRepo(const Equation &item) {
    auto it = std::find(equations.begin(), equations.end(), item);
    if (it != equations.end()) {
        throw CustomException(ExceptionTypes::AddException);
    }
    equations.push_back(item);
    this->save();
}

Equation &FileRepository::operator[](int index) {
    return this->equations[index];
}

void FileRepository::load() {
    std::ifstream input(this->fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Equation item;
        if (!(iss >> item)) { break; } // error

        this->addElementRepo(item);
    }
}

void FileRepository::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

