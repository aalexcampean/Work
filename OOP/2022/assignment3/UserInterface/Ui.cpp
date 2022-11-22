#include "Ui.h"

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

/// Constructors, Destructor
UserInterface::UserInterface(BaseService *providedAdminService, BaseService *providedUserService) {
    this->adminService = providedAdminService;
    this->userService = providedUserService;
}

UserInterface::UserInterface(UserInterface &ui) {
    this->adminService = ui.adminService;
    this->userService = ui.userService;
}

UserInterface::~UserInterface() {
}

/// Start
void UserInterface::start() {
    /// Populating The Database With The First 11 Dogs
    this->adminService->firstDogs();
    bool ok = false;
    std::string option;

    while (!ok) {
        this->printStartMenu();
        getline(std::cin, option);

        if (option == "1") {
            if (this->handleUserPassword()) {
                ok = true;
                this->startAdministrator();
            } else {
                std::cout << "Try again" << std::endl;
                std::cout << "" << std::endl;
            }
        } else if (option == "2") {
            ok = true;
            this->startUser();
        } else {
            std::cout << "No such command" << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void UserInterface::startAdministrator() {
    bool ok = false;
    std::string option;

    while (!ok) {
        try {
            this->printAdministratorMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->deleteFunctionalityUi();
            } else if (option == "3") {
                this->updateFunctionalityUi();
            } else if (option == "4") {
                this->printDogsInDatabase();
            } else if (option == "0") {
                std::cout << "" << std::endl;
                std::cout << "Bye bye!" << std::endl;
                ok = true;
            } else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string exp) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exp << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void UserInterface::startUser() {
    bool ok = false;
    std::string option;

    while (!ok) {
        try {
            this->printUserMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);
            if (option == "1") {
                this->seeDogs();
            } else if (option == "2") {
                this->printUserAdoptionList();
            } else if (option == "3") {
                this->printDogsInDatabase();
            } else if (option == "0") {
                ok = true;
            } else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string exp) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exp << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

/// Read user's password
bool UserInterface::handleUserPassword() {
    std::string correct_password = "***";
    std::string password = "";

    std::cout << "Please enter the password: " << std::endl;
    getline(std::cin, password);

    if (password == correct_password) {
        std::cout << BOLDGREEN << "Access granted" << RESET << std::endl;
        std::cout << "" << std::endl;
        return true;
    } else {
        std::cout << BOLDRED << "Access denied" << RESET << std::endl;
        std::cout << "" << std::endl;
        return false;
    }
}

/// Print Menus
void UserInterface::printStartMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Administrator" << std::endl;
    std::cout << "------2. User" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UserInterface::printAdministratorMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add dog" << std::endl;
    std::cout << "------2. Delete dog" << std::endl;
    std::cout << "------3. Update dog" << std::endl;
    std::cout << "------4. Show dogs" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UserInterface::printUserMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. See dogs" << std::endl;
    std::cout << "------2. See adoption list" << std::endl;
    std::cout << "------3. Show dogs" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

/// Print Wishlist
void UserInterface::printUserAdoptionList() {
    std::cout << "" << std::endl;
    for (int i = 0; i < this->userService->getServiceLength(); i++) {
        std::cout << this->userService->operator[](i).toString() << std::endl;
    }
}

/// Print Database
void UserInterface::printDogsInDatabase() {
    std::cout << "" << std::endl;
    for (int i = 0; i < this->adminService->getServiceLength(); i++) {
        std::cout << this->adminService->operator[](i).toString() << std::endl;
    }
}

/// Watch Movies
void UserInterface::seeDogs() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "What breed would you prefer?" << std::endl;
    std::cout << "Leave the field empty in order to see all breeds" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::string desiredBreed;
    getline(std::cin, desiredBreed);

    std::cout << "---------------------------" << std::endl;
    std::cout << "Choose an age to get all dos younger than" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::string desiredAge;
    getline(std::cin, desiredAge);

    double validatedAge;
    size_t pos1;
    try {
        validatedAge = std::stoi(desiredAge, &pos1);
    }
    catch (std::invalid_argument invalidArgument) {
        throw invalidArgument;
    }

    if (pos1 != desiredAge.size()) {
        throw std::string("Invalid numeric value for field age\n");
    }

    int database_copy_length = 0;
    Dog database_copy[this->adminService->getServiceLength()];
    database_copy_length = this->adminService->copyDatabase(database_copy, desiredBreed, validatedAge);

    bool done = false;
    int index = 0;
    std::string option;

    if (database_copy_length == 0) {
        std::cout << "" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "No dog of this breed" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "" << std::endl;
        done = true;
    }
    while (!done) {
        Dog currentDog = database_copy[index];
        index += 1;
        std::cout << currentDog.toString() << std::endl;
        std::string url = std::string("open ").append(currentDog.getImage());
//        system(url.c_str());

        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Adopt" << std::endl;
        std::cout << "2. Next dog" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "---------------------------" << std::endl;
        getline(std::cin, option);

        if (option == "1") {
            if (index == database_copy_length) {
                std::cout << "---------------------------" << std::endl;
                std::cout << "You've seen all of our fluffy friends, by choosing next, all dogs will be presented again"
                          << std::endl;
                std::cout << "---------------------------" << std::endl;
                index = 0;
            } else {
                try {
                    this->userService->addElementService(currentDog.getBreed(),
                                                         currentDog.getName(),
                                                         currentDog.getAge(),
                                                         currentDog.getImage());
                } catch (std::string exp) {
                    std::cout << "" << std::endl;
                    std::cout << BOLDRED << exp << RESET << std::endl;
                    std::cout << "" << std::endl;
                }
            }
        } else if (option == "2") {
            if (index == database_copy_length) {
                std::cout << "---------------------------" << std::endl;
                std::cout << "You've seen all of our fluffy friends, by choosing next, all dogs will be presented again"
                          << std::endl;
                std::cout << "---------------------------" << std::endl;
                index = 0;
            }
        } else if (option == "0") {
            done = true;
        } else {
            std::cout << "No such command!" << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

/// Add, Delete, Update
void UserInterface::addFunctionalityUi() {
    std::string inputBreed;
    std::string inputName;
    std::string inputAge;
    int validatedAge;
    std::string inputImage;

    std::cout << "" << std::endl;
    std::cout << "Breed: ";
    getline(std::cin, inputBreed);

    std::cout << "Name: ";
    getline(std::cin, inputName);

    std::cout << "Age: ";
    getline(std::cin, inputAge);

    std::cout << "Image: ";
    getline(std::cin, inputImage);

    /// Validating The Age
    size_t pos1;
    try {
        validatedAge = std::stoi(inputAge, &pos1);
        if (pos1 != inputAge.size()) {
            std::cout << "Invalid numeric value for field age\n";
        }
    }
    catch (std::invalid_argument) {
        std::cout << "Invalid numeric value for field age\n";
    }

    if (validatedAge < 0 || validatedAge > 30) {
        throw std::string("Invalid numeric value for a dog's age");
    }

    /// Validating The Dog's Image
    if (inputImage.rfind("https://", 0) != 0) {
        throw std::string("Invalid dog image");
    }

    /// Calling The Add Function For The Validated Input
    this->adminService->addElementService(inputBreed, inputName, validatedAge,
                                          inputImage);

    /// Printing A Message That The Movie Was Successfully Added
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Dog added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UserInterface::deleteFunctionalityUi() {
    std::string inputImage;

    std::cout << "" << std::endl;
    std::cout << "Image: ";
    getline(std::cin, inputImage);

    /// Validating The Dog's Image
    if (inputImage.rfind("https://", 0) != 0) {
        throw std::string("Invalid dog image");
    }

    /// Calling The Delete Function For The Validated Input
    this->adminService->deleteElementService(inputImage);

    /// Printing A Message That The Movie Was Successfully Deleted
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Dog deleted successfully" << RESET << std::endl;
    std::cout << "" << std::endl;

}

void UserInterface::updateFunctionalityUi() {
    std::string inputBreed;
    std::string inputName;
    std::string inputAge;
    int validatedAge;
    std::string inputImage;

    std::cout << "" << std::endl;
    std::cout << "Breed: ";
    getline(std::cin, inputBreed);

    std::cout << "Name: ";
    getline(std::cin, inputName);

    std::cout << "Age: ";
    getline(std::cin, inputAge);

    std::cout << "Image: ";
    getline(std::cin, inputImage);

    /// Validating The Age
    size_t pos1;
    try {
        validatedAge = std::stoi(inputAge, &pos1);
        if (pos1 != inputAge.size()) {
            std::cout << "Invalid numeric value for field age\n";
        }
    }
    catch (std::invalid_argument) {
        std::cout << "Invalid numeric value for field age\n";
    }

    if (validatedAge < 0 || validatedAge > 30) {
        throw std::string("Invalid numeric value for a dog's age");
    }

    /// Validating The Dog's Image

    if (inputImage.rfind("https://", 0) != 0) {
        throw std::string("Invalid dog image");
    }

    /// Calling The Update Function For The Validated Input
    this->adminService->updateElementService(inputBreed, inputName, validatedAge,
                                             inputImage);

    /// Printing A Message That The Movie Was Successfully Updated
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Dog updated successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

