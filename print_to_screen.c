#include "include/print_to_screen.h"

void print_weekday() {
    init_picture_buffer();
    print_to_buffer("Montag", 0, 0, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Dienstag", 0, 1, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Mittwoch", 0, 2, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Donnerstag", 0, 3, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Freitag", 0, 4, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Samstag", 0, 5, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Sonntag", 0, 6, global_settings.fontcolor, global_settings.background);
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
            print_to_buffer(buf, max_j + x + 1, i, global_settings.fontcolor, global_settings.background);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i, global_settings.fontcolor, global_settings.background);
    }
    free(buf);
}

void print_hour() {
    init_picture_buffer();
    for (int i = 0; i < 24; i++) {
        char string[6];
        sprintf(string, "%02d-%02d", i, i + 1);
        print_to_buffer(string, 0, i, global_settings.fontcolor, global_settings.background);
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
            print_to_buffer(buf, max_j + x + 1, i, global_settings.fontcolor, global_settings.background);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i, global_settings.fontcolor, global_settings.background);
    }
    free(buf);
}

void print_month() {
    init_picture_buffer();
    print_to_buffer("Januar", 0, 0, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Februar", 0, 1, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Maerz", 0, 2, global_settings.fontcolor, global_settings.background);
    print_to_buffer("April", 0, 3, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Mai", 0, 4, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Juni", 0, 5, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Juli", 0, 6, global_settings.fontcolor, global_settings.background);
    print_to_buffer("August", 0, 7, global_settings.fontcolor, global_settings.background);
    print_to_buffer("September", 0, 8, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Oktober", 0, 9, global_settings.fontcolor, global_settings.background);
    print_to_buffer("November", 0, 10, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Dezember", 0, 11, global_settings.fontcolor, global_settings.background);
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
            print_to_buffer(buf, max_j + x + 1, i, global_settings.fontcolor, global_settings.background);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i, global_settings.fontcolor, global_settings.background);
    }
    free(buf);
}

void print_day() {
    init_picture_buffer();
    char *buf1 = malloc(9 * sizeof(char));
    char *buf2 = malloc(((int) log10(global_day_arr[0].n) + 1) * sizeof(char));
    for (int i = 0; i < global_settings.top_n; i++) {
        sprintf(buf1, "%02d.%02d.%02d", global_day_arr[i].day, global_day_arr[i].month, global_day_arr[i].year);
        print_to_buffer(buf1, 0, i, global_settings.fontcolor, global_settings.background);
        int x = (int) ((x_size - log10(global_day_arr[0].n) - 25) *
                       (double) (global_day_arr[i].n / (double) global_day_arr[0].n));
        draw_rect(10, i, x, 1, 1, 0);
        sprintf(buf2, "%d", global_day_arr[i].n);
        print_to_buffer(buf2, x + 11, i, global_settings.fontcolor, global_settings.background);
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
        print_to_buffer(arr[i]->name, 0, i, global_settings.fontcolor, global_settings.background);
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
            print_to_buffer(buf, max_j + x + 1, i, global_settings.fontcolor, global_settings.background);
        else
            //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
            print_to_buffer(buf, max_j, i, global_settings.fontcolor, global_settings.background);
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
        print_to_buffer(arr[i]->name, 0, i, global_settings.fontcolor, global_settings.background);
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
                print_to_buffer(buf, max_j + x + 1, i, global_settings.fontcolor, global_settings.background);
            else
                //print_to_buffer(buf, max_j + 2, i, white, black);
                print_to_buffer(buf, max_j, i, global_settings.fontcolor, global_settings.background);
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
                print_to_buffer(strcat(buf, "%"), max_j + x + 1, i, global_settings.fontcolor,
                                global_settings.background);
            else
                //print_to_buffer(strcat(buf, "%"), max_j + 2, i, white, black);
                print_to_buffer(strcat(buf, "%"), max_j, i, global_settings.fontcolor, global_settings.background);

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
            print_to_buffer(output, 0, i, global_settings.fontcolor, global_settings.background);
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
    //TODO Suchalgorithmus fos Datum
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
        i++;
        temp = temp->next;
    }

    //Create Array with Names
    temp=global_first_user;
    char*name_array[i+1];
    for(int j=0;j<i;j++){
        name_array[j]=temp->name;
        temp=temp->next;
    }
    name_array[i]=NULL;
    merge_sort(name_array,i,0,'n');

    for(int j=0;j<i;j++){
        print_to_buffer(name_array[j], 0, j, global_settings.fontcolor, global_settings.background);
    }
    draw_picture_buffer();

    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");

    char *buf = malloc((max_c + 1) * sizeof(char));
    do {
        input = true;
        printf("  Gib den Namen des Nutzers ein\n  ");
        if (get_string(buf,max_c+1,(char*)name_array,STRING_ARRAY) == NULL)
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
        print_to_buffer(message->message, 0, i, global_settings.fontcolor, global_settings.background);
        i++;
        message = message->nextUser;
    }
}

void print_word_message() {
    pthread_join(*(pthread_t *)global_threads[6][0], NULL);
    clear_screen();
    init_picture_buffer();
    draw_picture_buffer();
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");
    List *input = NULL;
    global_input_buffer = 0;
    while (global_input_buffer != '') {
        if (global_send_input == true) {
            switch (global_input_buffer) {
                case 0:
                    break;
                case 8:
                    if (input->next != NULL) {
                        global_send_input = false;
                        printf(" ");
                        delete_n_char(2);
                        input = pop(input);
                    }
                    break;
                default:
                    input = insert(&global_input_buffer, input, 'c');
                    global_send_input = false;
                    char *string = get_string_from_list(input);
                    printf("%s", string);
                    List *words = NULL;
                    words = find_word(global_first_word, string, words);
                    int len = get_list_length(words);
                    char *output = malloc(x_size);
                    Message *temp = global_first_message;
                    int i = 0;
                    while (temp->next != NULL) {
                        sprintf(output, "%d.%d.%d, %02d:%02d - %s: %.*s", (int) temp->day, (int) temp->month, (int) temp->year,
                                (int) temp->hour, (int) temp->minute, temp->user, x_size-15,
                                temp->message);
                        print_to_buffer(output, 0, i, global_settings.fontcolor, global_settings.background);
                        i++;
                        temp = temp->next;
                    }
                    for (int j = 0; j < len; j++) {
                            sprintf(output, "%.*s", ((Dictionary *) words->item.pointer)->length_word,
                                    ((Dictionary *) words->item.pointer)->words->begin_message +
                                    ((Dictionary *) words->item.pointer)->words->offset);
                            print_to_buffer(output, ((Dictionary *) words->item.pointer)->words->offset + 19,
                                            ((Dictionary *) words->item.pointer)->words->number_message, black,
                                            (Color) {0, 255, 255});
                            words = words->next;
                    }
                    draw_picture_buffer();
                    free(string);
                    free(output);
                    break;
            }
        } else
            Sleep(sync_delay);
    }
    /*char *input = malloc(buffersize);
    if (get_string(input, buffersize, NULL, 0) == NULL)
        return;*/
    /*fflush(stdin);
    fgets(input, buffersize, stdin);
    fflush(stdin);
    Dictionary *word = find_word(input, global_first_word);
    List *found = NULL;
    if (word != NULL) {
        Message *temp = global_first_message;
        int output_size = 1000;
        char *output = malloc(output_size * sizeof(char));
        int i = 0;
        word_list *words = word->words;
        while (temp->next != NULL) {
            if (((temp->user != NULL ? strlen(temp->user) : 1) + (temp->message != NULL ? strlen(temp->message) : 1)) <
                output_size - 15) {
                if (strcmp(temp->message, words->begin_message) == 0) {
                    int x = 0;
                    sprintf(output, "%d.%d.%d, %02d:%02d - %s: ", (int) temp->day, (int) temp->month,
                            (int) temp->year,
                            (int) temp->hour, (int) temp->minute, temp->user);
                    print_to_buffer(output, x, i, global_settings.fontcolor, global_settings.background);
                    x += (int)strlen(output);
                    if (words->offset != 0) {
                        strncpy(output, temp->message, words->offset);
                        output[words->offset] = 0;
                        print_to_buffer(output, x, i, global_settings.fontcolor, global_settings.background);
                        x += (int)strlen(output);
                    }
                    strncpy(output, temp->message + words->offset, word->length_word);
                    output[word->length_word] = 0;
                    print_to_buffer(output, x, i, (Color){0, 0, 0}, (Color){0, 255, 255});
                    x += (int)strlen(output);
                    strcpy(output, temp->message + words->offset + word->length_word);
                    print_to_buffer(output, x, i, global_settings.fontcolor, global_settings.background);
                    found = insert(&i, found, 'i');
                    if (words->next != NULL)
                        words = words->next;
                } else {
                    sprintf(output, "%d.%d.%d, %02d:%02d - %s: %s", (int) temp->day, (int) temp->month,
                            (int) temp->year,
                            (int) temp->hour, (int) temp->minute, temp->user,
                            temp->message);
                    print_to_buffer(output, 0, i, global_settings.fontcolor, global_settings.background);
                }
                i++;
            }
            temp = temp->next;
        }
        draw_picture_buffer();
        List *list = found;
        if (list != NULL) {
            global_current_pos = list->item.integer * (global_settings.empty_lines + 1);
        }
        draw_picture_buffer();
        while (global_input_buffer != '') {
            if (global_input_buffer == 9) {
                list = list->next;
                if (list == NULL)
                    list = found;
                global_current_pos = list->item.integer * (global_settings.empty_lines + 1);
                draw_picture_buffer();
                global_input_buffer = 0;
            }
            Sleep(sync_delay);
        }
    }*/
}

void print_settings_example() {
    init_picture_buffer();
    print_to_buffer("Max Mustermann", 0, 0, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Erika Musterfrau", 0, 1, global_settings.fontcolor, global_settings.background);
    print_to_buffer("Otto Normalverbraucher", 0, 2, global_settings.fontcolor, global_settings.background);
    draw_rect(24, 0, (int)(x_size * 0.95 - 26), 1, 1, 0);
    draw_rect(24, 1, (int)(x_size * 0.55 - 26), 1, 1, 0);
    draw_rect(24, 2, (int)(x_size * 0.33 - 26), 1, 1, 0);
    draw_picture_buffer();
}