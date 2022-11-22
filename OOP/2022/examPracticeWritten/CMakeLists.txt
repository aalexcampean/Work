cmake_minimum_required(VERSION 3.21)
project(exam_practice_written)

set(CMAKE_CXX_STANDARD 14)

add_executable(exam_practice_written
        Sale/Sale.cpp
        Sale/Sale.h
        SaleItem/SaleItem.cpp
        SaleItem/SaleItem.h
        Discount/Discount.cpp
        Discount/Discount.h
        main.cpp)
