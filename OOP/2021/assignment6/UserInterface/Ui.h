#pragma once
#include "../Service/AdminService.h"
#include "../Service/UserService.h"

class UserInterface{
private:
    AdminService adminService;
    UserService userService;

public:

    // Constructor, Destructor

    UserInterface();
    UserInterface(UserInterface &ui);
    ~UserInterface();

    // Set service
    void setService();

    // Start

    /// <summary>Starts the ui</summary>
    /// <param name=""></param>
    /// <returns></returns
    void start();

    /// <summary>Starts the ui for in administrator mode</summary>
    /// <param name=""></param>
    /// <returns></returns
    void startAdministrator();

    /// <summary>Starts the ui in the user mode</summary>
    /// <param name=""></param>
    /// <returns></returns
    void startUser();

    // Read user's password

    bool handleUserPassword();

    // Print Menu

    /// <summary>Prints the menu of the application</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printStartMenu();

    /// <summary>Prints the menu for the administrator of the application</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printAdministratorMenu();

    /// <summary>Prints the menu for the user of the application</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printUserMenu();

    // Print Wishlist.txt

    /// <summary>Prints the wishlst of the user</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printUserWishlist();

    // Print Database

    /// <summary>Prints all the elements from the adminService->repository->dynamic array</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printMoviesInDatabase();

    // Watch Movies

    /// <summary>Shows the movies from the database of a given genre one by one and plays the trailer in the browser</summary>
    /// <param name=""></param>
    /// <returns>Prints the according messages</returns
    void watchMovies();

    // Modify wishlist

    /// <summary>Gives the user the permission to change change the wishlist once they see a movie</summary>
    /// <param name=""></param>
    /// <returns>Prints the according messages</returns
    void modifyWishlist();

    // Add, Delete, Update

    /// <summary>Prepares the addition of an element to the adminService layer</summary>
    /// <param name=""></param>
    /// <returns>Performs the operation if able or prints a message otherwise</returns
    void addFunctionalityUi();

    /// <summary>Prepares the deletion of an element from the adminService layer</summary>
    /// <param name=""></param>
    /// <returns>Performs the operation if able or prints a message otherwise</returns
    void deleteFunctionalityUi();

    /// <summary>Prepares the update of an element in the adminService layer</summary>
    /// <param name=""></param>
    /// <returns>Performs the operation if able or prints a message otherwise</returns
    void updateFunctionalityUi();
};
