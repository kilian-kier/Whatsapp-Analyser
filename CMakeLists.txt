cmake_minimum_required(VERSION 3.17)
project(Informatik_Projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(Informatik_Projekt
        main.c read.c read.h main.h structs.h structs.c menu.c menu.h analyser.c analyser.h sort.c sort.h)
