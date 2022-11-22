cmake_minimum_required(VERSION 3.17)
project(t1_912_Campean_Catalin_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t1_912_Campean_Catalin_1
        Domain/Gene.cpp
        Domain/Gene.h
        DynamicArray/Da.h
        Repository/Repository.h
        Repository/Repository.cpp
        Service/Service.h
        Service/Service.cpp
        User_Interface/Ui.h
        User_Interface/Ui.cpp
        Start.cpp)
