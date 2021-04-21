#ifndef INFORMATIK_PROJEKT_ANALYSER_H
#define INFORMATIK_PROJEKT_ANALYSER_H

#include "structs.h"
#include <stdio.h>
#include "main.h"

void print_user();
void read_user();
int *count_weekday();
void count_nachrichten();
int *count_hours();
unsigned int count_words(const char *string);
#endif //INFORMATIK_PROJEKT_ANALYSER_H
