#ifndef ANALYSER_H
#define ANALYSER_H

#include "std_include.h"

#include "structs.h"
#include "output.h"
#include "global.h"
#include "sort.h"

void *count_weekday();

void count_message();

void *count_hours();

void *count_month();

void *count_days();

struct User **sort_user(int n, int offset, char type);

void swap_user(struct User *user1, struct User *user2);

unsigned int count_words(const char *string);

bool true_day(unsigned int day, unsigned int month);

bool true_month(unsigned int month);

bool true_date(unsigned int day, unsigned int month, unsigned int year, Message *max_date);

User *user_exists(char *username);

int check_date(unsigned int day1, unsigned int month1, unsigned int year1, unsigned int day2, unsigned int month2, unsigned int year2);

#endif //ANALYSER_H
