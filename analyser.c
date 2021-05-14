#include "include/analyser.h"

void *read_user() {
    Nachricht *nachricht = first_nachricht;
    User *user = (User *) malloc(sizeof(User));
    first_user = user;
    first_user->previous = NULL;
    User *temp_user;
    Nachricht *temp_nachricht;
    int n_user = 0, found;
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
            nachricht = nachricht->next;
            User *next = (User *) malloc(sizeof(User));
            user->next = next;
            user->next->previous = user;
            user = next;
            user->next = NULL;
        }
    }
    temp_user = first_user;
    int n = 0;
    while (temp_user->next != NULL) {
        n++;
        temp_user->average_words = temp_user->average_words / temp_user->nachrichten_len;
        temp_user = temp_user->next;
    }
}

void print_average_words() {
    init_picture_buffer(picture_buffer);
    int n = 0;
    User *temp = first_user;
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
    User *temp = first_user;
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
            float val = (float) arr[i]->nachrichten_len * 100 / (float) anz_nachrichten;
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
    User *temp = first_user;
    int i = 0;
    while (temp->next != NULL) {
        arr[i] = temp;
        temp = temp->next;
        i++;
    }
    merge_sort(arr, n, offset, type);
    return arr;
}


//Wochentag und Uhrzeit
//0= Montag
int *count_weekday() {
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *) malloc(7 * sizeof(int));
    for (int x = 0; x < 7; x++) {
        *(arr1 + x) = 0;
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
        *(arr1 + weekday) += 1;
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

void count_nachrichten() {
    anz_nachrichten = 0;
    Nachricht *ptr = first_nachricht;
    while (ptr != NULL) {
        anz_nachrichten++;
        ptr = ptr->next;
    }
}

//Nachrichten anhand von Stunden zählen
int *count_hours() {
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *) malloc(24 * sizeof(int));
    for (int x = 0; x < 24; x++) {
        *(arr1 + x) = 0;
    }
    while (ptr->next != NULL) {
        *(arr1 + ptr->stunde) += 1;
        ptr = ptr->next;
    }
    return arr1;
}

int *count_month() {
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *) malloc(12 * sizeof(int));
    for (int x = 0; x < 12; x++) {
        *(arr1 + x) = 0;
    }
    while (ptr->next != NULL) {
        *(arr1 + ptr->monat) += 1;
        ptr = ptr->next;
    }
    return arr1;
}


/*void woerterbook() {
    first_word = NULL;
    int laenge, offset;
    char *anfang;
    Nachricht *ptr = first_nachricht;
    while (ptr->next != NULL) {
        if ((strcmp(ptr->nachricht,"<medien ausgeschlossen>")) == 0) continue;
        offset = 0;
        while (ptr->nachricht[offset] != '\0' && ptr->nachricht[offset] != '\n') {
            anfang = ptr->nachricht + offset;
            laenge = 0;
            while (ptr->nachricht[laenge + offset] != ' ' && ptr->nachricht[laenge + offset] != '.' &&
                   ptr->nachricht[laenge + offset] != ',' && ptr->nachricht[laenge + offset] != ':' && ptr->nachricht[laenge + offset] != '!' &&
                   ptr->nachricht[laenge + offset] != '?' && ptr->nachricht[laenge + offset] != '\n' &&
                   ptr->nachricht[laenge + offset] != '\0' &&
                   ptr->nachricht[laenge + offset] != '<' &&
                   ptr->nachricht[laenge + offset] != '>' &&
                   ptr->nachricht[laenge + offset] != '|' &&
                   ptr->nachricht[laenge + offset] != '/'){
                laenge++;
            }
            if (laenge == 0) offset++;
            //else insert(anfang,laenge,first_word);
            }
        ptr = ptr->next;
    }
    //print(first_word);
}


void insert(char *anfang, int l, Woerterbook *temp){
    int x = 0;
    if (temp == NULL){
        Woerterbook *x = (Woerterbook *) malloc(sizeof(Woerterbook));
        x->left = NULL;
        x->right = NULL;
        x->anzahl = 1;
        x->wortanfang = anfang;
        x->laenge = l;
        if (first_word == NULL) first_word = x;
        else temp = x;
        return;
    }
    else {
        if (l <= temp->laenge) x = l;
        else x = temp->laenge;
        if ((strncmp(anfang, temp->wortanfang, x) == 0)) {
            temp->anzahl++;
            return;
        }
        else if ((strncmp(anfang, temp->wortanfang, x) < 0)) insert(anfang, l, temp->left);
        else if ((strncmp(anfang, temp->wortanfang, x) > 0)) insert(anfang, l, temp->right);
    }
}

void print(Woerterbook *ptr){
    char buffer[200];
    if(ptr == NULL) return;
    print(ptr->left);
    strncpy(buffer,ptr->wortanfang,ptr->laenge);
    printf("%s",buffer);
    print(ptr->right);
}*/