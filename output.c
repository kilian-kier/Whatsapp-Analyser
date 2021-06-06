#include "include/output.h"


int print_point(int x, int y, wchar_t c, Color *foreground, Color *background) {
    static Console_buffer *current = NULL;
    int buffer_index = y / y_size;
    if (x >= x_size) {
        return -1;
    }
    if (current == NULL) {
        global_picture_buffer = create_console_buffer();
        if (global_picture_buffer == NULL) {
            return -1;
        }
        global_picture_buffer->n = 0;
        global_picture_buffer->next = NULL;
        global_picture_buffer->previous = NULL;
        global_page_count = 1;
    }
    if (global_picture_buffer->next == NULL) current = global_picture_buffer;
    while (buffer_index != current->n) {
        if (buffer_index > current->n) {
            if (current->next == NULL) {
                current->next = create_console_buffer();
                current->next->previous = current;
                current->next->next = NULL;
                current->next->n = current->n + 1;
                if (current->next == NULL) {
                    return -1;
                }
                global_page_count++;
            }
            current = current->next;
        } else {
            current = current->previous;
        }
    }
    int newy = y % (y_size);
    insert_in_buffer(current->buffer, x, newy, c, foreground, background);
    return 0;
}

Console_buffer *create_console_buffer() {
    Console_buffer *buffer = malloc(sizeof(Console_buffer));
    if (buffer == NULL) {
        perror("malloc");
        return NULL;
    }
    buffer->buffer = malloc(y_size * sizeof(Console_buffer_node));
    if (buffer->buffer == NULL) {
        perror("malloc");
        return NULL;
    }
    for (int i = 0; i < y_size; i++) {
        buffer->buffer[i].pixel_list = NULL;
    }
    return buffer;
}

void free_console_buffer(Console_buffer *buffer) {
    if (buffer != NULL) {
        for (int i = 0; i < y_size; i++) {
            List *temp = buffer->buffer[i].pixel_list;
            while (temp != NULL) {
                if (temp->i.dot != NULL) {
                    free(temp->i.dot);
                }
                temp = temp->next;
            }
            free_list(buffer->buffer[i].pixel_list);
        }
        if (buffer->buffer != NULL) {
            free(buffer->buffer);
        }
        free(buffer);
    }
}

void init_picture_buffer() {
    Console_buffer *temp = global_picture_buffer->next;
    Console_buffer *temp2 = temp;

    while (temp != NULL) {
        temp2 = temp->next;
        free_console_buffer(temp);
        temp = temp2;
    }
    global_page_count = 1;
    global_current_pos = 0;
    global_picture_buffer->next = NULL;
    for (int i = 0; i < y_size; i++) {
        List *list = global_picture_buffer->buffer[i].pixel_list;
        while (list != NULL) {
            if (list->i.dot != NULL) {
                free(list->i.dot);
            }
            list = list->next;
        }
        free_list(global_picture_buffer->buffer[i].pixel_list);
        global_picture_buffer->buffer[i].pixel_list = NULL;
    }
}


void change_color(int xsize, int ysize, int xpos, int ypos, Color foreground, Color background) {
    ypos = ypos * (global_settings.empty_lines + 1);
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            print_point(xpos + x, ypos + y, 0, &foreground, &background);
        }
    }
}

int print_to_buffer(const char *string, int xpos, int ypos, Color foreground, Color background) {
    ypos = ypos * (global_settings.empty_lines + 1);
    static int y = 0;
    static int x = 0;
    if (xpos >= 0) {
        x = xpos;
    }
    if (ypos >= 0) {
        y = ypos;
    }
    int y_temp = y;

    int to_print = (int) strlen(string);
    for (int i = 0; i < to_print; i++) {
        if (string[i] == '\n') {
            y += global_settings.empty_lines + 1;
            if (xpos > 0) {
                x = xpos;
            } else {
                x = 0;
            }
            continue;
        }
        print_point(x, y, string[i], &foreground, &background);
        x++;
    }
    return y_temp;
}

