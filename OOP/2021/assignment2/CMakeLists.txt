cmake_minimum_required(VERSION 3.17)
project(a23_912_Campean_Catalin C)

set(CMAKE_C_STANDARD 11)

add_executable(a23_912_Campean_Catalin
        Domain/Estate.h
        Domain/Estate.c
        DynamicArray/DA.h
        DynamicArray/DA.c
        Repository/Repo.h
        Repository/Repo.c
        Controller/Service.h
        Controller/Service.c
        Controller/UndoService.h
        Controller/UndoService.c
        Ui/Ui.h
        Ui/Ui.c
        Tests/Tests.h
        Tests/Tests.c
        Start.c)
