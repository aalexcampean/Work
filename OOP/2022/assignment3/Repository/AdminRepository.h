//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "BaseRepository.h"

class AdminRepository: public BaseRepository {
public:
    /// Constructors, Destructor
    AdminRepository();
    AdminRepository(const AdminRepository &repository);
    ~AdminRepository();

    /// Copy Database
    int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge) override;

    /// Update
    void updateElementAdminRepo(Dog &dog) override;
};
