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

    void setInputFileName(const std::string &inputFileName);
    const std::string &getInputFileName() const;

    int getRepoLength() const override;
    std::vector<ShoppingItem> getShoppingList() const override;

    /// Add, Delete
    void addElementRepo(const ShoppingItem& item) override;
    void deleteElementRepo(const std::string& name) override;

    /// Operators Overload
    ShoppingItem& operator[](int index) override;
};
