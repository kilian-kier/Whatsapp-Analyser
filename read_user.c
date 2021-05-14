//
// Created by kierk on 14.05.2021.
//

#include "include/read_user.h"

void *read_user() {
    Nachricht *nachricht = global_first_nachricht;
    User *user = (User *) malloc(sizeof(User));
    global_first_user = user;
    global_first_user->previous = NULL;
    User *temp_user;
    Nachricht *temp_nachricht;
    int n_user = 0, found;
    while (nachricht->next != NULL) {
        if (nachricht->user == NULL) {
            nachricht = nachricht->next;
            continue;
        }
        temp_user = global_first_user;
        found = 0;
        for (int i = 0; i < n_user; i++) {
            if (found != 1) {
                //TODO: Debuggen crasht do olbm
                while (temp_user->next != NULL) {
                    if (strcmp(nachricht->user, temp_user->name) == 0) {
                        temp_nachricht = temp_user->nachrichten;
                        while (temp_nachricht->nextUser != NULL) {
                            temp_nachricht = temp_nachricht->nextUser;
                        }
                        temp_user->nachrichten_len++;
                        temp_user->hour_arr[nachricht->stunde]++;
                        int h, k;
                        if ((int)nachricht->monat <= 2) {
                            h = (int)nachricht->monat + 12;
                            k = (int)nachricht->jahr - 1;
                        } else {
                            h = (int)nachricht->monat;
                            k = (int)nachricht->jahr;
                        }
                        user->weekday_arr[((int)nachricht->tag + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7]++;
                        temp_user->average_words += count_words(nachricht->nachricht);
                        temp_nachricht->nextUser = nachricht;
                        temp_nachricht->nextUser->nextUser = NULL;
                        found = 1;
                        nachricht = nachricht->next;
                        break;
                    }
                    temp_user = temp_user->next;
                }
            }
        }
        if (found != 1) {
            n_user++;
            user->name = (char *) malloc(strlen(nachricht->user) * sizeof(char));
            strcpy(user->name, nachricht->user);
            user->nachrichten = nachricht;
            user->average_words = count_words(nachricht->nachricht);
            user->nachrichten_len = 1;
            user->nachrichten->nextUser = NULL;
            for (int j = 0; j < 24; j++)
                user->hour_arr[j] = 0;
            for (int j = 0; j < 7; j++)
                user->weekday_arr[j] = 0;
            user->hour_arr[nachricht->stunde]++;
            int h, k;
            if ((int)nachricht->monat <= 2) {
                h = (int)nachricht->monat + 12;
                k = (int)nachricht->jahr - 1;
            } else {
                h = (int)nachricht->monat;
                k = (int)nachricht->jahr;
            }
            user->weekday_arr[((int)nachricht->tag + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7]++;
            nachricht = nachricht->next;
            User *next = (User *) malloc(sizeof(User));
            user->next = next;
            user->next->previous = user;
            user = next;
            user->next = NULL;
        }
    }
    temp_user = global_first_user;
    int n = 0;
    while (temp_user->next != NULL) {
        n++;
        temp_user->average_words = temp_user->average_words / temp_user->nachrichten_len;
        temp_user = temp_user->next;
    }
}
