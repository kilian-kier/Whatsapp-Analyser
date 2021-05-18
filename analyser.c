#include "include/analyser.h"

void print_weekday() {
    User *temp = global_first_user;
    init_picture_buffer(picture_buffer);
    print_to_buffer("Montag", 0, 0, white, black);
    print_to_buffer("Dienstag", 0, 2, white, black);
    print_to_buffer("Mittwoch", 0, 4, white, black);
    print_to_buffer("Donnerstag", 0, 6, white, black);
    print_to_buffer("Freitag", 0, 8, white, black);
    print_to_buffer("Samstag", 0, 10, white, black);
    print_to_buffer("Sonntag", 0, 12, white, black);
    int max_j = strlen("Donnerstag") + 1;
    int max_i = 0;
    char *buf;
    for (int i = 0; i < 7; i++) {
        if (global_week_arr[i] > max_i)
            max_i = global_week_arr[i];
    }
    buf = malloc((int) log10(max_i) + 1 * sizeof(char));
    for (int i = 0; i < 7; i++) {
        int x = (x_size - (int) log10(max_i) - 5 - max_j) * (global_week_arr[i]) /
                (max_i);
        draw_rect(max_j, i * 2, x, 1, white, 1, 0);
        //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_week_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i * 2, white, black);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i * 2, white, black);
            print_to_buffer(buf, max_j, i * 2, white, black);
    }
}

void print_hour() {
    init_picture_buffer(picture_buffer);
    for (int i = 0; i < 24; i++) {
        char string[6];
        sprintf(string, "%02d-%02d", i, i+1);
        print_to_buffer(string, 0, i * 2, white, black);
    }
    int max_j = strlen("00-01") + 1;
    int max_i = 0;
    char *buf;
    for (int i = 0; i < 24; i++) {
        if (global_hour_arr[i] > max_i)
            max_i = global_hour_arr[i];
    }
    buf = malloc((int) log10(max_i) + 1 * sizeof(char));
    for (int i = 0; i < 24; i++) {
        int x = (x_size - (int) log10(max_i) - 5 - max_j) * (global_hour_arr[i]) /
                (max_i);
        draw_rect(max_j, i * 2, x, 1, white, 1, 0);
        //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_hour_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i * 2, white, black);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i * 2, white, black);
            print_to_buffer(buf, max_j, i * 2, white, black);
    }
}

void print_month() {
    User *temp = global_first_user;
    init_picture_buffer(picture_buffer);
    print_to_buffer("Januar", 0, 0, white, black);
    print_to_buffer("Februar", 0, 2, white, black);
    print_to_buffer("Maerz", 0, 4, white, black);
    print_to_buffer("April", 0, 6, white, black);
    print_to_buffer("Mai", 0, 8, white, black);
    print_to_buffer("Juni", 0, 10, white, black);
    print_to_buffer("Juli", 0, 12, white, black);
    print_to_buffer("August", 0, 14, white, black);
    print_to_buffer("September", 0, 16, white, black);
    print_to_buffer("Oktober", 0, 18, white, black);
    print_to_buffer("November", 0, 20, white, black);
    print_to_buffer("Dezember", 0, 22, white, black);
    int max_j = strlen("September") + 1;
    int max_i = 0;
    char *buf;
    for (int i = 0; i < 12; i++) {
        if (global_month_arr[i] > max_i)
            max_i = global_week_arr[i];
    }
    buf = malloc((int) log10(max_i) + 1 * sizeof(char));
    for (int i = 0; i < 12; i++) {
        int x = (x_size - (int) log10(max_i) - 5 - max_j) * (global_month_arr[i]) /
                (max_i);
        draw_rect(max_j, i * 2, x, 1, white, 1, 0);
        //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_month_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i * 2, white, black);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i * 2, white, black);
            print_to_buffer(buf, max_j, i * 2, white, black);
    }
}

void print_average_words() {
    init_picture_buffer(picture_buffer);
    int n = 0;
    User *temp = global_first_user;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    User **arr = sort_user(n, 32, 'd');
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        print_to_buffer(arr[i]->name, 0, i * 2, white, black);
        if (strlen(arr[i]->name) > max_j) {
            max_j = strlen(arr[i]->name);
        }
    }
    max_j++;
    char *buf;
    buf = malloc((int) log10(arr[0]->average_words) + 1 * sizeof(char));
    for (int i = 0; i < n; i++) {
        int x = (x_size - (int) log10(arr[0]->average_words) - 5 - max_j) * (arr[i]->average_words) /
                (arr[0]->average_words);
        draw_rect(max_j, i * 2, x, 1, white, 1, 0);
        //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
        sprintf(buf, "%.2lf", arr[i]->average_words);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i * 2, white, black);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i * 2, white, black);
            print_to_buffer(buf, max_j, i * 2, white, black);
    }
    free(arr);
}