void draw_rect(int xpos, int ypos, int xsize, int ysize, bool fill, bool layer) {
    ypos = ypos * (global_settings.empty_lines + 1);
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (fill || (!x || !y || y == ysize - 1 || x == xsize - 1)) {
                if (layer) {
                    print_point(x + xpos, y + ypos, -37, &global_settings.barcolor, NULL);
                } else {
                    print_point(x + xpos, y + ypos, ' ', NULL, &global_settings.barcolor);
                }
            }
        }
    }
}

void draw_picture(char *pointer1, char *pointer2, int xpos, int ypos, int xsize, int ysize) {
    char temp[100];
    unsigned char color;
    int ret = 1;
    int columns = 0;
    int rows = 0;
    FILE *picture;

    if (xsize + xpos > x_size) {
        printf("Bild ist zu gross");
        return;
    }

    if (pointer2 == NULL) {
        picture = fopen(pointer1, "rb");
        if (picture == NULL) {
            perror("fopen");
            return;
        }
        rewind(picture);
        for (int i = 0; i < 2; i++) {
            fgets(temp, 100, picture);
        }
        fscanf(picture, "%d %d\n", &columns, &rows);
        fgets(temp, 100, picture);
    } else {
        int i = 0;
        while (i < 2) {
            if (*pointer1 == '\n') i++;
            pointer1++;
        }
        for (i = 0; pointer1[i] != ' '; i++);
        pointer1[i] = 0;
        columns = atoi(pointer1);
        pointer1[i] = ' ';
        pointer1 = &pointer1[i] + 1;
        for (i = 0; pointer1[i] != '\n'; i++);
        pointer1[i] = 0;
        rows = atoi(pointer1);
        pointer1[i] = '\n';
        pointer1 = &pointer1[i] + 1;
        for (pointer1; *pointer1 != '\n'; pointer1++);
        pointer1++;
    }
    unsigned char (*buffer)[rows][columns][3] = (unsigned char (*)[rows][columns][3]) malloc(
            sizeof(unsigned char) * rows * columns * 3);

    if (pointer2 == NULL) {
        for (int y = 0; y < rows && ret == 1; y++) {
            for (int x = 0; x < columns && ret == 1; x++) {
                fread(&color, 1, 1, picture);
                (*buffer)[y][x][0] = color;
                fread(&color, 1, 1, picture);
                (*buffer)[y][x][1] = color;
                ret = fread(&color, 1, 1, picture);
                (*buffer)[y][x][2] = color;
            }
        }
        fclose(picture);
    } else {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                (*buffer)[y][x][0] = *pointer1;
                pointer1++;
                (*buffer)[y][x][1] = *pointer1;
                pointer1++;
                (*buffer)[y][x][2] = *pointer1;
                pointer1++;
            }
        }
    }

    int newx;
    int newy;
    Color rgb;
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            newx = x * columns / xsize;
            newy = y * rows / ysize;
            rgb = (Color) {(*buffer)[newy][newx][0], (*buffer)[newy][newx][1], (*buffer)[newy][newx][2]};
            print_point(x + xpos, y + ypos, ' ', NULL, &rgb);
        }
    }
    free((*buffer));
}

