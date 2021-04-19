#include "analyser.h"

void read_user() {
    Nachricht *nachricht = first_nachricht;
    User *user = (User *) malloc(sizeof(User));
    first_user = user;
    User *temp = user;
    Nachricht *swap;
    int n_user = 1;
    while (nachricht != NULL) {
        if (nachricht->user == NULL) {
            nachricht = nachricht->next;
            continue;
        }
        for (int i = 0; i < n_user; i++) {
            if (strcmp(nachricht->user, temp->name) == 0) {
                swap = temp->nachrichten->next;
                temp->nachrichten->next =
            }
        }
        user->name = (char *) malloc(strlen(nachricht->user) * sizeof(char));
        strcpy(user->name, nachricht->user);
        user->nachrichten = nachricht;
        nachricht = nachricht->next;
        User *next = (User *) malloc(sizeof(User));
        user->next = next;
        user = next;
    }
    printf("%s", first_user->next->name);
}