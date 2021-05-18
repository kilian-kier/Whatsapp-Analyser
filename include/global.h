#ifndef INFORMATIK_PROJEKT_GLOBAL_H
#define INFORMATIK_PROJEKT_GLOBAL_H

#include "structs.h"
#include <pthread.h>

int global_anz_nachrichten;
struct Nachricht *global_first_nachricht;
struct User *global_first_user;
struct Woerterbook *gloabl_first_word;
int *global_week_arr;
int *global_hour_arr;
int *global_month_arr;
pthread_t read_file_tread;
pthread_t read_user_tread;
pthread_t weekday_thread;
pthread_t hour_thread;
pthread_t month_thread;

#endif //INFORMATIK_PROJEKT_GLOBAL_H
