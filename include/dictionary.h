#ifndef INFORMATIK_PROJEKT_DICTIONARY_H
#define INFORMATIK_PROJEKT_DICTIONARY_H

#include "main.h"
#include "global.h"
#include "structs.h"

void create_dictionary();
int check_char(char c);
Dictionary *insert_word(char *word_begin, int length, Dictionary *temp);
int height(Dictionary *temp);
Dictionary *right_rotate(Dictionary *temp);
Dictionary *left_rotate(Dictionary *temp);
void print_dictionary(Dictionary *ptr);
int get_balanced(Dictionary * temp);
int max_height(int left, int right);
void update_height(Dictionary *temp, int level);

void dictionary_main(FILE*f);
int relative_word_count(Dictionary *ptr);
int find_longest_word(int longest,Dictionary*ptr);
Dictionary** find_most_word();
void shift_pointer_array(char **array,int index,int size);
void find_most_rec();

#endif //INFORMATIK_PROJEKT_DICTIONARY_H
