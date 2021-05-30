//
// Created by Martin Gamper on 29.05.2021.
//



#ifndef INFORMATIK_PROJEKT_INPUT_H
#define INFORMATIK_PROJEKT_INPUT_H

#include "std_include.h"
#include "menu.h"
#include "structs.h"
int run_input_thread();
char* get_string(char*string,int size,char*pointer,int type);
Suggestions *get_suggestions_from_array(char**array,int size,char*search);
void free_suggestions(Suggestions *suggestions);
#endif //INFORMATIK_PROJEKT_INPUT_H