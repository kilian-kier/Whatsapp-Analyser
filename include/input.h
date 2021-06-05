//
// Created by Martin Gamper on 29.05.2021.
//



#ifndef INFORMATIK_PROJEKT_INPUT_H
#define INFORMATIK_PROJEKT_INPUT_H

#include "std_include.h"
#include "menu.h"

#include "structs.h"
int run_input_thread();
char* get_string(char*string,int size,char*pointer);
List *get_suggestions_from_array(char**array,int size,char*search);
void delete_n_char(int n);
void cursor_blink(bool on,int offset);
List* get_suggestions_from_dict_tree(Dictionary*ptr , List*suggestions, char*search);
Dictionary* find_in_tree(Dictionary*ptr,char*search);
#endif //INFORMATIK_PROJEKT_INPUT_H