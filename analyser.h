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
int *count_weekday();
void count_nachrichten();
int *count_hours();
User **sort_user(int n);
void swap_user(User *user1, User *user2);
unsigned int count_words(const char *string);
#endif //INFORMATIK_PROJEKT_ANALYSER_H
