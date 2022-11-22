//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

#include "../Domain/Writer.h"

class WriterRepo {
private:
    std::vector<Writer> writers;
    std::string fileName;

    void load();
public:
    WriterRepo(const std::string &filename = "Writers.txt");
    ~WriterRepo(){};
    std::vector<Writer> getAll() const;
    Writer& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const WriterRepo &repository);
};

inline std::ostream& operator<<(std::ostream& stream, const WriterRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}

