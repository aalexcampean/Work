//
// Created by Alex Campean on 10.06.2022.
//

#include "ProgrammerRepo.h"

ProgrammerRepo::ProgrammerRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

void ProgrammerRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Programmer programmer;
        if (!(iss >> programmer)) { break; } // error

        programmers.push_back(programmer);
    }
}

void ProgrammerRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

std::vector<Programmer> ProgrammerRepo::getAll() const {
    return programmers;
}

Programmer &ProgrammerRepo::operator[](int index) {
    return programmers[index];
}