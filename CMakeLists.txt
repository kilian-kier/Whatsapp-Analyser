cmake_minimum_required(VERSION 3.17)
project(Informatik_Projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(Informatik_Projekt
        main.c read.c include/read.h include/main.h include/structs.h structs.c menu.c include/menu.h analyser.c include/analyser.h include/global.h sort.c include/sort.h read_user.c include/read_user.h)
