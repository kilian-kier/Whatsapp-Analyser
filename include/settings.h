#ifndef INFORMATIK_PROJEKT_SETTINGS_H
#define INFORMATIK_PROJEKT_SETTINGS_H

#include "global.h"
#include "output.h"
#include "input.h"

Color *read_color(wchar_t *string);
void set_font_color();
void set_background_color();
void set_menu_color();
void set_bar_color();
void set_top_n();
void set_empty_lines();
void default_settings();
void read_config();
void write_config();

#endif //INFORMATIK_PROJEKT_SETTINGS_H
