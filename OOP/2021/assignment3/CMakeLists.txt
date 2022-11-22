cmake_minimum_required(VERSION 3.17)
project(a45_912_Campean_Catalin)

set(CMAKE_CXX_STANDARD 14)

add_executable(a45_912_Campean_Catalin
        Domain/Movie.h
        Domain/Movie.cpp
        DynamicArray/Da.h
        Repository/AdminRepo.h
        Repository/AdminRepo.cpp
        Repository/UserRepo.h
        Repository/UserRepo.cpp
        Service/AdminService.h
        Service/AdminService.cpp
        Service/UserService.h
        Service/UserService.cpp
        Tests/Tests.h
        Tests/Tests.cpp
        UserInterface/Ui.h
        UserInterface/Ui.cpp
        Start.cpp)
