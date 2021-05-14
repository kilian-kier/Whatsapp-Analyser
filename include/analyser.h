#ifndef INFORMATIK_PROJEKT_ANALYSER_H
#define INFORMATIK_PROJEKT_ANALYSER_H

#include "structs.h"
#include "main.h"
#include "menu.h"
#include "sort.h"
#include "global.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void *read_user();
void print_nachricht_len(unsigned short mode);
void print_average_words();
int *count_weekday();
void count_nachrichten();
int *count_hours();
struct User **sort_user(int n, int offset, char type);
void swap_user(struct User *user1, struct User *user2);
unsigned int count_words(const char *string);
void create_dict();
//void woerterbook();
int *count_month();
//void insert(char *anfang, int l, Woerterbook *temp);
//void print(Woerterbook *ptr);
#endif //INFORMATIK_PROJEKT_ANALYSER_H
