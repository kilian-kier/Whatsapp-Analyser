#ifndef OUTPUT_H
#define OUTPUT_H

#include "structs.h"
#include "std_include.h"
#include "global.h"

#define menucolor 255,255,0
#define white (Color){255,255,255}
#define black (Color){0,0,0}
#define FOREGROUND_LAYER 1
#define BACKGROUND_LAYER 0

void background_color(int r, int g, int b);
void foreground_color(int r, int g, int b);
void clear_screen();
void draw_picture_buffer();
void init_picture_buffer();
void draw_picture(char *pointer1,char*pointer2 ,int xpos, int ypos,int xsize,int ysize);
void print_to_buffer(char string[], int xpos,int ypos, Color foreground, struct Color background);
void draw_rect(int xpos,int ypos,int xsize, int ysize, Color color, bool fill, bool layer);
void free_console_buffer(Console_buffer *buffer);
Console_buffer *create_console_buffer();
int print_point(int x,int y,wchar_t c, Color *foreground, Color *background);
void init_console_buffer( Console_buffer *buffer);




#endif //OUTPUT_H