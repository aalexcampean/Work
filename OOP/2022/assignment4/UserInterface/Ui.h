#pragma once

#include "../Service/AdminService.h"
#include "../Service/UserService.h"

class UserInterface{
private:
    AdminService* adminService;
    UserService* userService;

    void startAdministrator();
    void startUser();
    void handleUserPassword();
    void setService();

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

public:
    /// Constructors, Destructor
    UserInterface(AdminService* providedAdminService, UserService* providedUserService);
    UserInterface(UserInterface &ui);
    ~UserInterface();

    /// Start
    void start();
};
