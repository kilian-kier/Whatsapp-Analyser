#ifndef OUTPUT_H
#define OUTPUT_H

#include "structs.h"
#include "std_include.h"
#include "global.h"
#include "memory.h"

#define white (Color){255,255,255}
#define black (Color){0,0,0}

void foreground_color(Color color);

void background_color(Color color);

void clear_screen();

void draw_picture_buffer();

void init_picture_buffer();

void draw_picture(char *pointer1, char *pointer2, int xpos, int ypos, int xsize, int ysize);

int print_to_buffer(const char *string, int xpos, int ypos, Color foreground, Color background);

void draw_rect(int xpos, int ypos, int xsize, int ysize, bool fill, bool layer);

void free_console_buffer(Console_buffer *buffer);

Console_buffer *create_console_buffer();

int print_point(int x, int y, wchar_t c, Color *foreground, Color *background);

void init_console_buffer(Console_buffer *buffer);

void print_banner();

void change_color(int xsize, int ysize, int xpos, int ypos, Color foreground, Color background);

void insert_in_buffer(Console_buffer_node *buffer, int xpos, int ypos, wchar_t c, Color *foreground, Color *background);

Pixel *get_from_buffer(Console_buffer_node *buffer, int xpos, int ypos);


#endif //OUTPUT_H