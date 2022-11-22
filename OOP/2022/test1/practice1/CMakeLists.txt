cmake_minimum_required(VERSION 3.21)
project(t1_practice1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t1_practice1
        Domain/Gene.cpp
        Domain/Gene.h
        Repository/Repository.cpp
        Repository/Repository.h Service/Service.cpp Service/Service.h Tests/Tests.cpp Tests/Tests.h Start.cpp UserInterface/UI.cpp UserInterface/UI.h)
