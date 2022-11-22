cmake_minimum_required(VERSION 3.21)
project(a3_4_aalexcampean)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(a3_4_aalexcampean
        Domain/Country.c
        Domain/Country.h
        Tests/Tests.c
        Tests/Tests.h
        Start.c
        DynamicArray/DA.c
        DynamicArray/DA.h
        Repository/Repo.h
        Repository/Repo.c
        Controller/Service.h
        Controller/Service.c
        Controller/UndoService.h
        Controller/UndoService.c Ui/Ui.h Ui/Ui.c)
