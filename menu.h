//
// Created by Martin Gamper on 14.04.2021.
//

#ifndef INFORMATIK_PROJEKT_MENU_H
#define INFORMATIK_PROJEKT_MENU_H
#include "main.h"

#define x_size 150
#define y_size 40
#define x_pos 40
#define y_pos 3

void main_menu();
int menu(int quantity,int select,...);
void anzeigeHintergrund(int r, int g, int b);
void anzeigeVordergrund(int r, int g, int b);
void clearscreen();
void draw_picture_buffer(CHAR_INFO picture_buffer[x_size*y_size]);
void init_picture_buffer(CHAR_INFO picture_buffer[x_size*y_size]);

#endif //INFORMATIK_PROJEKT_MENU_H
