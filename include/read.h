#ifndef READ_H
#define READ_H

#include "std_include.h"
#include "structs.h"
#include "global.h"
#include "read_user.h"
#include "dictionary.h"

char *get_message(char *buffer, FILE *f);
bool check_new_string(const char *string);

int count_lines(FILE *f);
void *read_file(void *f);
int length(const char *buffer, char search, int start);
char * string_convert(char *string, int offset);

#endif //READ_H