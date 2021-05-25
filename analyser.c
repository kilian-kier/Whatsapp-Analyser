#include "include/analyser.h"

void *count_weekday() {
    Message *ptr = global_first_message;
    global_week_arr = (int *) malloc(7 * sizeof(int));
    for (int x = 0; x < 7; x++) {
        *(global_week_arr + x) = 0;
    }
    unsigned short weekday, h, k;
    while (ptr->next != NULL) {
        if ((int)ptr->month <= 2) {
            h = (int)ptr->month + 12;
            k = (int)ptr->year - 1;
        } else {
            h = (int)ptr->month;
            k = (int)ptr->year;
        }
        weekday = (int)((int)ptr->day + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7;
        *(global_week_arr + weekday)+=1;
        ptr = ptr->next;
    }
}

unsigned int count_words(const char *string) {
    unsigned int words = 0;
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == ' ' || string[i] == '\n')
            words++;
        i++;
    }
    return words;
}

void count_message() {
    global_message_n = 0;
    Message *ptr = global_first_message;
    while (ptr != NULL) {
        global_message_n++;
        ptr = ptr->next;
    }
}

void *count_hours() {
    Message *ptr = global_first_message;
    global_hour_arr = (int *) malloc(24 * sizeof(int));
    for (int x = 0; x < 24; x++) {
        *(global_hour_arr + x) = 0;
    }
    while (ptr->next != NULL) {
        *(global_hour_arr + (int)ptr->hour)+=1;
        ptr = ptr->next;
    }
}

void *count_month() {
    Message *ptr = global_first_message;
    global_month_arr = (int *) malloc(12 * sizeof(int));
    for (int x = 0; x < 12; x++) {
        global_month_arr[x] = 0;
    }
    while (ptr->next != NULL) {
        global_month_arr[(int)ptr->month - 1]++;
        ptr = ptr->next;
    }
}
