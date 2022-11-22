cmake_minimum_required(VERSION 3.21)
project(t3_practice3)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(Repository)
include_directories(Service)
include_directories(UI)

add_executable(t3_practice3
        Domain/Block.cpp
        Domain/Block.h
        Domain/Building.cpp
        Domain/Building.h
        Domain/House.cpp
        Domain/House.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        UI/UI.cpp
        UI/UI.h
        Start.cpp)
