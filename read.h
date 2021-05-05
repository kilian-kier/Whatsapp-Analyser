#ifndef INFORMATIK_PROJEKT_READ_H
#define INFORMATIK_PROJEKT_READ_H

#include "main.h"
#include <stdbool.h>

#define buffersize 10000
char * getMessage(char *buffer,FILE *f);
bool checkNewString(const char *string);

int countlines(FILE *f);
void *readFile(void *f);
int lenght(const char buffer[1000], char suche,int anfang);
char * string_to_lower(char*);

#endif //INFORMATIK_PROJEKT_READ_H