//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "UserService.h"
#include "../Repository/InMemory/InMemoryRepository.h"


class AdminService: public UserService{
public:
    /// Constructors, Destructor
    AdminService(TextFileRepository* repository);
    AdminService(const AdminService &service);
    ~AdminService();

    /// Getters
    TextFileRepository* getRepoState();

    /// Filter Dogs by breed
    std::vector<Dog> filterByBreedAndAge(const std::string &inputBreed, double inputAge);

    /// Update
    void updateElementService(const std::string &breed, const std::string &name, std::string age, const std::string &image);
};