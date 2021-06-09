#ifndef READ_H
#define READ_H

#include "std_include.h"
#include "structs.h"
#include "global.h"
#include "read_user.h"
#include "dictionary.h"

char *get_message(char *buffer);

bool check_new_string(const char *string);

void *read_file();

int length(const char *buffer, char search, int start);

char *string_convert(char *string, int offset);

#endif //READ_H