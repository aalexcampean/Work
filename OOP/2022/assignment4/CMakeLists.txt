cmake_minimum_required(VERSION 3.21)
project(a8_9_aalexcampean)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(Repository)
include_directories(Service)
include_directories(Tests)
include_directories(UserInterface)

add_executable(a8_9_aalexcampean
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
        UserInterface/Ui.cpp
        UserInterface/Ui.h
        Start.cpp)
