//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "../Repository/TextFile/TextFileRepository.h"


class UserService {
protected:
    TextFileRepository* repository;

public:
    /// Constructors, Destructor
    UserService(TextFileRepository* repository);
    UserService(const UserService &service);
    ~UserService();

    /// Set Repository Type
    void setRepositoryType(const std::string& type);

    /// Operators Overload
    UserService& operator=(const UserService &service);
    Dog& operator[](int index);

    /// Getters
    int getServiceLength() const;
    Dog& getDogByImage(const std::string &image);
    std::vector<Dog> getRepository() const;

    /// Filtering
    std::vector<Dog> filterByBreed(const std::string &inputBreed);

    /// Open File
    void openFile();

    /// Add, Delete, Update

    /// <summary>Adds an element to the service layer</summary>
    /// <param name="breed">string, the breed of the dog</param>
    /// <param name="name">string, the name of the dog</param>
    /// <param name="age">double, the age of the dog</param>
    /// <param name="image">string, the link to the image of the dog</param>
    /// <returns></returns
    void addElementService(const std::string &breed, const std::string &name, std::string age, const std::string &image);
    /// <summary>Deletes an element from the service layer</summary>
    /// <param name="image">string, the link to the image of the dog</param>
    /// <returns></returns
    void deleteElementService(const std::string &image);
};


