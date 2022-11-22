cmake_minimum_required(VERSION 3.17)
project(Assignment1C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(..)
include_directories(.)

add_executable(Assignment1C__
        Graph.h
        Graph.cpp
        Ui.h
        Ui.cpp
        Start.cpp)
