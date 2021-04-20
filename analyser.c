#include "analyser.h"

void read_user() {
    Nachricht *nachricht = first_nachricht;
    User *user = (User *) malloc(sizeof(User));
    first_user = user;
    User *temp_user = user;
    Nachricht *temp_nachricht;
    int n_user = 0, found = 0;
    while (nachricht->next != NULL) {
        if (nachricht->user == NULL) {
            nachricht = nachricht->next;
            continue;
        }
        temp_user = first_user;
        found = 0;
        for (int i = 0; i < n_user; i++) {
            if (found != 1) {
                while (temp_user->next != NULL) {
                    if (strcmp(nachricht->user, temp_user->name) == 0) {
                        temp_nachricht = temp_user->nachrichten;
                        while (temp_nachricht->nextUser != NULL) {
                            temp_nachricht = temp_nachricht->nextUser;
                        }
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
            user->nachrichten->nextUser = NULL;
            nachricht = nachricht->next;
            User *next = (User *) malloc(sizeof(User));
            user->next = next;
            user = next;
            user->next = NULL;
        }
    }
    print_user();
}

void print_user() {
    User *temp = first_user;
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}
    Nachricht *ptr = first_nachricht;
    while (ptr != NULL) {

    }
}


//Wochentag und Uhrzeit
//0= Montag
int *count_date(Nachricht *ptr){
    int *arr1 = (int *)malloc(7*sizeof(int));
    for(int x = 0; x < 7; x++){
        *arr1 = 0;
        arr1 ++;
    }
    short weekday;
    int h, k;
    while(ptr->next != NULL){
        if(ptr->monat <= 2){
            h = ptr->monat + 12;
            k = ptr ->jahr -1;
        }
        else{
            h = ptr->monat;
            k = ptr->jahr;
        }
        weekday = (ptr->tag+2*h+(3*h+3)/5+k+k/4-k/100+k/400+1)%7;
        switch(weekday){
            case 0: *(arr1+6) += 1; break;
            case 1: *arr1 += 1; break;
            case 2: *(arr1+1) += 1; break;
            case 3: *(arr1+2) += 1; break;
            case 4: *(arr1+3) += 1; break;
            case 5: *(arr1+4) += 1; break;
            case 6: *(arr1+5) += 1; break;
            default: perror("Fehler Wochentag!"); break;
        }
        ptr = ptr->next;
    }
    return arr1;
}
