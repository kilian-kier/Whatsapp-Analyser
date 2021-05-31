#ifndef GLOBAL_H
#define GLOBAL_H

#include "std_include.h"

#include "structs.h"

int x_size;
int y_size;
#define x_pos 40
#define y_pos 1
#define buffersize 10000
#define sync_delay 20

Settings global_settings;
#define DICT_TREE 1
#define STRING_ARRAY 0


FILE *file;

int global_message_n;
struct Message *global_first_message;
struct User *global_first_user;
struct Dictionary *global_first_word;
int *global_week_arr;
int *global_hour_arr;
int *global_month_arr;
Day_count *global_day_arr;
Console_buffer *global_picture_buffer;
int global_current_pos;
int global_page_count;


short global_arrow_keys;
char global_send_input;
char global_input_buffer;

pthread_t read_file_tread;
pthread_t read_user_tread;
pthread_t weekday_thread;
pthread_t hour_thread;
pthread_t month_thread;
pthread_t day_thread;
pthread_t dictionary_thread;

#endif //GLOBAL_H
