#ifndef INFORMATIK_PROJEKT_DICTIONARY_H
#define INFORMATIK_PROJEKT_DICTIONARY_H

#include "main.h"
#include "global.h"
#include "structs.h"

void *create_dictionary();
int check_char(char c);
Dictionary *insert_word(char *ptr, int offset, int length, Dictionary *temp);
int height(Dictionary *temp);
Dictionary *right_rotate(Dictionary *temp);
Dictionary *left_rotate(Dictionary *temp);
void print_dictionary(Dictionary *ptr,bool reverse);
int get_balanced(Dictionary * temp);
int max_height(int left, int right);
void update_height(Dictionary *temp, int level);

void dictionary_main(char sort);
int relative_word_count(Dictionary *ptr);
int find_longest_word(int longest,Dictionary*ptr);
void dictionary_select();
Dictionary *find_word(Dictionary *tree_node, List *input);
int find_most_word(int most,Dictionary*ptr);

Dictionary *rearange_word(Dictionary*new_dict,Dictionary *dict,char type);
Dictionary *rearange_tree(Dictionary*new_dict,Dictionary*dict,char type);

#endif //INFORMATIK_PROJEKT_DICTIONARY_H
