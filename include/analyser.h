#ifndef ANALYSER_H
#define ANALYSER_H

#include "std_include.h"

#include "structs.h"
#include "output.h"
#include "global.h"
#include "sort.h"

void *count_weekday();
void count_message();
void *count_hours();
void *count_month();
void *count_month();
struct User **sort_user(int n, int offset, char type);
void swap_user(struct User *user1, struct User *user2);
unsigned int count_words(const char *string);

#endif //INFORMATIK_PROJEKT_ANALYSER_H
