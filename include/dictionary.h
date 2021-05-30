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
void dictionary_main(FILE*f);
int relative_word_count(Dictionary *ptr);
int find_longest_word(int longest,Dictionary*ptr);
Dictionary** find_most_word();
void shift_pointer_array(char **array,int index,int size);
void find_most_rec();

#endif //INFORMATIK_PROJEKT_DICTIONARY_H
