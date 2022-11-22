//
// Created by Alex Campean on 11.06.2022.
//

#include "WriterRepo.h"
#include <iostream>
#include <fstream>
#include <sstream>

WriterRepo::WriterRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

std::vector<Writer> WriterRepo::getAll() const {
    return writers;
}

Writer &WriterRepo::operator[](int index) {
    return writers[index];
}

void WriterRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Writer writer;
        if (!(iss >> writer)) { break; } // error

        writers.push_back(writer);
    }
}