cmake_minimum_required(VERSION 3.21)
project(a5_6_aalexcampean)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(a5_6_aalexcampean
        Domain/Dog.cpp
        Domain/Dog.h
        DynamicArray/Da.h
        Repository/UserRepository.cpp
        Repository/UserRepository.h
        Repository/AdminRepository.cpp
        Repository/AdminRepository.h
        Service/UserService.cpp
        Service/UserService.h
        Tests/Tests.cpp
        Tests/Tests.h
        Start.cpp
        Repository/BaseRepository.cpp
        Repository/BaseRepository.h
        Service/BaseService.cpp
        Service/BaseService.h
        Service/AdminService.cpp
        Service/AdminService.h
        UserInterface/Ui.cpp
        UserInterface/Ui.h)
