cmake_minimum_required(VERSION 3.17)
project(Assignment1_DSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment1_DSA
        Bag.h
        Bag.cpp
        BagIterator.h
        BagIterator.cpp
        ShortTest.h
        ShortTest.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        app.cpp)