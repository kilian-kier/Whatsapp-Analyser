#ifndef GLOBAL_H
#define GLOBAL_H

#include "std_include.h"

#include "structs.h"

int x_size;
int y_size;
#define x_pos 40
#define y_pos 1
#define buffersize 10000

int global_message_n;
struct Message *global_first_message;
struct User *global_first_user;
struct Dictionary *gloabl_first_word;
int *global_week_arr;
int *global_hour_arr;
int *global_month_arr;
Console_buffer *global_picture_buffer2;
int current_pos;
int page_count;
pthread_t read_file_tread;
pthread_t read_user_tread;
pthread_t weekday_thread;
pthread_t hour_thread;
pthread_t month_thread;

#endif //GLOBAL_H
