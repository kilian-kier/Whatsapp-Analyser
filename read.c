#include "read.h"

void readFile(FILE *f) {
    if (f == NULL)
        perror("fopen");
    else {
        char buffer[1000];
        char two_char_buffer[3];
        //strtol convert String to Integer
        char *strtol_buffer[1];
        Nachricht *ptr = (Nachricht *)malloc(sizeof(Nachricht));
        first = ptr;
        int size = 0;
        while (fgets(buffer, 1000, f) != NULL) {
            strncpy(two_char_buffer, buffer, 2);
            ptr->tag = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 3, 2);
            ptr->monat = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 6, 2);
            ptr->jahr = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 10, 2);
            ptr->stunde = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 13, 2);
            ptr->minute = (short) strtol(two_char_buffer, strtol_buffer, 10);
            if (strchr(buffer+13, ':') != NULL) {
                size = lenght(buffer,':',18);
                ptr->user = (char *) malloc((size * sizeof(char)));
                strncpy(ptr->user, buffer + 18, size);
                ptr->user[size] = '\0';
                size = lenght(buffer,'\n',size+18);
                ptr->nachricht = (char *) malloc(size * sizeof(char));
                strncpy(ptr->nachricht, buffer+18+strlen(ptr->user)+2,size);
            } else {
                ptr->user = NULL;
                size = lenght(buffer,'\n',size+18);
                ptr->nachricht = (char *) malloc(size * sizeof(char));
                strncpy(ptr->nachricht, buffer + 18, size);
            }
            Nachricht *next = (Nachricht *) malloc(sizeof(Nachricht));
            ptr->next = next;
            next->previous = ptr;
            ptr = ptr->next;
        }
        ptr->next = NULL;
        print_nachricht(get_nachricht(4));
    }
}

int lenght(const char buffer[1000], char suche,int anfang){
    int x = 0;
    while(x < 1000){
        if(buffer[x+anfang] == suche) break;
        x++;
    }
    return x;
}