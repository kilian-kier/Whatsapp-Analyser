#include "include/menu.h"
extern char*_binary_whatsapptest_ppm_start;
extern char*_binary_whatsapptest_ppm_end;
void main_menu() {
    FILE *f = NULL;
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    struct _CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);
    x_size = screenBufferInfo.srWindow.Right - x_pos-1;
    y_size = screenBufferInfo.srWindow.Bottom - y_pos-1;
    global_picture_buffer = (Pixel**) malloc(y_size*sizeof(Pixel*));
    for(int i = 0; i < y_size; i++){
        global_picture_buffer[i] = (Pixel*) malloc( x_size * sizeof(Pixel));
        if(global_picture_buffer[i]==NULL){
            perror("malloc");
        }
    }


    init_picture_buffer();

    draw_picture((char*)&_binary_whatsapptest_ppm_start,(char*)&_binary_whatsapptest_ppm_end,0, 0,100,40);

    printf("\x1b[?25l");

    Option_tree *temp = create_option(NULL, NULL, NULL, 2, 0);
    Option_tree *option_root = temp;
    temp = create_option(L"Datei \x94\146\146nen", &opt1, temp, 2, 0);
    temp = create_option(L"Users", &opt1_1, temp, 3, 0);
    create_option(L"Anzahl Nachrichten", &opt1_1_1, temp, 0, 0);
    create_option(L"prozentual\n", &opt1_1_2, temp, 0, 1);
    create_option(L"durchschnittliche W\x94rter\n", &opt1_1_3, temp, 0, 2);
    temp = create_option(L"Zeit", &opt1_2, temp->parent, 3, 1);
    create_option(L"Monat", &opt1_2_1, temp, 0, 0);
    create_option(L"Wochentag", &opt1_2_2, temp, 0, 1);
    create_option(L"Uhrzeit\n", &opt1_2_3, temp, 0, 2);
    create_option(L"Schlie\xe1\145n", &opt2, temp->parent->parent, 0, 1);


    temp = option_root;
    int x;
    do {
        clear_screen();
        draw_picture_buffer();
        printf("\x1b[%dB", y_pos);
        x = menu(1, temp);
        if (x == 0) {
            init_picture_buffer(global_picture_buffer);
            draw_picture_buffer();
            temp = temp->parent;
            if (temp == NULL)
                break;
            continue;
        }
        if (temp->children[x - 1]->function != NULL)
            temp->children[x - 1]->function(f);
        if (temp->children[x - 1]->n_child != 0) {
            temp = temp->children[x - 1];
        }
    } while (1);
}


int menu(int select, Option_tree *option) {
    background_color(0, 0, 0);
    foreground_color(255, 255, 255);
    int input;

    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cursor;
    COORD line[option->n_child];
    foreground_color(menucolor);

    printf("%s\n", "WhatsApp Analyzer\n");
    foreground_color(255, 255, 255);

    for (int i = 1; i <= option->n_child; i++) {
        GetConsoleScreenBufferInfo(hStdout, &cursor);
        line[i - 1] = cursor.dwCursorPosition;
        if (select == i) {
            printf("[*]\t");
        } else {
            printf("[ ]\t");
        }
        fwprintf(stdout, L"%s\n", option->children[i - 1]->opt);
        foreground_color(255, 255, 255);
    }
    SetConsoleCursorPosition(hStdout, line[select - 1]);
    do {
        do {
            fflush(stdin);
            input = _getch();
        } while (input != 10 && input != 13 && input != 'w' && input != 's' && input != 27);

        switch (input) {
            case 'w':
                select = select > 1 ? select - 1 : option->n_child;
                break;
            case 's':
                select = select < option->n_child ? select + 1 : 1;
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
    } while (input != 13 && input != 10);

    return select;
}