cmake_minimum_required(VERSION 3.21)
project(t2_aalexcampean)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(Service)
include_directories(UI)

add_executable(t2_aalexcampean
        Domain/Car.cpp
        Domain/Car.h
        Domain/ElectricEngine.cpp
        Domain/ElectricEngine.h
        Domain/Engine.cpp
        Domain/Engine.h
        Domain/TurboEngine.cpp
        Domain/TurboEngine.h
        Service/Service.cpp
        Service/Service.h
        UI/UI.cpp
        UI/UI.h
        Start.cpp)
