cmake_minimum_required(VERSION 3.21)
project(a89_912_Campean_Catalin)

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

include_directories(Domain)
include_directories(DynamicArray)

add_executable(a89_912_Campean_Catalin
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
        gui.cpp
        gui.h
        )

target_link_libraries(a89_912_Campean_Catalin
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )