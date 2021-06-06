#ifndef INFORMATIK_PROJEKT_DICTIONARY_H
#define INFORMATIK_PROJEKT_DICTIONARY_H

#include "main.h"
#include "global.h"
#include "structs.h"
#include "input.h"

void *create_dictionary();
int check_char(char c);
Dictionary *insert_word(Message *ptr, int offset, int length, Dictionary *temp, int message_number);
int height(Dictionary *temp);
Dictionary *right_rotate(Dictionary *temp);
Dictionary *left_rotate(Dictionary *temp);
void print_dictionary(Dictionary *ptr,bool reverse,int max_amount);
int get_balanced(Dictionary * temp);
int max_height(int left, int right);
void update_height(Dictionary *temp, int level);
void print_word_stats(Dictionary*dict);

void dictionary_main(char sort);
int relative_word_count(Dictionary *ptr);
int find_longest_word(int longest,Dictionary*ptr);
void dictionary_select();
Tree *find_word(Dictionary *tree_node, const char *string, Tree *ret, int n_word);
Tree *find_other_word(Dictionary *tree_node, const char *string, Tree *ret, int n_word);

bool check_word(Dictionary *tree_node, const char *string);
int find_most_word(int most,Dictionary*ptr);
Dictionary*get_string_tree(char *string, int size, char *pointer);
List* get_suggestions_from_dict_tree(Dictionary*ptr , List*suggestions, char*search);
Dictionary* find_similar_in_tree(Dictionary*ptr, char*search);
Dictionary* find_in_tree(Dictionary*ptr, char*search);

Dictionary *rearange_word(Dictionary*new_dict,Dictionary *dict,char type);
Dictionary *rearange_tree(Dictionary*new_dict,Dictionary*dict,char type);


#endif //INFORMATIK_PROJEKT_DICTIONARY_H
