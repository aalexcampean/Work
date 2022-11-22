//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "BaseService.h"
#include "../Repository/UserRepository.h"

class UserService: public BaseService{
public:
    /// Constructors, Destructor
    UserService();
    UserService(BaseRepository* repository);
    UserService(const UserService &service);
    ~UserService();

    /// Copy Database
    int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge) override;

    /// Update
    void updateElementService(const std::string &breed, const std::string &name, double age, const std::string &image) override;

    /// First 10 Dogs
    void firstDogs() override;
};


