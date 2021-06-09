#ifndef GLOBAL_H
#define GLOBAL_H

#include "std_include.h"

#include "structs.h"

int x_size;
int y_size;

#define x_pos 40
#define y_pos 1

#define buffer_size 10000
#define sync_delay 20
#define key_down 80
#define key_up 72
#define key_left 75
#define key_right 77

#define DONT_INIT_BUFFER 1
#define EXECUTE_PARENT 2

Settings global_settings;

FILE *file;
char*filename;

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
int global_input_buffer;

void *global_threads[7][2];

#endif //GLOBAL_H
