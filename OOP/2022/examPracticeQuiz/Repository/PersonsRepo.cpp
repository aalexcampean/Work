//
// Created by Alex Campean on 10.06.2022.
//

#include "PersonsRepo.h"

#include <iostream>
#include <fstream>
#include <sstream>

PersonsRepo::PersonsRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

void PersonsRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Person person;
        if (!(iss >> person)) { break; } // error

        persons.push_back(person);
    }
}

void PersonsRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

std::vector<Person> PersonsRepo::getAll() const {
    return persons;
}

Person &PersonsRepo::operator[](int index) {
    return persons[index];
}