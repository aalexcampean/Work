cmake_minimum_required(VERSION 3.17)
project(a67_912_Campean_Catalin)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(DynamicArray)

add_executable(a67_912_Campean_Catalin
        Exception/CustomException.h
        Exception/CustomException.cpp
        Validator/EntityValidator.h
        Validator/EntityValidator.cpp
        Domain/Movie.h
        Domain/Movie.cpp
        MemoryRepository/MemoryRepo.h
        MemoryRepository/MemoryRepo.cpp
        TextRepository/TextRepo.h
        TextRepository/TextRepo.cpp
        HtmlRepository/HtmlRepo.cpp
        HtmlRepository/HtmlRepo.h
        CsvRepository/CsvRepo.cpp
        CsvRepository/CsvRepo.h
        Service/AdminService.h
        Service/AdminService.cpp
        Service/UserService.h
        Service/UserService.cpp
        UserInterface/Ui.h
        UserInterface/Ui.cpp
        Tests/Tests.h
        Tests/Tests.cpp
        Start.cpp
        )
