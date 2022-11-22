//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <vector>
#include "../Domain/Person.h"

class PersonsRepo {
private:
    std::vector<Person> persons;
    std::string fileName;

    void load();
    void save();

public:
    PersonsRepo(const std::string &filename = "Persons.txt");
    ~PersonsRepo(){};

    std::vector<Person> getAll() const;
    Person& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const PersonsRepo &repository);
};

inline std::ostream& operator<<(std::ostream& stream, const PersonsRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}
