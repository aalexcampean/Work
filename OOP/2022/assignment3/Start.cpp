//
// Created by Alex Campean on 03.04.2022.
//

#include "Tests/Tests.h"
#include "UserInterface/Ui.h"

int main(){
    /// Run Tests
    testAll();

    /// Admin Assemble
    AdminRepository adminRepository;
    AdminService adminService(&adminRepository);

    /// User Assemble
    UserRepository userRepository;
    UserService userService(&userRepository);

    /// User Interface Assemble
    UserInterface userInterface(&adminService, &userService);

    /// Start
    userInterface.start();
}