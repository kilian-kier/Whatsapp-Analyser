#include "include/print_to_screen.h"

void print_weekday() {
    init_picture_buffer();
    print_to_buffer("Montag", 0, 0);
    print_to_buffer("Dienstag", 0, 1);
    print_to_buffer("Mittwoch", 0, 2);
    print_to_buffer("Donnerstag", 0, 3);
    print_to_buffer("Freitag", 0, 4);
    print_to_buffer("Samstag", 0, 5);
    print_to_buffer("Sonntag", 0, 6);
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
        draw_rect(max_j, i, x, 1, 1, 0);
        //draw_rect(max_j, i, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_week_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i);
    }
    free(buf);
}

void print_hour() {
    init_picture_buffer();
    for (int i = 0; i < 24; i++) {
        char string[6];
        sprintf(string, "%02d-%02d", i, i + 1);
        print_to_buffer(string, 0, i);
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
        draw_rect(max_j, i, x, 1, 1, 0);
        //draw_rect(max_j, i, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_hour_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i);
    }
    free(buf);
}

void print_month() {
    init_picture_buffer();
    print_to_buffer("Januar", 0, 0);
    print_to_buffer("Februar", 0, 1);
    print_to_buffer("Maerz", 0, 2);
    print_to_buffer("April", 0, 3);
    print_to_buffer("Mai", 0, 4);
    print_to_buffer("Juni", 0, 5);
    print_to_buffer("Juli", 0, 6);
    print_to_buffer("August", 0, 7);
    print_to_buffer("September", 0, 8);
    print_to_buffer("Oktober", 0, 9);
    print_to_buffer("November", 0, 10);
    print_to_buffer("Dezember", 0, 11);
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
        draw_rect(max_j, i, x, 1, 1, 0);
        //draw_rect(max_j, i, 1, 1, white, 1, 0);
        sprintf(buf, "%d", global_month_arr[i]);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i);
    }
    free(buf);
}

void print_day() {
    init_picture_buffer();
    char *buf1 = malloc(9 * sizeof(char));
    char *buf2 = malloc(((int) log10(global_day_arr[0].n) + 1) * sizeof(char));
    for (int i = 0; i < global_settings.top_n; i++) {
        sprintf(buf1, "%02d.%02d.%02d", global_day_arr[i].day, global_day_arr[i].month, global_day_arr[i].year);
        print_to_buffer(buf1, 0, i);
        int x = (int) ((x_size - log10(global_day_arr[0].n) - 25) *
                       (double) (global_day_arr[i].n / (double) global_day_arr[0].n));
        draw_rect(10, i, x, 1, 1, 0);
        sprintf(buf2, "%d", global_day_arr[i].n);
        print_to_buffer(buf2, x + 11, i);
    }
    free(buf1);
    free(buf2);
}

void print_average_words() {
    init_picture_buffer();
    int n = 0;
    User *temp = global_first_user;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    User **arr = sort_user(n, 32, 'd');
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        print_to_buffer(arr[i]->name, 0, i);
        if (strlen(arr[i]->name) > max_j) {
            max_j = (int) strlen(arr[i]->name);
        }
    }
    max_j++;
    char *buf;
    buf = malloc(((int) log10(arr[0]->average_words) + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        int x = (int) ((x_size - (int) log10(arr[0]->average_words) - 5 - max_j) *
                       (double) (arr[i]->average_words) / (arr[0]->average_words));
        draw_rect(max_j, i, x, 1, 1, 0);
        //draw_rect(max_j, i, 1, 1, white, 1, 0);
        sprintf(buf, "%.2lf", arr[i]->average_words);
        if (x > 0)
            print_to_buffer(buf, max_j + x + 1, i);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i);
    }
    free(arr);
    free(buf);
}

void print_message_len(unsigned short mode) {
    init_picture_buffer();
    int n = 0;
    User *temp = global_first_user;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    User **arr = sort_user(n, 24, 'u');
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        print_to_buffer(arr[i]->name, 0, i);
        if (strlen(arr[i]->name) > max_j) {
            max_j = (int) strlen(arr[i]->name);
        }
    }
    User arr2[n][1];
    for (int i = 0; i < n; i++) {
        arr2[i][0] = arr[i][0];
    }
    max_j++;
    char *buf;
    if (mode == 0) {
        buf = malloc(((int) log10(arr[0]->message_len) + 1) * sizeof(char));
        for (int i = 0; i < n; i++) {
            int x = (int) ((x_size - (int) log10(arr[0]->message_len) - 2 - max_j) * (double) (arr[i]->message_len) /
                           (arr[0]->message_len));
            draw_rect(max_j, i, x, 1, 1, 0);

            //draw_rect(max_j, i, 1, 1, white, 1, 0);
            itoa((int) arr[i]->message_len, buf, 10);
            if (x > 0)
                print_to_buffer(buf, max_j + x + 1, i);
            else
                //print_to_buffer(buf, max_j + 2, i, white, black);
                print_to_buffer(buf, max_j, i);
        }
    } else if (mode == 1) {
        buf = malloc(3 * sizeof(char));
        for (int i = 0; i < n; i++) {
            int x = (int) ((x_size - 6 - max_j) * (double) (arr[i]->message_len) / (arr[0]->message_len));
            draw_rect(max_j, i, x, 1, 1, 0);
            //draw_rect(max_j, i, 1, 1, white, 1, 0);
            float val = (float) arr[i]->message_len * 100 / (float) global_message_n;
            sprintf(buf, "%.1f", val);
            if (x > 0)
                print_to_buffer(strcat(buf, "%"), max_j + x + 1, i);
            else
                //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
                print_to_buffer(strcat(buf, "%"), max_j, i);

        }
    }
    free(arr);
    free(buf);
}

