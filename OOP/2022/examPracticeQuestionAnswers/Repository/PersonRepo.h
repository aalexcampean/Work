//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include "Person.h"


class PersonRepo {
private:
    std::vector<Person> persons;
    std::string fileName;

    void load();

public:
    PersonRepo(const std::string &filename = "Persons.txt");
    ~PersonRepo(){};

    std::vector<Person> getAll() const;
    Person& operator[](int index);
};