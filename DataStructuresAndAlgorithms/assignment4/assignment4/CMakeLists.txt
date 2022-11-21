cmake_minimum_required(VERSION 3.19)
project(Assignment_4_DSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment_4_DSA
        App.cpp
        Da.h
        Node.cpp
        Node.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h
        Exception/CustomException.h
        Exception/CustomException.cpp)
