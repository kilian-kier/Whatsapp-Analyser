#ifndef INFORMATIK_PROJEKT_ANALYSER_H
#define INFORMATIK_PROJEKT_ANALYSER_H

#include "structs.h"
#include <stdio.h>
#include <string.h>

void read_user();
void print_user();
int *count_date(Nachricht *ptr);
unsigned int count_words(const char *string);
#endif //INFORMATIK_PROJEKT_ANALYSER_H
