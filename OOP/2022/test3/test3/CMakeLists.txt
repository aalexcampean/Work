cmake_minimum_required(VERSION 3.21)
project(t3_aalexcampean)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

include_directories(Domain)
include_directories(Repository)
include_directories(Service)
include_directories(GUI)

set(CMAKE_PREFIX_PATH "/Users/alexcampean/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(t3_aalexcampean
        Domain/Equation.cpp
        Domain/Equation.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        GUI/GUI.cpp
        GUI/GUI.h
        Repository/FileRepository.cpp
        Repository/FileRepository.h
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        Start.cpp)

target_link_libraries(t3_aalexcampean
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )