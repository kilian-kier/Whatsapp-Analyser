#ifndef INFORMATIK_PROJEKT_SORT_H
#define INFORMATIK_PROJEKT_SORT_H

#include "main.h"
void merge(char ** arr, int size,int offset,char type);
char ** merge_sort(char ** arr, int size, int offset,char type);
void arr_cpy(int size, char**arr1,char**arr2);

#endif //INFORMATIK_PROJEKT_SORT_H
