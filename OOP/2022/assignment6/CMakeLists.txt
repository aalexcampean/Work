cmake_minimum_required(VERSION 3.21)
project(a14_aalexcampean)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

include_directories(Domain)
include_directories(Domain/Validator)
include_directories(Exception)
include_directories(GUI)
include_directories(Repository/CSV)
include_directories(Repository/HTML)
include_directories(Repository/InMemory)
include_directories(Repository/TextFile)
include_directories(Service)

set(CMAKE_PREFIX_PATH "/Users/alexcampean/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(a14_aalexcampean
        Domain/Validator/DogValidator.cpp
        Domain/Validator/DogValidator.h
        Domain/Dog.cpp
        Domain/Dog.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        GUI/DogsTableModel.cpp
        GUI/DogsTableModel.h
        GUI/GUI.cpp
        GUI/GUI.h
        Repository/CSV/CSVRepository.cpp
        Repository/CSV/CSVRepository.h
        Repository/HTML/HTMLRepository.cpp
        Repository/HTML/HTMLRepository.h
        Repository/InMemory/InMemoryRepository.cpp
        Repository/InMemory/InMemoryRepository.h
        Repository/TextFile/TextFileRepository.cpp
        Repository/TextFile/TextFileRepository.h
        Service/AdminService.cpp
        Service/AdminService.h
        Service/UserService.cpp
        Service/UserService.h
        Operation/Operation.cpp
        Operation/Operation.h
        Operation/OperationExecution.cpp
        Operation/OperationExecution.h
        main.cpp)

target_link_libraries(a14_aalexcampean
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )