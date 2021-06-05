#ifndef PRINT_TO_SCREEN_H
#define PRINT_TO_SCREEN_H

#include "input.h"
#include "std_include.h"
#include "output.h"
#include "global.h"
#include "sort.h"
#include "analyser.h"


void print_message_len(unsigned short mode);
void print_average_words();
void print_weekday();
void print_hour();
void print_month();
void print_day();
void print_date_message();
void print_user_message();
void print_word_message(const char *input_string);
void print_settings_example();
void highlight_words(Tree *node, List *input);

#endif //PRINT_TO_SCREEN_H
