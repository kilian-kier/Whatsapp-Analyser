//
// Created by Martin Gamper on 14.04.2021.
//

#ifndef INFORMATIK_PROJEKT_MENU_H
#define INFORMATIK_PROJEKT_MENU_H
#include "main.h"

#define x_size 150
#define y_size 50
#define x_pos 40
#define y_pos 3


#define white (Color){255,255,255}
#define black (Color){0,0,0}
#define FOREGROUND_LAYER 1
#define BACKGROUND_LAYER 0

typedef struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}Color;
typedef struct Pixel{
    char character;
    Color foreground;
    Color background;
}Pixel;

Pixel picture_buffer[y_size][x_size];

void main_menu();
int menu(int quantity,int select,...);
void anzeigeHintergrund(int r, int g, int b);
void anzeigeVordergrund(int r, int g, int b);
void clearscreen();
void draw_picture_buffer(Pixel picture_buffer[y_size][x_size]);
void init_picture_buffer(Pixel picture_buffer[y_size][x_size]);
void draw_picture(Pixel picture_buffer[y_size][x_size], char *file, int xpos, int ypos,int xsize,int ysize);
void print_to_buffer(char string[], int xpos,int ypos,Color foreground,Color background);
void draw_rect(int xpos,int ypos,int xsize, int ysize, Color color, bool fill, bool layer);
void draw_rect(int xpos,int ypos,int xsize, int ysize, Color color, bool fill, bool layer);
void print_to_buffer(char string[], int xpos,int ypos,Color foreground,Color background);
Pixel picture_buffer[y_size][x_size];
#endif //INFORMATIK_PROJEKT_MENU_H
