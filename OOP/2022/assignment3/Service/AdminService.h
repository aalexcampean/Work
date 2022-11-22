//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "BaseService.h"
#include "../Repository/AdminRepository.h"


class AdminService: public BaseService{
public:
    /// Constructors, Destructor
    AdminService();
    AdminService(BaseRepository* repository);
    AdminService(const AdminService &service);
    ~AdminService();

    /// Copy Database
    int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge) override;

    /// Update
    void updateElementService(const std::string &breed, const std::string &name, double age, const std::string &image) override;

    /// First 10 Dogs
    void firstDogs() override;
};