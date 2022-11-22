cmake_minimum_required(VERSION 3.21)
project(exam-practice-task-manager)

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

add_executable(exam-practice-task-manager
        Domain/Task.cpp
        Domain/Task.h
        Domain/Programmer.cpp
        Domain/Programmer.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        Repository/TaskRepo.cpp
        Repository/TaskRepo.h
        Repository/ProgrammerRepo.cpp
        Repository/ProgrammerRepo.h
        Widgets/ProgrammerWidget.cpp
        Widgets/ProgrammerWidget.h
        Observer.cpp
        Observer.h
        Start.cpp)

target_link_libraries(exam-practice-task-manager
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

