cmake_minimum_required(VERSION 3.17)
project(Informatik_Projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(Informatik_Projekt
        main.c read.c include/read.h include/main.h include/structs.h structs.c menu.c include/menu.h analyser.c include/analyser.h include/global.h sort.c include/sort.h read_user.c include/read_user.h options.c include/options.h include/std_include.h output.c include/output.h print_to_screen.c include/print_to_screen.h  dictionary.c include/dictionary.h input.c include/input.h settings.c include/settings.h memory.c include/memory.h)

target_link_libraries(Informatik_Projekt -lpsapi)