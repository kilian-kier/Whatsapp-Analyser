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
    int n = 0;
    User *temp = first_user;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    User **arr = sort_user(n);
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        print_to_buffer(arr[i]->name,0,i*2,white,black);
        if(strlen(arr[i]->name)>max_j){
            max_j = strlen(arr[i]->name);
        }
    }
    max_j++;
    int j;
    for (int i = 0; i < n; i++) {
        //Balken von Balkendiagramm
        draw_rect(max_j,i*2,(x_size - (int)log10(arr[0]->nachrichten_len) - 2) * arr[i]->nachrichten_len/arr[0]->nachrichten_len-max_j,1,white,1,0);
        draw_rect(max_j,i*2,1,1,white,1,0);

        char *buf = malloc((int)log10(arr[i]->nachrichten_len) + 1 * sizeof(char));
        itoa(arr[i]->nachrichten_len, buf, 10);
        int k = (int) log10(arr[i]->nachrichten_len);
        //Länge der Wörter
        print_to_buffer(buf,x_size - k - 1,i*2,white,black);
        free(buf);
    }
    free(arr);
}

User **sort_user(int n) {
    User **arr = malloc(n * sizeof(char *));
    User *temp = first_user;
    int i = 0;
    while (temp->next != NULL) {
        arr[i] = temp;
        temp = temp->next;
        i++;
    }
    // TODO: Merge Sort
    for (i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i]->nachrichten_len < arr[i+1]->nachrichten_len) {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
    return arr;
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


