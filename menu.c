#include "include/menu.h"

#define menuefarbe 255,255,0

void opt1(int n, char *ptr) {
    FILE *f = fopen(get_file_name(), "rb");
    ptr = f;
    pthread_create(&read_file_tread, NULL, readFile, (void *) ptr);
}

void opt2(int n, char *ptr) {
    exit(1);
}

void opt1_1(int n, char *ptr) {
    static bool is_read = false;
    if (is_read == false) {
        if (pthread_join(read_file_tread, NULL) != 0)
            readFile(*ptr);
        if (pthread_join(read_user_tread, NULL) != 0)
            read_user();
        is_read = true;
    }
}

void opt1_2(int n, char *ptr) {
    static bool is_read = false;
    if (is_read == false) {
        if (pthread_join(weekday_thread, NULL) != 0)
            count_weekday();
        if (pthread_join(hour_thread, NULL) != 0)
            count_hours();
        is_read = true;
    }
}

void opt1_1_1(int n, char *ptr) {
    print_nachricht_len(0);
}

void opt1_1_2(int n, char *ptr) {
    print_nachricht_len(1);
}

void opt1_1_3(int n, char *ptr) {
    print_average_words();
}

void opt1_2_1(int n, char *ptr) {
    print_month();
}

void opt1_2_2(int n, char *ptr) {
    print_weekday();
}

void opt1_2_3(int n, char *ptr) {
    print_hour();
}

void main_menu() {
    FILE *f = NULL;
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    init_picture_buffer();
    printf("\x1b[?25l");
    bool menu1;
    bool menu2;
    //draw_picture("whatsapptest.ppm", 0, 0,100,40);
    //print_to_buffer("Hallo Welt\nHallo Welt",-1,-1,(Color){255,0,0},black);
    //print_to_buffer("Hallo Welt\nHallo Welt",50,20,white,black);
    //draw_rect(0,0,1,5,white,1,1);

    Option_tree *temp = create_option(NULL, NULL, 0, NULL, NULL, 2, 0);
    Option_tree *option_root = temp;
    temp = create_option(L"Datei \x94\146\146nen", &opt1, 1, f, temp, 2, 0);
    temp = create_option(L"Users", &opt1_1, 1, f, temp, 3, 0);
    create_option(L"Anzahl Nachrichten", &opt1_1_1, 0, NULL, temp, 0, 0);
    create_option(L"prozentual\n", &opt1_1_2, 0, NULL, temp, 0, 1);
    create_option(L"durchschnittliche W\x94rter\n", &opt1_1_3, 0, NULL, temp, 0, 2);
    temp = create_option(L"Zeit", &opt1_2, 0, NULL, temp->parent, 3, 1);
    create_option(L"Monat", &opt1_2_1, 0, NULL, temp, 0, 0);
    create_option(L"Wochentag", &opt1_2_2, 0, NULL, temp, 0, 1);
    create_option(L"Uhrzeit\n", &opt1_2_3, 0, NULL, temp, 0, 2);
    create_option(L"Schlie\xe1\145n", &opt2, 1, NULL, temp->parent->parent, 0, 1);


    temp = option_root;
    int x;
    do {
        clearscreen();
        draw_picture_buffer();
        printf("\x1b[%dB", y_pos);
        x = menu(1, temp);
        if (x == 0) {
            init_picture_buffer(picture_buffer);
            draw_picture_buffer();
            temp = temp->parent;
            if (temp == NULL)
                break;
            continue;
        }
        if (temp->childs[x - 1]->function != NULL)
            temp->childs[x - 1]->function(temp->argc, temp->argv);
        if (temp->childs[x - 1]->n_childs != 0) {
            temp = temp->childs[x - 1];
        }
    } while (1);
}


int menu(int select, Option_tree *option) { // Koan Fehler des mitn Endless loop. CLION hot an schodn
    anzeigeHintergrund(0, 0, 0);
    anzeigeVordergrund(255, 255, 255);
    int input = 0;

    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cursor;
    COORD line[option->n_childs];
    anzeigeVordergrund(menuefarbe);
    printf("%s\n", "WhatsApp Analyzer\n");
    anzeigeVordergrund(255, 255, 255);
    for (int i = 1; i <= option->n_childs; i++) {
        GetConsoleScreenBufferInfo(hStdout, &cursor);
        line[i - 1] = cursor.dwCursorPosition;
        if (select == i) {
            printf("[*]\t");
        } else {
            printf("[ ]\t");
        }
        fwprintf(stdout, L"%s\n", option->childs[i - 1]->opt);
        anzeigeVordergrund(255, 255, 255);
    }
    SetConsoleCursorPosition(hStdout, line[select - 1]);
    do {
        do {
            fflush(stdin);
            input = getch();
        } while (input != 13 && input != 'w' && input != 's' && input != 27);

        switch (input) {
            case 'w':
                select = select > 1 ? select - 1 : option->n_childs;
                break;
            case 's':
                select = select < option->n_childs ? select + 1 : 1;
                break;
            case '':
                return 0;
            default:
                break;
        }
        printf("\x1b[1K\x1b[3D[ ]");
        SetConsoleCursorPosition(hStdout, line[select - 1]);
        printf("\x1b[1K\x1b[3D[*]");
        fflush(stdout);
    } while (input != 13);

    return select;
}

