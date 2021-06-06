#ifndef INPUT_H
#define INPUT_H

#include "std_include.h"
#include "menu.h"

#include "structs.h"

int run_input_thread();

char *get_string(char *string, int size, char *pointer);

List *get_suggestions_from_array(char **array, int size, char *search);

void delete_n_char(int n);

void cursor_blink(bool on, int offset);

#endif //INPUT_H