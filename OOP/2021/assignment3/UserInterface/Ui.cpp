#include "../UserInterface/Ui.h"
#include <iostream>
#include <string>
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

// Constructor, Destructor

UserInterface::UserInterface() {
    AdminService designated_admin_service;
    UserService designated_user_service;

    this->adminService = designated_admin_service;
    this->userService = designated_user_service;
}

UserInterface::UserInterface(UserInterface &ui) {
    this->adminService = ui.adminService;
    this->userService = ui.userService;
}

UserInterface::~UserInterface() {
}

// Start

void UserInterface::start(){
    // populating the database with the first 10 movies
    this->adminService.firstMovies();
    bool ok = false;
    std::string option;

    while (!ok) {
        this->printStartMenu();
        getline(std::cin, option);

        if (option == "1") {
            if (this->handleUserPassword()){
                ok = true;
                this->startAdministrator();
            }
            else {
                std::cout << "Try again" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        else if (option == "2"){
            ok = true;
            this->startUser();
        }
        else {
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
                this->printMoviesInDatabase();
            } else if (option == "0") {
                std::cout << "" << std::endl;
                std::cout << "Bye bye!" << std::endl;
                ok = true;
            } else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string exp){
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
                this->watchMovies();
            }
            else if (option == "2") {
                this->printUserWishlist();
            }
            else if (option == "3") {
                this->modifyWishlist();
            }
            else if (option == "4") {
                this->printMoviesInDatabase();
            }
            else if (option == "0") {
                ok = true;
            }
            else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string exp){
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exp << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

// Read user's password

bool UserInterface::handleUserPassword(){
    std::string correct_password = "*****";
    std::string password = "";

    std::cout << "Please enter the password: " << std::endl;
    getline(std::cin, password);

    if( password == correct_password ){
        std::cout << BOLDGREEN << "Access granted" << RESET << std::endl;
        std::cout << "" << std::endl;
        return true;
    }
    else {
        std::cout << BOLDRED << "Access denied" << RESET << std::endl;
        std::cout << "" << std::endl;
        return false;
    }
}

// Print Menu

void UserInterface::printStartMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Administrator" << std::endl;
    std::cout << "------2. User" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UserInterface::printAdministratorMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add movie" << std::endl;
    std::cout << "------2. Delete movie" << std::endl;
    std::cout << "------3. Update movie" << std::endl;
    std::cout << "------4. Show movies" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UserInterface::printUserMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Watch movies" << std::endl;
    std::cout << "------2. See watch list" << std::endl;
    std::cout << "------3. Modify wishlist" << std::endl;
    std::cout << "------4. Show movies" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

// Print Wishlist

void UserInterface::printUserWishlist() {
    std::cout << "" << std::endl;
    for (int i = 0; i < this->userService.getUserServiceLength(); i++) {
        std::cout << this->userService[i].toString() << std::endl;
    }
}

// Print Database

void UserInterface::printMoviesInDatabase() {
    std::cout << "" << std::endl;
    for (int i = 0; i < this->adminService.getAdminServiceLength(); i++) {
        std::cout << this->adminService[i].toString() << std::endl;
    }
}

// Watch Movies

void UserInterface::watchMovies(){
    std::cout << "---------------------------" << std::endl;
    std::cout << "What genre would you prefer?" << std::endl;
    std::cout << "Leave the field empty in order to see all genres" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::string given_genre;
    getline(std::cin, given_genre);

    int database_copy_length = 0;
    Movie database_copy[this->adminService.getAdminServiceLength()];
    database_copy_length = this->adminService.copyDatabase(database_copy, given_genre);

    bool done = false;
    int index = 0;
    std::string option;

    if (database_copy_length == 0){
        std::cout << "" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "No movie with this genre" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "" << std::endl;
        done = true;
    }
    while (!done){
        Movie current_movie = database_copy[index];
        std::cout << current_movie.toString() << std::endl;
        std::string url = std::string("open ").append(current_movie.getTrailer());
        system(url.c_str());

        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Add to wishlist" << std::endl;
        std::cout << "2. Next movie" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "---------------------------" << std::endl;
        getline(std::cin, option);

        if (option == "1"){
            index += 1;
            this->userService.addElementUserService(current_movie.getTitle(),
                                                    current_movie.getGenre(),
                                                    current_movie.getYearOfRelease(),
                                                    current_movie.getNrOfLikes(),
                                                    current_movie.getTrailer());}
            if (index == database_copy_length){
                std::cout << "---------------------------" << std::endl;
                std::cout << "You've got a taste of all of our movies, by choosing next, all movies will be presented again" << std::endl;
                std::cout << "---------------------------" << std::endl;
                index = 0;
            }
        else if (option == "2"){
            if (index == database_copy_length){
                std::cout << "---------------------------" << std::endl;
                std::cout << "You've got a taste of all of our movies, by choosing next, all movies will be presented again" << std::endl;
                std::cout << "---------------------------" << std::endl;
                index = 0;
            }
            else {
                index += 1;
            }
        }
        else if (option == "0"){
            done = true;
        }
    }
}

// Modify wishlist

void UserInterface::modifyWishlist() {
    std::string option1;
    bool done = false;

    while (!done) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "1. See current wishlist" << std::endl;
        std::cout << "2. Delete movie" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "---------------------------" << std::endl;
        getline(std::cin, option1);

        if (option1 == "1") {
            this->printUserWishlist();
        }
        else if (option1 == "2") {
            std::string input_title;

            std::cout << "" << std::endl;
            std::cout << "Title: ";
            getline(std::cin, input_title);

            std::string option2;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Did you enjoy this movie?" << std::endl;
            std::cout << "1. Yes, I'd give it a like" << std::endl;
            std::cout << "2. No, not really, it was average" << std::endl;
            std::cout << "---------------------------" << std::endl;
            getline(std::cin, option2);

            if (option2 == "1") {
                Movie desired_element = this->adminService.getElementByUniqueField(input_title);
                this->adminService.updateElementAdminService(desired_element.getTitle(),
                                                             desired_element.getGenre(),
                                                             desired_element.getYearOfRelease(),
                                                             desired_element.getNrOfLikes() + 1,
                                                             desired_element.getTrailer());
            }
            this->userService.deleteElementUserService(input_title);
            // printing a message that the movie was successfully deleted
            std::cout << "" << std::endl;
            std::cout << BOLDGREEN << "Movie deleted" << RESET << std::endl;
            std::cout << "" << std::endl;
        }
        else if (option1 == "0") {
            done = true;
        }
        else {
            std::cout << "No such command!" << std::endl;
            std::cout << "" << std::endl;
        }
    }

}

// Add, Delete, Update

void UserInterface::addFunctionalityUi() {
    std::string input_title;
    std::string input_genre;
    std::string input_year_of_release;
    int validated_year_of_release;
    std::string input_nr_of_likes;
    int validated_nr_of_likes;
    std::string input_trailer;

    std::cout << "" << std::endl;
    std::cout << "Title: ";
    getline(std::cin, input_title);

    std::cout << "Genre: ";
    getline(std::cin, input_genre);

    std::cout << "Year of Release: ";
    getline(std::cin, input_year_of_release);

    std::cout << "Number of Likes: ";
    getline(std::cin, input_nr_of_likes);

    std::cout << "Trailer: ";
    getline(std::cin, input_trailer);

    // validating the year of release
    size_t pos1;
    try {
        validated_year_of_release = std::stoi(input_year_of_release, &pos1);
        if (pos1 != input_year_of_release.size()) {
            std::cout << "Invalid numeric value for field year\n";
        }
    }
    catch (std::invalid_argument) {
        std::cout << "Invalid numeric value for field year\n";
    }

    if (validated_year_of_release < 1000) {
        throw std::string("Invalid numeric value for a movie's year of release");
    }

    // validating the number of likes
    size_t pos2;
    try {
        validated_nr_of_likes = std::stoi(input_nr_of_likes, &pos2);
        if (pos2 != input_year_of_release.size()) {
            std::cout << "Invalid numeric value for number of likes\n";
        }
    }
    catch (std::invalid_argument) {
        std::cout << "Invalid numeric value for number of likes\n";
    }

    if (validated_nr_of_likes < 0) {
        throw std::string("Invalid numeric value for a movie's number of likes");
    }

    // validating the trailer link

    if (input_trailer.rfind("https/", 0) != 0) {
        throw std::string("Invalid trailer link");
    }

    // actually calling the add function for the validated input
    this->adminService.addElementAdminService(input_title, input_genre, validated_year_of_release, validated_nr_of_likes,
                                              input_trailer);

    // printing a message that the movie was successfully added
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Movie added" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UserInterface::deleteFunctionalityUi() {
    std::string input_title;

    std::cout << "" << std::endl;
    std::cout << "Title: ";
    getline(std::cin, input_title);

    // calling the delete function
    this->adminService.deleteElementAdminService(input_title);

    // printing a message that the movie was successfully deleted
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN<< "Movie deleted" << RESET << std::endl;
    std::cout << "" << std::endl;

}

void UserInterface::updateFunctionalityUi() {
    std::string input_title;
    std::string input_genre;
    std::string input_year_of_release;
    int validated_year_of_release;
    std::string input_nr_of_likes;
    int validated_nr_of_likes;
    std::string input_trailer;

    std::cout << "" << std::endl;
    std::cout << "Title: ";
    getline(std::cin, input_title);

    std::cout << "Genre: ";
    getline(std::cin, input_genre);

    std::cout << "Year of Release: ";
    getline(std::cin, input_year_of_release);

    std::cout << "Number of Likes: ";
    getline(std::cin, input_nr_of_likes);

    std::cout << "Trailer: ";
    getline(std::cin, input_trailer);

    // validating the year of release
    size_t pos1;
    try {
        validated_year_of_release = std::stoi(input_year_of_release, &pos1);
        if (pos1 != input_year_of_release.size()){
            std::cout << "Invalid numeric value for field year\n";
        }
    }
    catch (std::invalid_argument){
        std::cout << "Invalid numeric value for field year\n";
    }

    if (validated_year_of_release < 1000) {
        throw std::string("Invalid numeric value for a movie's year of release");
    }

    // validating the number of likes
    size_t pos2;
    try {
        validated_nr_of_likes = std::stoi(input_nr_of_likes, &pos2);
        if (pos2 != input_year_of_release.size()){
            std::cout << "Invalid numeric value for number of likes\n";
        }
    }
    catch (std::invalid_argument){
        std::cout << "Invalid numeric value for number of likes\n";
    }

    if (validated_nr_of_likes < 0) {
        throw std::string("Invalid numeric value for a movie's number of likes");
    }

    // validating the trailer link

    if (input_trailer.rfind("https/", 0) != 0){
        throw std::string("Invalid trailer link");
    }

    // actually calling the update function for the validated input
    this->adminService.updateElementAdminService(input_title, input_genre, validated_year_of_release, validated_nr_of_likes, input_trailer);

    // printing a message that the movie was successfully updated
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Movie updated" << RESET << std::endl;
    std::cout << "" << std::endl;
}