void draw_picture_buffer() {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hStdout, &bufferInfo);
    int r = 0;
    int br = 0;
    int g = 0;
    int bg = 0;
    int b = 0;
    int bb = 0;
    char c = 0;

    printf("\x1b[s");
    int page = global_current_pos / y_size;
    int offset = global_current_pos % y_size;
    int newy;
    Console_buffer *temp = global_picture_buffer;
    while (temp->n != page) {
        if (temp->next != 0) {
            temp = temp->next;
        } else {
            return;
        }
    }
    Pixel empty_pixel = {' ', global_settings.fontcolor, global_settings.background};
    setvbuf(stdout, NULL, _IOFBF, (x_pos + x_size) * (y_pos + y_size) * 25);
    printf("\x1b[%d;%dH", y_pos + 1, x_pos + 1);
    for (int y = 0; y < y_size; y += 1) {
        newy = y + offset;
        for (int x = 0; x < x_size; x++) {
            Pixel *pixel = get_from_buffer(temp->buffer, x, newy);
            if (pixel == NULL) {
                pixel = &empty_pixel;
            }
            if (pixel->background.r != br || pixel->background.g != bg ||
                pixel->background.b != bb) {
                br = pixel->background.r;
                bg = pixel->background.g;
                bb = pixel->background.b;
                if (br == 0 && bg == 0 && bb == 0) {
                    background_color(global_settings.background);
                } else {
                    background_color((Color) {br, bg, bb});
                }
            }
            if (pixel->foreground.r != br ||
                pixel->foreground.g != bg ||

                pixel->foreground.b != bb) {
                r = pixel->foreground.r;
                g = pixel->foreground.g;
                b = pixel->foreground.b;
                foreground_color((Color) {r, g, b});
            }
            if (pixel->character == 9) {
                c = ' ';
            } else {
                c = pixel->character;
            }
            printf("%c", c);
        }
        if (newy == y_size - 1) {
            offset = -(y + 1);
            if (temp->next != NULL) {
                temp = temp->next;
            } else {
                break;
            }
        }
        printf("\x1b[%dD\x1b[1B", x_size);
    }
    fflush(stdout);
    foreground_color(global_settings.menucolor);
    printf("\x1b[2E            \x1b[12DP[%d | %d]", page + 1, global_page_count);
    printf("\x1b[u");
    setvbuf(stdout, NULL, _IONBF, 0);
    SetConsoleCursorPosition(hStdout, bufferInfo.dwCursorPosition);
    memory_thread();
}

void
insert_in_buffer(Console_buffer_node *buffer, int xpos, int ypos, wchar_t c, Color *foreground, Color *background) {
    if (xpos >= x_size) return;
    if (ypos >= y_size) return;

    if (buffer != NULL) {
        List temp_list;
        temp_list.next = buffer[ypos].pixel_list;
        List *pixel = &temp_list;

        for (int i = 0; i <= xpos; i++) {
            if (pixel->next == NULL) {
                pixel->next = malloc(sizeof(List));
                if (pixel->next == NULL) {
                    perror("malloc");
                    return;
                }
                pixel->next->i.dot = NULL;
                pixel->next->next = NULL;
            }
            pixel = pixel->next;
        }
        buffer[ypos].pixel_list = temp_list.next;
        if (pixel->i.dot == NULL) {
            pixel->i.dot = malloc(sizeof(Pixel));
            pixel->i.dot->character = ' ';
            pixel->i.dot->foreground = global_settings.fontcolor;
            pixel->i.dot->background = global_settings.background;
            if (pixel->i.dot == NULL) {
                perror("malloc");
                return;
            }
        }
        if (c != 0) {
            pixel->i.dot->character = c;
        }
        if (foreground != NULL) {
            pixel->i.dot->foreground = *foreground;
        }
        if (background != NULL) {
            pixel->i.dot->background = *background;
        }
    }
}

Pixel *get_from_buffer(Console_buffer_node *buffer, int xpos, int ypos) {
    if (xpos >= x_size) return NULL;
    if (ypos >= y_size) return NULL;
    if (buffer != NULL) {
        List temp_list;
        temp_list.next = buffer[ypos].pixel_list;
        List *pixel = &temp_list;

        for (int i = 0; i <= xpos; i++) {
            if (pixel->next == NULL) {
                return NULL;
            }
            pixel = pixel->next;
        }
        return pixel->i.dot;
    }
}

void clear_screen() {
    printf("\x1b[H\x1b[0J");
}

void foreground_color(Color color) {
    printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void background_color(Color color) {
    printf("\x1b[48;2;%d;%d;%dm", color.r, color.g, color.b);
}

void print_banner() {
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");
    foreground_color(white);
}