void print_nachricht_len(unsigned short mode) {
    init_picture_buffer(picture_buffer);
    int n = 0;
    User *temp = global_first_user;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    User **arr = sort_user(n, 24, 'u');
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        print_to_buffer(arr[i]->name, 0, i * 2, white, black);
        if (strlen(arr[i]->name) > max_j) {
            max_j = strlen(arr[i]->name);
        }
    }
    max_j++;
    char *buf;
    if (mode == 0) {
        buf = malloc((int) log10(arr[0]->nachrichten_len) + 1 * sizeof(char));
        for (int i = 0; i < n; i++) {
            int x = (x_size - (int) log10(arr[0]->nachrichten_len) - 2 - max_j) * (arr[i]->nachrichten_len) /
                    (arr[0]->nachrichten_len);
            draw_rect(max_j, i * 2, x, 1, white, 1, 0);
            //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
            itoa(arr[i]->nachrichten_len, buf, 10);
            if (x > 0)
                print_to_buffer(buf, max_j + x + 1, i * 2, white, black);
            else
                //print_to_buffer(buf, max_j + 2, i * 2, white, black);
                print_to_buffer(buf, max_j, i * 2, white, black);
        }
    } else if (mode == 1) {
        buf = malloc(3 * sizeof(char));
        for (int i = 0; i < n; i++) {
            int x = (x_size - 6 - max_j) * (arr[i]->nachrichten_len) / (arr[0]->nachrichten_len);
            draw_rect(max_j, i * 2, x, 1, white, 1, 0);
            //draw_rect(max_j, i * 2, 1, 1, white, 1, 0);
            float val = (float) arr[i]->nachrichten_len * 100 / (float) global_anz_nachrichten;
            sprintf(buf, "%.1f", val);
            if (x > 0)
                print_to_buffer(strcat(buf, "%"), max_j + x + 1, i * 2, white, black);
            else
                //print_to_buffer(strcat(buf, "%"), max_j + 2, i * 2, white, black);
                print_to_buffer(strcat(buf, "%"), max_j, i * 2, white, black);

        }
    }
    free(arr);
}

User **sort_user(int n, int offset, char type) {
    User **arr = malloc((n + 1) * sizeof(char *));
    User *temp = global_first_user;
    int i = 0;
    while (temp->next != NULL) {
        arr[i] = temp;
        temp = temp->next;
        i++;
    }
    merge_sort(arr, n, offset, type);
    return arr;
}


void *count_weekday() {
    Nachricht *ptr = global_first_nachricht;
    global_week_arr = (int *) malloc(7 * sizeof(int));
    for (int x = 0; x < 7; x++) {
        *(global_week_arr + x) = 0;
    }
    short weekday;
    int h, k;
    while (ptr->next != NULL) {
        if (ptr->monat <= 2) {
            h = ptr->monat + 12;
            k = ptr->jahr - 1;
        } else {
            h = ptr->monat;
            k = ptr->jahr;
        }
        weekday = (ptr->tag + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7;
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

void count_nachrichten() {
    global_anz_nachrichten = 0;
    Nachricht *ptr = global_first_nachricht;
    while (ptr != NULL) {
        global_anz_nachrichten++;
        ptr = ptr->next;
    }
}

void *count_hours() {
    Nachricht *ptr = global_first_nachricht;
    global_hour_arr = (int *) malloc(24 * sizeof(int));
    for (int x = 0; x < 24; x++) {
        *(global_hour_arr + x) = 0;
    }
    while (ptr->next != NULL) {
        *(global_hour_arr + ptr->stunde)+=1;
        ptr = ptr->next;
    }
}

void *count_month() {
    Nachricht *ptr = global_first_nachricht;
    global_month_arr = (int *) malloc(12 * sizeof(int));
    for (int x = 0; x < 12; x++) {
        global_month_arr[x] = 0;
    }
    while (ptr->next != NULL) {
        global_month_arr[ptr->monat - 1]++;
        ptr = ptr->next;
    }
}


