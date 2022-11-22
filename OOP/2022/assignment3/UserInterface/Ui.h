#pragma once

#include "../Service/AdminService.h"
#include "../Service/UserService.h"

class UserInterface{
private:
    BaseService* adminService;
    BaseService* userService;

public:
    /// Constructors, Destructor
    UserInterface(BaseService* providedAdminService, BaseService* providedUserService);
    UserInterface(UserInterface &ui);
    ~UserInterface();

    /// Start
    void start();
    void startAdministrator();
    void startUser();
    bool handleUserPassword();

    /// Print Menus
    void printStartMenu();
    void printAdministratorMenu();
    void printUserMenu();

    /// Print Wishlist
    void printUserAdoptionList();

    /// Print Database
    void printDogsInDatabase();

    /// See Dogs
    void seeDogs();

    /// Add, Delete, Update
    void addFunctionalityUi();
    void deleteFunctionalityUi();
    void updateFunctionalityUi();
};
