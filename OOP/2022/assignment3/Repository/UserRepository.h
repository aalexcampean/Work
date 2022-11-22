//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "BaseRepository.h"

class UserRepository: public BaseRepository{
public:
    /// Constructors, Destructor
    UserRepository();
    UserRepository(const UserRepository &repository);
    ~UserRepository();

    /// Copy Database
    int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge) override;

    /// Update
    void updateElementAdminRepo(Dog &dog) override;
};

