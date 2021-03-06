#include "include/menu.h"

void main_menu() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    struct _CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);
    x_size = screenBufferInfo.srWindow.Right - x_pos - 1;
    y_size = screenBufferInfo.srWindow.Bottom - y_pos - 1;

    printf("\x1b[?25l");

    Option_tree *temp = create_option(NULL, &opt0, NULL, 4, 0, 0);
    Option_tree *option_root = temp;
    temp = create_option(L"Datei \x94\146\146nen", &opt1, temp, 4, 0, 0);
    temp = create_option(L"Users", NULL, temp, 3, 0, 0);
    create_option(L"Anzahl Nachrichten", &opt1_1_1, temp, 0, 0, 0);
    create_option(L"prozentual\n", &opt1_1_2, temp, 0, 1, 0);
    create_option(L"durchschnittliche W\x94rter\n", &print_average_words, temp, 0, 2, 0);
    temp = create_option(L"W\x94rterbuch", NULL, temp->parent, 0, 3, 0);
    temp = create_option(L"Zeit", NULL, temp->parent, 4, 1, 0);

    temp = create_option(L"W\x94rterbuch", &opt1_4_2, temp->parent, 2
                         , 3, 0);

    temp = create_option(L"Sortierung", NULL, temp, 4, 1, DONT_INIT_BUFFER);
    create_option(L"Alphabet", &opt1_4_2_1, temp, 0, 0, DONT_INIT_BUFFER);
    create_option(L"L\x84nge", &opt1_4_2_2, temp, 0, 1, DONT_INIT_BUFFER);
    create_option(L"Anzahl", &opt1_4_2_3, temp, 0, 2, DONT_INIT_BUFFER);
    create_option(L"Richtung \x84ndern", &opt1_4_2_4, temp, 0, 3, DONT_INIT_BUFFER);


    temp = create_option(L"Auswahl", &opt1_4_1, temp->parent, 1, 0, EXECUTE_PARENT);
    create_option(NULL, NULL, temp, 0, 0, 0);
    temp = temp->parent;

    temp = create_option(L"Zeit", NULL, temp->parent, 4, 1, 0);
    create_option(L"Monat", &print_month, temp, 0, 0, 0);
    create_option(L"Wochentag", &print_weekday, temp, 0, 1, 0);
    create_option(L"Tag", &print_day, temp, 0, 2, 0);
    create_option(L"Uhrzeit\n", &print_hour, temp, 0, 3, 0);
    create_option(L"Schlie\xe1\145n", &opt3, temp->parent->parent, 0, 3, 0);
    temp = create_option(L"Nachrichten", NULL, temp->parent, 3, 2, 0);
    create_option(L"Suchen nach Datum", &print_date_message, temp, 1, 0, 0);
    create_option(L"Suchen nach Nutzer", &print_user_message, temp, 1, 1, 0);
    create_option(L"Suchen nach W\x94rter", &opt1_3_3, temp, 1, 2, 0);
    for (int i = 0; i < 3; i++)
        create_option(NULL, NULL, temp->children[i], 0, 0, 0);
    temp = create_option(L"Einstellungen", &print_settings_example, temp->parent->parent, 4, 1, 0);
    temp = create_option(L"Farben", &print_settings_example, temp, 4, 0, 0);
    create_option(L"Schrift", &set_font_color, temp, 1, 0, 0);
    create_option(L"Balken", &set_bar_color, temp, 1, 1, 0);
    create_option(L"Men\x81", &set_menu_color, temp, 1, 2, 0);
    create_option(L"Hintergrund", &set_background_color, temp, 1, 3, 0);
    for (int i = 0; i < 4; i++) {
        create_option(NULL, NULL, temp->children[i], 0, 0, 0);
    }
    temp = create_option(L"Top n", &set_top_n, temp->parent, 1, 1, 0);
    create_option(NULL, NULL, temp, 0, 0, 0);
    temp = create_option(L"Zeilenabstand", &set_empty_lines, temp->parent, 1, 2, 0);
    create_option(NULL, NULL, temp, 0, 0, 0);
    create_option(L"Zur\x81cksetzen", &opt2_4, temp->parent, 0, 3, 0);
    temp = create_option(L"Infos", &opt4, option_root, 1, 2, 0);
    create_option(NULL, NULL, temp, 0, 0, 0);

    temp = option_root;
    temp->function();
    int x;

    run_input_thread();
    do {
        printf("\x1b[%dB", y_pos);
        x = menu(1, temp);
        if (x == 0) {
            Option_tree *temp2 = temp;
            if (!(temp2->settings & DONT_INIT_BUFFER)) {
                init_picture_buffer();
                draw_picture_buffer();
            }
            temp = temp->parent;
            if (temp == NULL) {
                break;
            } else if ((temp->function != NULL && temp->opt == 0) || temp2->settings & EXECUTE_PARENT) {
                temp->function();
            }
            continue;
        }
        if (temp->children[x - 1]->function != NULL) {
            temp->children[x - 1]->function();
            if (temp->opt == NULL && file == NULL && temp->children[x-1]->function!=print_settings_example)
                continue;
        }
        if (temp->children[x - 1]->n_childs != 0) {
            temp = temp->children[x - 1];
        }
    } while (1);
}


int menu(int select, Option_tree *option) {
    background_color(global_settings.background);
    clear_screen();
    draw_picture_buffer();
    int input;
    if (global_input_buffer == '') {
        global_input_buffer = 0;
        return 0;
    }
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cursor;
    COORD line[option->n_childs];
    foreground_color(global_settings.menu_color);
    printf("%s\n", "WhatsApp Analyzer\n");
    if (option->children[0]->opt != NULL) {
        for (int i = 1; i <= option->n_childs; i++) {
            GetConsoleScreenBufferInfo(hStdout, &cursor);
            line[i - 1] = cursor.dwCursorPosition;
            if (select == i) {
                printf("[*]\t");
            } else {
                printf("[ ]\t");
            }
            fwprintf(stdout, L"%s\n", option->children[i - 1]->opt);
        }
        COORD jumpto;
        do {
            do {
                input = (int) global_input_buffer;
                Sleep(sync_delay / 2);
            } while (input != 10 && input != 13 && input != 'w' && input != 's' && input != 27 && input != 'r' &&
                     input != 'f' && input != 'a' && input != 'd');
            global_input_buffer = 0;
            jumpto = line[select - 1];
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
            global_input_buffer = 0;
            SetConsoleCursorPosition(hStdout, jumpto);
            foreground_color(global_settings.menu_color);
            printf("\x1b[1K\x1b[3D[ ]");
            SetConsoleCursorPosition(hStdout, line[select - 1]);
            printf("\x1b[1K\x1b[3D[*]");
            fflush(stdout);
        } while (input != 13 && input != 10);
    } else {
        do {
            do {
                input = global_input_buffer;
                Sleep(sync_delay / 2);
            } while (input != 27 && input != 10);
            global_input_buffer = 0;
            switch (input) {
                case '':
                    return 0;
                default:
                    break;
            }
        } while (input != 13 && input != 10);
    }
    return select;
}