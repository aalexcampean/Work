cmake_minimum_required(VERSION 3.21)
project(a11_12_aalexcampean)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/alexcampean/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(a11_12_aalexcampean
        Domain/Dog.cpp
        Domain/Dog.h
        Domain/Validator/DogValidator.cpp
        Domain/Validator/DogValidator.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        Repository/InMemory/InMemoryRepository.cpp
        Repository/InMemory/InMemoryRepository.h
        Repository/TextFile/TextFileRepository.cpp
        Repository/TextFile/TextFileRepository.h
        Repository/CSV/CSVRepository.cpp
        Repository/CSV/CSVRepository.h
        Repository/HTML/HTMLRepository.cpp
        Repository/HTML/HTMLRepository.h
        Service/AdminService.cpp
        Service/AdminService.h
        Service/UserService.cpp
        Service/UserService.h
        GUI/GUI.cpp
        GUI/GUI.h
        main.cpp)

target_link_libraries(a11_12_aalexcampean
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

