cmake_minimum_required(VERSION 3.21)
project(exam-practice-quiz)

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

add_executable(exam-practice-quiz
        Domain/Question.cpp
        Domain/Question.h
        Domain/Person.cpp
        Domain/Person.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        Repository/QuestionRepo.cpp
        Repository/QuestionRepo.h
        Repository/PersonsRepo.cpp
        Repository/PersonsRepo.h
        Widgets/PresenterWidget.cpp
        Widgets/PresenterWidget.h
        Widgets/ParticipantWidget.cpp
        Widgets/ParticipantWidget.h
        Observer.cpp
        Observer.h
        main.cpp)

target_link_libraries(exam-practice-quiz
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

