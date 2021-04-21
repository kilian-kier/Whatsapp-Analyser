#include "analyser.h"

int anz_nachrichten = 0;

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
                        temp_user->nachrichten_len++;
                        temp_user->total_words += count_words(nachricht->nachricht);
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
            user->total_words = count_words(nachricht->nachricht);
            user->nachrichten_len = 1;
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
    while (temp->next != NULL) {
        printf("%d, %d, %d\n", temp->nachrichten_len, temp->total_words, temp->total_words/temp->nachrichten_len);
        temp = temp->next;
    }
}


//Nachrichten anhand der Wochentage zählen
int *count_weekday(){
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *)malloc(7*sizeof(int));
    for(int x = 0; x < 7; x++){
        *(arr1+x) = 0;
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


void count_nachrichten(){
    Nachricht *ptr = first_nachricht;
    while(ptr != NULL){
        anz_nachrichten ++;
        ptr = ptr->next;
    }
}

//Nachrichten anhand von Stunden zählen
int *count_hours(){
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *)malloc(24*sizeof(int));
    for(int x = 0; x < 24; x++){
        *(arr1+x) = 0;
    }
    while(ptr->next != NULL){
        switch(ptr->stunde){
            case 0: *(arr1) += 1; break;
            case 1: *(arr1+1) += 1; break;
            case 2: *(arr1+2) += 1; break;
            case 3: *(arr1+3) += 1; break;
            case 4: *(arr1+4) += 1; break;
            case 5: *(arr1+5) += 1; break;
            case 6: *(arr1+6) += 1; break;
            case 7: *(arr1+7) += 1; break;
            case 8: *(arr1+8) += 1; break;
            case 9: *(arr1+9) += 1; break;
            case 10: *(arr1+10) += 1; break;
            case 11: *(arr1+11) += 1; break;
            case 12: *(arr1+12) += 1; break;
            case 13: *(arr1+13) += 1; break;
            case 14: *(arr1+14) += 1; break;
            case 15: *(arr1+15) += 1; break;
            case 16: *(arr1+16) += 1; break;
            case 17: *(arr1+17) += 1; break;
            case 18: *(arr1+18) += 1; break;
            case 19: *(arr1+19) += 1; break;
            case 20: *(arr1+20) += 1; break;
            case 21: *(arr1+21) += 1; break;
            case 22: *(arr1+22) += 1; break;
            case 23: *(arr1+23) += 1; break;
            default: perror("Fehler Uhrzeit!"); break;
        }
        ptr = ptr->next;
    }
    return arr1;
}