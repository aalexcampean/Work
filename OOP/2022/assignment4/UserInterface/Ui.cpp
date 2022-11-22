#include "Ui.h"

#include "../Exception/CustomException.h"
#include "Validator/DogValidator.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

/// Constructors, Destructor
UserInterface::UserInterface(AdminService *providedAdminService, UserService *providedUserService) {
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
    bool ok = false;
    std::string option;

    while (!ok) {
        this->printStartMenu();
        getline(std::cin, option);

        if (option == "1") {
            try {
                this->handleUserPassword();
                this->startAdministrator();
            } catch (CustomException &exception) {
                std::cout << "" << std::endl;
                std::cout << BOLDRED << exception.what() << RESET << std::endl;
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
        catch (CustomException &exception) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exception.what() << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void UserInterface::startUser() {
    this->setService();
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
        catch (CustomException &exception) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exception.what() << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

/// Read user's password
void UserInterface::handleUserPassword() {
    std::string correct_password = "***";
    std::string password = "";

    std::cout << "Please enter the password: " << std::endl;
    getline(std::cin, password);

    if (password == correct_password) {
        std::cout << BOLDGREEN << "Access granted" << RESET << std::endl;
        std::cout << "" << std::endl;
    } else {
        throw CustomException(ExceptionTypes::LogInException);
    }
}

/// Set Repository Type
void UserInterface::setService() {
    std::string option;
    std::string type;

    std::cout << "Chose how to store your movie wishlist" << std::endl;
    std::cout << "1. Csv file" << std::endl;
    std::cout << "2. Html file" << std::endl;
    getline(std::cin, option);

    if (option == "1") {
        this->userService->setRepositoryType("csv");
    }
    else if (option == "2") {
        this->userService->setRepositoryType("html");
    }
    else {
        std::cout << "No such file type" << std::endl;
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
    this->userService->openFile();
//    std::cout << "" << std::endl;
//    for (int i = 0; i < this->userService->getServiceLength(); i++) {
//        std::cout << this->userService->operator[](i).toString() << std::endl;
//    }
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
    std::cout << "Choose an age to get all dogs younger than" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::string desiredAge;
    getline(std::cin, desiredAge);

    DogValidator::validateAge(desiredAge);
    size_t pos2;
    double validatedAge = std::stod(desiredAge, &pos2);

    std::vector<Dog> filteredDogs = this->adminService->filterByBreedAndAge(desiredBreed, validatedAge);

    bool done = false;
    int index = 0;
    std::string option;

    if (filteredDogs.empty()) {
        std::cout << "" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "No dog of this breed and age" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "" << std::endl;
        done = true;
    }
    while (!done) {
        Dog currentDog = filteredDogs[index];
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
            if (index == filteredDogs.size()) {
                std::cout << "" << std::endl;
                std::cout << BOLDGREEN
                          << "You've seen all of our fluffy friends, by choosing next, all dogs will be presented again"
                          << RESET << std::endl;
                std::cout << "" << std::endl;
                index = 0;
            } else {
                try {
                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(0) << currentDog.getAge();
                    std::string stringAge = stream.str();
                    this->userService->addElementService(currentDog.getBreed(),
                                                         currentDog.getName(),
                                                         stringAge,
                                                         currentDog.getImage());
                } catch (CustomException &exception) {
                    std::cout << "" << std::endl;
                    std::cout << BOLDRED << exception.what() << RESET << std::endl;
                    std::cout << "" << std::endl;
                }
            }
        } else if (option == "2") {
            if (index == filteredDogs.size()) {
                std::cout << "" << std::endl;
                std::cout << BOLDGREEN
                          << "You've seen all of our fluffy friends, by choosing next, all dogs will be presented again"
                          << RESET << std::endl;
                std::cout << "" << std::endl;
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

    /// Calling The Add Function For The Validated Input
    this->adminService->addElementService(inputBreed, inputName, inputAge,
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


    /// Calling The Update Function For The Validated Input
    this->adminService->updateElementService(inputBreed, inputName, inputAge,
                                             inputImage);

    /// Printing A Message That The Movie Was Successfully Updated
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Dog updated successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}