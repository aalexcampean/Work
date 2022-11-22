//
// Created by Alex Campean on 10.06.2022.
//

#include "PersonRepo.h"

PersonRepo::PersonRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

std::vector<Person> PersonRepo::getAll() const {
    return persons;
}

Person &PersonRepo::operator[](int index) {
    return persons[index];
}

void PersonRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Person person;
        if (!(iss >> person)) { break; } // error

        persons.push_back(person);
    }
}