void init_picture_buffer() {
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            picture_buffer[y][x].character = ' ';
            picture_buffer[y][x].foreground = white;
            picture_buffer[y][x].background = black;

        }
    }
}

void print_to_buffer(char string[], int xpos, int ypos, Color foreground, Color background) {
    static int y = 0;
    static int x = 0;
    if (xpos >= 0) {
        x = xpos;
    }
    if (ypos >= 0) {
        y = ypos;
    }
    int toprint = strlen(string);
    for (int i = 0; i < toprint; i++) {
        if (y >= y_size) {
            return;
        }
        if (string[i] == '\n') {
            y++;
            if (xpos > 0) {
                x = xpos;
            } else {
                x = 0;
            }
            continue;
        }
        picture_buffer[y][x].character = string[i];
        picture_buffer[y][x].foreground = foreground;
        picture_buffer[y][x].background = background;
        x++;
    }
}

void draw_rect(int xpos, int ypos, int xsize, int ysize, Color color, bool fill, bool layer) {
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (fill || (!x || !y || y == ysize - 1 || x == xsize - 1)) {
                if (layer) {
                    picture_buffer[y + ypos][x + xpos].character = 219;
                    picture_buffer[y + ypos][x + xpos].foreground = color;
                } else {
                    picture_buffer[y + ypos][x + xpos].character = ' ';
                    picture_buffer[y + ypos][x + xpos].background = color;
                }
            }
        }
    }
}

void draw_picture(char *file, int xpos, int ypos, int xsize, int ysize) {
    char rubbish[100];
    unsigned char color;
    int ret = 1;
    int columns = 0;
    int rows = 0;

    FILE *picture = fopen(file, "rb");
    if (picture == NULL) {
        perror("fopen");
        return;
    }
    rewind(picture);

    for (int i = 0; i < 2; i++) {
        fgets(rubbish, 100, picture);
    }
    fscanf(picture, "%d %d\n", &columns, &rows);
    if (xsize + xpos > x_size || ysize + ypos > y_size) {
        printf("Bild ist zu gross");
        return;
    }

    unsigned char (*buffer)[rows][columns][3] = (unsigned char (*)[rows][columns][3]) malloc(
            sizeof(unsigned char) * rows * columns * 3);
    //perror("fehler");
    //Sleep(10000);

    fgets(rubbish, 100, picture);
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
    int newx;
    int newy;
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            newx = x * columns / xsize;
            newy = y * rows / ysize;
            picture_buffer[y + ypos][x + xpos].character = ' ';
            picture_buffer[y + ypos][x + xpos].background = (Color) {(*buffer)[newy][newx][0], (*buffer)[newy][newx][1],
                                                                     (*buffer)[newy][newx][2]};
        }
    }
    free(*buffer);
}

void draw_picture_buffer() {
    int r = 0;
    int br;
    int g = 0;
    int bg;
    int b = 0;
    int bb;
    setvbuf(stdout, NULL, _IOFBF, (x_pos + x_size) * (y_pos + y_size) * 25);
    printf("\x1b[%d;%dH", y_pos + 1, x_pos + 1);
    for (int y = 0; y < y_size; y += 1) {
        for (int x = 0; x < x_size; x++) {
            if (picture_buffer[y][x].background.r != br || picture_buffer[y][x].background.g != bg ||
                picture_buffer[y][x].background.b != bb) {
                br = picture_buffer[y][x].background.r;
                bg = picture_buffer[y][x].background.g;
                bb = picture_buffer[y][x].background.b;
                anzeigeHintergrund(br, bg, bb);
            }
            if (picture_buffer[y][x].foreground.r != br || picture_buffer[y][x].foreground.g != bg ||
                picture_buffer[y][x].foreground.b != bb) {
                r = picture_buffer[y][x].foreground.r;
                g = picture_buffer[y][x].foreground.g;
                b = picture_buffer[y][x].foreground.b;
                anzeigeVordergrund(r, g, b);
            }

            printf("%c", picture_buffer[y][x].character);
        }
        printf("\x1b[%dD\x1b[1B", x_size);
    }
    fflush(stdout);
    anzeigeVordergrund(255, 255, 255);
    printf("\x1b[H");
    setvbuf(stdout, NULL, _IONBF, 0);
}

void clearscreen() {
    printf("\x1b[H\x1b[0J");
}

void anzeigeVordergrund(int r, int g, int b) {
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void anzeigeHintergrund(int r, int g, int b) {
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}