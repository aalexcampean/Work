//
// Created by Alex Campean on 03.04.2022.
//

#include "UserInterface/Ui.h"

int main(){
    /// Admin Assemble
    TextFileRepository adminRepository("Database.txt", "Database.txt");
    AdminService adminService(&adminRepository);

    /// User Assemble
    TextFileRepository userRepository("AdoptionList.txt", "Database.txt");
    UserService userService(&userRepository);

    /// User Interface Assemble
    UserInterface userInterface(&adminService, &userService);

    /// Start
    userInterface.start();
}