#ifndef INFORMATIK_PROJEKT_DICTIONARY_H
#define INFORMATIK_PROJEKT_DICTIONARY_H

#include "main.h"
#include "global.h"
#include "structs.h"

void create_dictionary();
int check_char(char c);
Dictionary *insert_word(char *anfang, int l, Dictionary *temp);
//int height(Dictionary *temp);
//Dictionary *right_rotaition(Dictionary *temp);
//Dictionary *left_rotaition(Dictionary *temp);
void print_dictionary(Dictionary *ptr);

#endif //INFORMATIK_PROJEKT_DICTIONARY_H
