cmake_minimum_required(VERSION 3.21)
project(e911-aalexcampean)

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

add_executable(e911-aalexcampean
        Domain/Idea.cpp
        Domain/Idea.h
        Domain/Writer.cpp
        Domain/Writer.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        Repository/IdeaRepo.cpp
        Repository/IdeaRepo.h
        Repository/WriterRepo.cpp
        Repository/WriterRepo.h
        TableModel/IdeasTableModel.cpp
        TableModel/IdeasTableModel.h
        Widgets/WriterWidget.cpp
        Widgets/WriterWidget.h
        main.cpp)

target_link_libraries(e911-aalexcampean
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

