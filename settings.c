#include "include/settings.h"

Color *read_color(wchar_t *string) {
    Color *color = malloc(sizeof(Color));
    while (1) {
        wprintf(string);
        char *buffer = malloc(20 * sizeof(char));
        if (get_string(buffer, 20, NULL) == NULL)
            return NULL;
        if (sscanf(buffer, "%d,%d,%d", &color->r, &color->g, &color->b) != 3) {
            printf("\n  Bitte im g\x81ltigen Format eingeben\n\n");
            continue;
        } else {
            if (color->r >= 256)
                color->r = 255;
            else if (color->r < 0)
                color->r = 0;
            if (color->g >= 256)
                color->g = 255;
            else if (color->g < 0)
                color->g = 0;
            if (color->b >= 256)
                color->b = 255;
            else if (color->b < 0)
                color->b = 0;

            if (color->r == 0 && color->g == 0 && color->b == 0)
                color->b = 1;
            break;
        }
    }
    return color;
}

void set_font_color() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    Color *color = read_color(L"  Setzte die Schriftfarbe in den Diagrammen [Rot, Gr\x81n, Blau]\n  ");
    if (color == NULL)
        return;
    global_settings.fontcolor = *color;
    draw_picture_buffer();
    global_input_buffer = '';
}

void set_background_color() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    Color *color = read_color(L"  Setzte die Hintergrundfarbe  [Rot, Gr\x81n, Blau]\n  ");
    if (color == NULL)
        return;
    global_settings.background = *color;
    draw_picture_buffer();
    global_input_buffer = '';
}

void set_menu_color() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    Color *color = read_color(L"  Setzte die Men\x81farbe [Rot, Gr\x81n, Blau]\n  ");
    if (color == NULL)
        return;
    global_settings.menucolor = *color;
    draw_picture_buffer();
    global_input_buffer = '';
}

void set_bar_color() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    Color *color = read_color(L"  Setzte die Diagrammfarbe [Rot, Gr\x81n, Blau]\n  ");
    if (color == NULL)
        return;
    global_settings.barcolor = *color;
    global_input_buffer = '';
}

void set_top_n() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");
    printf("Wie viele Zeilen sollen z.B. bei den Tagen mit den meisten Nachrichten ausgegeben werden:\n");
    printf("\n  \x84ndere den Wert mit den Pfeiltasten\n  ");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    COORD coord;
    coord.X = bufferInfo.dwCursorPosition.X;
    coord.Y = bufferInfo.dwCursorPosition.Y;
    global_arrow_keys = 2;
    while (global_input_buffer != 13 && global_input_buffer != '\n' && global_input_buffer != '') {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("%d", global_settings.top_n);
        Sleep(sync_delay);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("                  ");
    }
    global_arrow_keys = 0;
    global_input_buffer = '';
}

void set_empty_lines() {
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");
    printf("\n  \x84ndere den Wert mit den Pfeiltasten\n  ");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    COORD coord;
    coord.X = bufferInfo.dwCursorPosition.X;
    coord.Y = bufferInfo.dwCursorPosition.Y;
    global_arrow_keys = 1;
    while (global_input_buffer != 13 && global_input_buffer != '\n' && global_input_buffer != '') {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("%d", global_settings.empty_lines);
        Sleep(sync_delay);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("                  ");
    }
    global_arrow_keys = 0;
    global_input_buffer = '';
}

void default_settings() {
    global_settings.fontcolor = (Color) {255, 255, 255};
    global_settings.menucolor = (Color) {255, 255, 0};
    global_settings.barcolor = (Color) {255, 255, 255};
    global_settings.background = (Color) {0, 0, 0};
    global_settings.highlight_font = (Color) {0, 0, 0};
    global_settings.highlight_back = (Color) {0, 255, 255};
    global_settings.top_n = 40;
    global_settings.empty_lines = 1;
}

void read_config() {
    FILE *config_file = fopen("../config\\settings.cfg", "rb");
    if (config_file != NULL)
        fread(&global_settings, sizeof(Settings), 1, config_file);
    else
        default_settings();
    fclose(config_file);
}

void write_config() {
    FILE *config_file = fopen("../config\\settings.cfg", "wb");
    fwrite(&global_settings, sizeof(Settings), 1, config_file);
    fclose(config_file);
}