#include "include/input.h"

void *blink_input() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    COORD coord;
    coord.X = bufferInfo.dwCursorPosition.X;
    coord.Y = bufferInfo.dwCursorPosition.Y;
    while (1) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("-> ");
        Sleep(500);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("  ");
        Sleep(500);
    }
}

char *get_string(char *string, int size, char *pointer, int type) {
    int i = 0, j = 0;
    global_input_buffer = 0;
    global_send_input = false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    COORD coord1;
    coord1.X = bufferInfo.dwCursorPosition.X;
    coord1.Y = bufferInfo.dwCursorPosition.Y;
    COORD coord2;
    coord2.X = (short) (bufferInfo.dwCursorPosition.X + 3);
    coord2.Y = bufferInfo.dwCursorPosition.Y;
    while (global_input_buffer != 13 && global_input_buffer != '\n') {
        if (j % 66 < 33) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord1);
            printf("->");
        } else {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord1);
            printf("  ");
        }
        if (global_send_input == true) {
            if (global_input_buffer == 8) {
                if (i > 0) {
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord2);
                    printf(" ");
                    coord2.X--;
                    global_send_input = false;
                    i--;
                }
            } else if (global_input_buffer == '')
                return NULL;
            else {
                string[i] = global_input_buffer;
                coord2.X++;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord2);
                printf("%c", string[i]);
                global_send_input = false;
                if (i < size) {
                    i++;
                } else {
                    break;
                }
            }
        }
        j++;
        Sleep(sync_delay / 2);
    }
    string[i] = 0;
    return string;
}

void *input_thread() {
    global_input_buffer = 0;

    int c;
    do {
        if (_kbhit()) {
            c = _getch();
            switch (c) {
                case 0:
                case 224:
                    c = _getch();
                    switch (c) {
                        case 80:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos < global_page_count * y_size - y_size) {
                                    global_current_pos++;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 1) {
                                if (global_settings.empty_lines != 0)
                                    global_settings.empty_lines--;
                            } else if (global_arrow_keys == 2) {
                                if (global_settings.top_n != 0)
                                    global_settings.top_n--;
                            }
                            break;
                        case 72:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos > 0) {
                                    global_current_pos--;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 1)
                                global_settings.empty_lines++;
                            else if (global_arrow_keys == 2)
                                global_settings.top_n++;
                            break;
                        case 75:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos - y_size > 0) {
                                    global_current_pos -= y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos != 0) {
                                    global_current_pos = 0;
                                    draw_picture_buffer();

                                }
                            } else if (global_arrow_keys == 2) {
                                if (global_settings.top_n >= 11)
                                    global_settings.top_n -= 10;
                            }
                            break;
                        case 77:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos + y_size < global_page_count * y_size - y_size + 1) {
                                    global_current_pos += y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos + y_size != global_page_count * y_size - y_size) {
                                    global_current_pos = (global_page_count - 1) * y_size;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 2) {
                                global_settings.top_n += 10;
                            }

                            break;
                    }
                    break;
                default:
                    global_input_buffer = c;
                    global_send_input = true;
                    break;
            }
        }
        Sleep(sync_delay);
    } while (1);

}

int run_input_thread() {
    pthread_t pthread;
    pthread_create(&pthread, NULL, input_thread, NULL);
    while (global_send_input == -1) {
        Sleep(sync_delay);
    }
    return 0;
}
