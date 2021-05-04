#ifndef INFORMATIK_PROJEKT_ANALYSER_H
#define INFORMATIK_PROJEKT_ANALYSER_H

#include "structs.h"
#include "main.h"
#include "menu.h"
#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void read_user();
void print_user();
int *count_date(Nachricht *ptr);
User **sort_user(int n);
unsigned int count_words(const char *string);

#endif //INFORMATIK_PROJEKT_ANALYSER_H
