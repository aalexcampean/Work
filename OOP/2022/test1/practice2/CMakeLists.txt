cmake_minimum_required(VERSION 3.21)
project(t1_practice2)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_practice2
        Domain/Project.cpp
        Domain/Project.h
        Start.cpp Repository/Repository.cpp Repository/Repository.h Service/Service.cpp Service/Service.h Tests/Tests.cpp Tests/Tests.h UserInterface/Ui.cpp UserInterface/Ui.h)
