cmake_minimum_required(VERSION 3.21)
project(t2_practice1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t2_practice1
        Start.cpp
        Domain/Appliance.cpp
        Domain/Appliance.h
        Domain/Refrigerator.cpp
        Domain/Refrigerator.h
        Domain/DishWasher.cpp
        Domain/DishWasher.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        UI/UI.cpp
        UI/UI.h)
