#ifndef INFORMATIK_PROJEKT_ANALYSER_H
#define INFORMATIK_PROJEKT_ANALYSER_H

#include "structs.h"
#include "main.h"
#include "menu.h"
#include "sort.h"
#include "global.h"
#include "read_user.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void print_nachricht_len(unsigned short mode);
void print_average_words();
void print_weekday();
void print_hour();
void print_month();
void *count_weekday();
void count_nachrichten();
void *count_hours();
void *count_month();
struct User **sort_user(int n, int offset, char type);
void swap_user(struct User *user1, struct User *user2);
unsigned int count_words(const char *string);
void create_dict();
void woerterbook();
#endif //INFORMATIK_PROJEKT_ANALYSER_H
