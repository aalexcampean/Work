//
// Created by Alex Campean on 27.05.2022.
//

#pragma once
#include "Repository.h"

class FileRepository : public Repository{
private:
    std::string fileName;

    /// Load data from file
    void load();
    void save();
public:
    FileRepository(){};
    FileRepository(const std::string &inputFileName);
    FileRepository(const FileRepository &inputRepository) : Repository(inputRepository){};
    ~FileRepository(){};

    int getRepoLength() const override;
    std::vector<Equation> getEquations() const override;

    /// Add, Delete
    void addElementRepo(const Equation& item) override;

    /// Operators Overload
    Equation& operator[](int index) override;
};
