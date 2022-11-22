cmake_minimum_required(VERSION 3.21)
project(t1_practice3)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t1_practice3
        Domain/Task.cpp
        Domain/Task.h Repository/Repository.cpp Repository/Repository.h Service/Service.cpp Service/Service.h Tests/Tests.cpp Tests/Tests.h Start.cpp UserInterface/Ui.cpp UserInterface/Ui.h)
