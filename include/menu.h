#ifndef MENU_H
#define MENU_H

#include "std_include.h"
#include "structs.h"
#include "options.h"
#include "output.h"

void main_menu();
int menu(int select, struct Option_tree *option);
#endif //MENU_H
