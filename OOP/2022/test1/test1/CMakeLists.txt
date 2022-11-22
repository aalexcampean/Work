cmake_minimum_required(VERSION 3.21)
project(t1_aalexcampean)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(t1_aalexcampean
        Domain/Bill.cpp
        Domain/Bill.h
        Start.cpp Repository/Repository.cpp Repository/Repository.h Service/Service.cpp Service/Service.h UserInterface/Ui.cpp UserInterface/Ui.h Tests/Tests.cpp Tests/Tests.h)
