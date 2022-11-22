//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include "../Domain/Programmer.h"

class ProgrammerRepo {
private:
    std::vector<Programmer> programmers;
    std::string fileName;

    void load();
    void save();

public:
    ProgrammerRepo(const std::string &filename = "Programmers.txt");
    ~ProgrammerRepo(){};

    std::vector<Programmer> getAll() const;
    Programmer& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const ProgrammerRepo &repository);
};

inline std::ostream& operator<<(std::ostream& stream, const ProgrammerRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}
