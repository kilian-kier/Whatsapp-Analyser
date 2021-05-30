#ifndef SORT_H
#define SORT_H

#include "std_include.h"
#include "structs.h"

User **sort_user(int n, int offset, char type);
void merge(char ** arr, int size,int offset,char type);
char ** merge_sort(char ** arr, int size, int offset,char type);
void arr_cpy(int size, char**arr1,char**arr2);
char** binary_search(char**array,char*search, int size);

#endif //SORT_H
