#include "include/read_user.h"

void *read_user() {
    Message *message = global_first_message;
    User *user = (User *) malloc(sizeof(User));
    global_first_user = user;
    User *temp_user;
    Message *temp_message;
    int n_user = 0, found;
    while (message->next != NULL) {
        if (message->user == NULL) {
            message = message->next;
            continue;
        }
        temp_user = global_first_user;
        found = 0;
        for (int i = 0; i < n_user; i++) {
            if (found != 1) {
                //TODO: Debuggen crasht do olbm, wohrscheinlich wegn é ba René
                while (temp_user->next != NULL) {
                    if (strcmp(message->user, temp_user->name) == 0) {
                        temp_message = temp_user->message;
                        while (temp_message->nextUser != NULL) {
                            temp_message = temp_message->nextUser;
                        }
                        temp_user->message_len++;
                        temp_user->hour_arr[message->hour]++;
                        int h, k;
                        if ((int)message->month <= 2) {
                            h = (int)message->month + 12;
                            k = (int)message->year - 1;
                        } else {
                            h = (int)message->month;
                            k = (int)message->year;
                        }
                        user->weekday_arr[((int)message->day + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7]++;
                        temp_user->average_words += count_words(message->message);
                        temp_message->nextUser = message;
                        temp_message->nextUser->nextUser = NULL;
                        found = 1;
                        message = message->next;
                        break;
                    }
                    temp_user = temp_user->next;
                }
            }
        }
        if (found != 1) {
            n_user++;
            user->name = (char *) malloc(strlen(message->user) * sizeof(char));
            strcpy(user->name, message->user);
            user->message = message;
            user->average_words = count_words(message->message);
            user->message_len = 1;
            user->message->nextUser = NULL;
            for (int j = 0; j < 24; j++)
                user->hour_arr[j] = 0;
            for (int j = 0; j < 7; j++)
                user->weekday_arr[j] = 0;
            user->hour_arr[message->hour]++;
            int h, k;
            if ((int)message->month <= 2) {
                h = (int)message->month + 12;
                k = (int)message->year - 1;
            } else {
                h = (int)message->month;
                k = (int)message->year;
            }
            user->weekday_arr[((int)message->day + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7]++;
            message = message->next;
            User *next = (User *) malloc(sizeof(User));
            user->next = next;
            user = next;
            user->next = NULL;
        }
    }
    temp_user = global_first_user;
    int n = 0;
    while (temp_user->next != NULL) {
        n++;
        temp_user->average_words = temp_user->average_words / temp_user->message_len;
        temp_user = temp_user->next;
    }
}
