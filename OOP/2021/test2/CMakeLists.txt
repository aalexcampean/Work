cmake_minimum_required(VERSION 3.19)
project(t2_912_Campean_Catalin_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t2_912_Campean_Catalin_1
        Domain/Measurement.cpp
        Domain/Measurement.h
        Domain/BMI.cpp
        Domain/BMI.h
        Domain/BP.cpp
        Domain/BP.h Person/Person.cpp Person/Person.h Exception/CustomException.cpp Exception/CustomException.h UserInterface/Ui.cpp UserInterface/Ui.h main.cpp)
