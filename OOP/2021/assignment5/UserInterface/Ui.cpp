#include "../UserInterface/Ui.h"
#include "../Validator/EntityValidator.h"
#include <iostream>
#include <string>
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

// Constructor, Destructor

UserInterface::UserInterface() {
    AdminService as;
    UserService us;
    this->adminService = as;
    this->userService = us;
}

UserInterface::UserInterface(UserInterface &ui) {
    this->adminService = ui.adminService;
    this->userService = ui.userService;
}

UserInterface::~UserInterface() {
}

// Set service

void UserInterface::setService() {
    std::string option;
    std::string type;

    std::cout << "Chose how to store your movie wishlist" << std::endl;
    std::cout << "1. Csv file" << std::endl;
    std::cout << "2. Html file" << std::endl;
    getline(std::cin, option);

    if (option == "1") {
        this->userService.setRepoType("csv");
    }
    else if (option == "2") {
        this->userService.setRepoType("html");
    }
    else {
        std::cout << "No such file type" << std::endl;
    }
}

// Start

void UserInterface::start(){
    // populating the database with the first 10 movies
//    this->adminService.firstMovies();
    bool ok = false;
    std::string option;

    while (!ok) {
        this->printStartMenu();
        getline(std::cin, option);

        if (option == "1") {
            if (this->handleUserPassword()){
                this->startAdministrator();
            }
            else {
                std::cout << "Try again" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        else if (option == "2"){
            this->startUser();
        }
        else if (option == "0") {
            ok = true;
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
        catch (const CustomException &e){
            std::cout << "" << std::endl;
            std::cout << BOLDRED << e.what() << RESET << std::endl;
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
                this->watchMovies();
            }
            else if (option == "2") {
                this->printUserWishlist();
            }
            else if (option == "3") {
                this->modifyWishlist();
            }
            else if (option == "0") {
                ok = true;
            }
            else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (const CustomException &e){
            std::cout << "" << std::endl;
            std::cout << BOLDRED << e.what() << RESET << std::endl;
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
    std::cout << "------0. Exit" << std::endl;
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
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

// Print Wishlist.txt

void UserInterface::printUserWishlist() {
    std::cout << "" << std::endl;
    std::cout << this->userService << std::endl;
}

// Print Database

void UserInterface::printMoviesInDatabase() {
    std::cout << "" << std::endl;
    std::cout << this->adminService << std::endl;
}

// Watch Movies

void UserInterface::watchMovies(){
    std::cout << "---------------------------" << std::endl;
    std::cout << "What genre would you prefer?" << std::endl;
    std::cout << "Leave the field empty in order to see all genres" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::string given_genre;
    getline(std::cin, given_genre);

    std::vector<Movie> database_copy = this->adminService.copyDatabase(given_genre);

    bool done = false;
    int index = 0;
    std::string option;

    if (database_copy.empty()){
        std::cout << "" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "No movie with this genre" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "" << std::endl;
    }
    else {
        while (!done) {
            Movie current_movie = database_copy[index];
            std::cout <<"Title: " << current_movie.getTitle() << "  |  "
                << "Genre: " << current_movie.getGenre() << "  |  "
                << "Year of Release: " << current_movie.getYearOfRelease() << "  |  "
                << "Number of Likes"<< current_movie.getNrOfLikes() << "  |  "
                << "Trailer" << current_movie.getTrailer() << std::endl;
            std::string url = std::string("open ").append(current_movie.getTrailer());
            system(url.c_str());

            std::cout << "---------------------------" << std::endl;
            std::cout << "1. Add to wishlist" << std::endl;
            std::cout << "2. Next movie" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "---------------------------" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                if (index == database_copy.size()) {
                    std::cout << "" << std::endl;
                    std::cout << BOLDGREEN << "You've got a taste of all of our movies, by choosing next, all movies will be presented again" << RESET << std::endl;
                    std::cout << "" << std::endl;
                    index = 0;
                }
                else {
                    if (this->userService.findElement(this->adminService.getDataBase()[index].getTitle())) {
                        std::cout << "" << std::endl;
                        std::cout << BOLDRED << "Movie has been already added to your wishlist" << RESET << std::endl;
                        std::cout << "" << std::endl;
                    }
                    else {
                        this->userService.addElement(current_movie.getTitle(), current_movie.getGenre(), current_movie.getYearOfRelease(), current_movie.getNrOfLikes(), current_movie.getTrailer());
                        std::cout << "" << std::endl;
                        std::cout << BOLDGREEN << "Movie added to your wishlist" << RESET << std::endl;
                        std::cout << "" << std::endl;
                    }
                    index += 1;
                }
            }
            else if (option == "2") {
                if (index == database_copy.size()) {
                    std::cout << "" << std::endl;
                    std::cout << BOLDGREEN
                              << "You've got a taste of all of our movies, by choosing next, all movies will be presented again"
                              << RESET << std::endl;
                    std::cout << "" << std::endl;
                    index = 0;
                }
                else {
                    index += 1;
                }
            }
            else if (option == "0") {
                done = true;
                this->userService.openFile();
            }
            else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
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

            if (this->userService.findElement(input_title)) {
                std::string option2;
                std::cout << "---------------------------" << std::endl;
                std::cout << "Did you enjoy this movie?" << std::endl;
                std::cout << "1. Yes, I'd give it a like" << std::endl;
                std::cout << "2. No, not really, it was average" << std::endl;
                std::cout << "---------------------------" << std::endl;
                getline(std::cin, option2);

                if (option2 == "1") {
                    Movie desired_element = this->adminService.getElementByTitle(input_title);
                    this->adminService.updateElement(desired_element.getTitle(), desired_element.getGenre(), std::to_string(desired_element.getYearOfRelease()),std::to_string(desired_element.getNrOfLikes() + 1), desired_element.getTrailer());
                    this->userService.deleteElement(input_title);
                    // printing a message that the movie was successfully deleted
                    std::cout << "" << std::endl;
                    std::cout << BOLDGREEN << "Movie deleted" << RESET << std::endl;
                    std::cout << "" << std::endl;
                }
                else if (option2 == "2") {
                    this->userService.deleteElement(input_title);
                    // printing a message that the movie was successfully deleted
                    std::cout << "" << std::endl;
                    std::cout << BOLDGREEN << "Movie deleted" << RESET << std::endl;
                    std::cout << "" << std::endl;
                }
                else {
                    std::cout << "No such command!" << std::endl;
                    std::cout << "" << std::endl;
                }
            }
            else {
                std::cout << "" << std::endl;
                std::cout << BOLDRED << "This movie does not exist in your wishlist" << RESET << std::endl;
                std::cout << "" << std::endl;
            }
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
    std::string input_nr_of_likes;
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

    bool added = true;

    try {
        this->adminService.addElement(input_title, input_genre, input_year_of_release, input_nr_of_likes, input_trailer);
    }
    catch (const CustomException& e) {
        std::cout << "" << std::endl;
        std::cout << BOLDRED << e.what() << RESET << std::endl;
        std::cout << "" << std::endl;
        added = false;
    }

    // printing a message that the movie was successfully added
    if (added){
        std::cout << "" << std::endl;
        std::cout << BOLDGREEN << "Movie added" << RESET << std::endl;
        std::cout << "" << std::endl;
    }
}

void UserInterface::deleteFunctionalityUi() {
    std::string input_title;

    std::cout << "" << std::endl;
    std::cout << "Title: ";
    getline(std::cin, input_title);

    bool deleted = true;

    try {
        this->adminService.deleteElement(input_title);
    }
    catch (const CustomException& e) {
        std::cout << "" << std::endl;
        std::cout << BOLDGREEN << e.what() << RESET << std::endl;
        std::cout << "" << std::endl;
        deleted = false;
    }

    // printing a message that the movie was successfully deleted
    if (deleted) {
        std::cout << "" << std::endl;
        std::cout << BOLDGREEN<< "Movie deleted" << RESET << std::endl;
        std::cout << "" << std::endl;
    }
}

void UserInterface::updateFunctionalityUi() {
    std::string input_title;
    std::string input_genre;
    std::string input_year_of_release;
    std::string input_nr_of_likes;
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

    bool updated = true;

    try {
        this->adminService.updateElement(input_title, input_genre, input_year_of_release, input_nr_of_likes, input_trailer);
    }
    catch (const CustomException& e) {
        std::cout << "" << std::endl;
        std::cout << BOLDRED << e.what() << RESET << std::endl;
        std::cout << "" << std::endl;
        updated = false;
    }

    // printing a message that the movie was successfully updated
    if (updated) {
        std::cout << "" << std::endl;
        std::cout << BOLDGREEN << "Movie updated" << RESET << std::endl;
        std::cout << "" << std::endl;
    }
}

