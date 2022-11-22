cmake_minimum_required(VERSION 3.17)
project(a10_912_Campean_Catalin-1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(Domain)
include_directories(DynamicArray)

set(CMAKE_PREFIX_PATH "/Users/alexcampean/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(a10_912_Campean_Catalin-1
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
        Gui/gui.cpp
        Gui/gui.h
        Gui/MoviesTableModel.cpp
        Gui/MoviesTableModel.h
        Operation/Operation.cpp
        Operation/Operation.h
        Operation/OperationExecution.cpp
        Operation/OperationExecution.h
        Start.cpp
        )

target_link_libraries(a10_912_Campean_Catalin-1
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )