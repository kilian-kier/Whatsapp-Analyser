#ifndef INFORMATIK_PROJEKT_READ_H
#define INFORMATIK_PROJEKT_READ_H

#include "main.h"

int countlines(FILE *f);
void readFile(FILE *f);
int lenght(const char buffer[1000], char suche,int anfang);

#endif //INFORMATIK_PROJEKT_READ_H