void print_date_message() {
    bool input;
    clear_screen();
    init_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    unsigned int day, month, year;
    do {
        input = true;
        Message *temp = global_first_message;
        while (temp->next->next != NULL)
            temp = temp->next;
        printf("  Wann wurde die Nachricht geschrieben (zwischen %02d.%02d.%02d und %02d.%02d.%02d) [dd.mm.yy]:\n  ",
               (int) global_first_message->day, (int) global_first_message->month, (int) global_first_message->year,
               (int) temp->day,
               (int) temp->month, (int) temp->year);
        char *buffer = malloc(9 * sizeof(char));
        if (get_string(buffer, 9, NULL, 0) == NULL)
            return;
        if (sscanf(buffer, "%d.%d.%d", &day, &month, &year) != 3) {
            input = false;
        }

        if (true_day(day, month) == false || true_month(month) == false) {
            input = false;
            _putws(L"\n  Gib bitte ein g\x81\x6ctiges Datum ein\n\n");
        } else if (true_date(day, month, year, temp) == false) {
            input = false;
            _putws(L"\n  Bitte gib ein Datum im g\x81\x6ctigen Zeitraum sein\n\n");
        }
        free(buffer);
    } while (input == false);

    Message *temp = global_first_message;
    int i = 0;
    int output_size = 1000;
    char *output = malloc(output_size * sizeof(char));
    if (output == NULL) {
        perror("malloc");
    }
    bool found = false;
    while (temp != NULL) {
        if (((temp->user != NULL ? strlen(temp->user) : 1) + (temp->message != NULL ? strlen(temp->message) : 1)) <
            output_size - 15) {
            sprintf(output, "%d.%d.%d, %02d:%02d - %s: %s", (int) temp->day, (int) temp->month, (int) temp->year,
                    (int) temp->hour, (int) temp->minute, temp->user,
                    temp->message);
            print_to_buffer(output, 0, i);
            i++;
            if (found == false) {
                if (check_date(temp->day, temp->month, temp->year, day, month, year) == -1)
                    global_current_pos += 2;
                else
                    found = true;
            }
        }
        temp = temp->next;
    }
    printf("%p", output);
    free(output);
    draw_picture_buffer();
}

void print_user_message() {
    clear_screen();
    init_picture_buffer();

    bool input;
    int max_c = 0, x, i = 0;

    User *temp = global_first_user;
    while (temp->next != NULL) {
        x = (int) strlen(temp->name);
        if (x > max_c)
            max_c = x;
        print_to_buffer(temp->name, 0, i);
        i++;
        temp = temp->next;
    }
    draw_picture_buffer();

    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    char *buf = malloc((max_c + 1) * sizeof(char));
    do {
        input = true;
        printf("  Gib den Namen des Nutzers ein\n  ");
        if (get_string(buf, max_c + 1, NULL, 0) == NULL)
            return;
        temp = user_exists(buf);
        if (temp == NULL) {
            printf("\n  Diesen Nutzer gibt es nicht!\n\n");
            input = false;
        }
    } while (input == false);
    free(buf);

    init_picture_buffer();
    Message *message = temp->message;
    i = 0;
    while (message != NULL) {
        print_to_buffer(message->message, 0, i);
        i++;
        message = message->nextUser;
    }
}

void print_settings_example() {
    init_picture_buffer();
    print_to_buffer("Max Mustermann", 0, 0);
    print_to_buffer("Erika Musterfrau", 0, 1);
    print_to_buffer("Otto Normalverbraucher", 0, 2);
    draw_rect(24, 0, (int)(x_size * 0.95 - 26), 1, 1, 0);
    draw_rect(24, 1, (int)(x_size * 0.55 - 26), 1, 1, 0);
    draw_rect(24, 2, (int)(x_size * 0.33 - 26), 1, 1, 0);
}