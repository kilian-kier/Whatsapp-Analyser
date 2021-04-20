//
// Created by Martin Gamper on 14.04.2021.
//

#ifndef INFORMATIK_PROJEKT_MENU_H
#define INFORMATIK_PROJEKT_MENU_H
#include "main.h"

#define x_size 150
#define y_size 45
#define x_pos 40
#define y_pos 3

#define FAST_MODE 0
#define SLOW_MODE 1

typedef struct Pixel{
    char character;
    int r;
    int g;
    int b;
}Pixel;
void main_menu();
int menu(int quantity,int select,...);
void anzeigeHintergrund(int r, int g, int b);
void anzeigeVordergrund(int r, int g, int b);
void clearscreen();
void draw_picture_buffer(Pixel picture_buffer[y_size][x_size],int mode);
void init_picture_buffer(Pixel picture_buffer[y_size][x_size]);
void draw_picture(Pixel picture_buffer[y_size][x_size], char *file, int xpos, int ypos,int xsize,int ysize);

#endif //INFORMATIK_PROJEKT_MENU_H
