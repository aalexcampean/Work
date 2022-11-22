cmake_minimum_required(VERSION 3.21)
project(exam_practice_question_answers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(.)
include_directories(Domain)
include_directories(Exception)
include_directories(Repository)
include_directories(Widgets)

set(CMAKE_PREFIX_PATH "/Users/alexcampean/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(exam_practice_question_answers
        Domain/Answer.cpp
        Domain/Answer.h
        Domain/Person.cpp
        Domain/Person.h
        Domain/Question.cpp
        Domain/Question.h
        Exception/CustomException.cpp
        Exception/CustomException.h
        Repository/AnswerRepo.cpp
        Repository/AnswerRepo.h
        Repository/PersonRepo.cpp
        Repository/PersonRepo.h
        Repository/QuestionRepo.cpp
        Repository/QuestionRepo.h
        Service/QuestionService.cpp
        Service/QuestionService.h
        Service/AnswerService.cpp
        Service/AnswerService.h
        Widgets/SearchWidget.cpp
        Widgets/SearchWidget.h
        Widgets/UserWidget.cpp
        Widgets/UserWidget.h
        main.cpp
        Observer.cpp
        Observer.h)

target_link_libraries(exam_practice_question_answers
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )