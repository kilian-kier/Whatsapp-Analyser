#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int tag :5;
    unsigned int monat :4;
    unsigned int jahr :7;
    unsigned int stunde :5;
    unsigned int minute :6;
    char *user;
    char nachricht[1000];
} Nachricht;

int countlines(FILE *f);

void print_nachricht(Nachricht *nachricht);

int main(int argc, char *argv[]) {
    /*argc - wie viele Paramter (.exe inclusiv)
      argv - Array mit den Paramter (.exe inclusiv)*/
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        perror("fopen");
    else {
        Nachricht arr[countlines(f)];
        char buffer[1000];
        char two_char_buffer[3];
        //strtol convert String to Integer
        char *strtol_buffer[1];
        int i = 0;
        while (fgets(buffer, 1000, f) != NULL) {
            strncpy(two_char_buffer, buffer, 2);
            arr[i].tag = (short)strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer+3, 2);
            arr[i].monat = (short)strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer+6, 2);
            arr[i].jahr = (short)strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer+10, 2);
            arr[i].stunde = (short)strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer+13, 2);
            arr[i].minute = (short)strtol(two_char_buffer, strtol_buffer, 10);
            //TODO: User und Nachricht kloppn no et gonz
            if (strchr(buffer+13, ':') != NULL) {
                arr[i].user = malloc((int)(buffer + 18 - strchr(buffer, ':'))* 3 * sizeof(char));
                strncpy(arr[i].user, buffer + 18, buffer + 18 - strchr(buffer, ':'));
                arr[i].user[buffer + 18 - strchr(buffer, ':')] = '\0';
            } else
                arr[i].user = NULL;
            strcpy(arr[i].nachricht, buffer+18);
            i++;
        }
        print_nachricht(&arr[3]);
    }
    return 0;
}

int countlines(FILE *f) {
    int lines = 0, c = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n')
            lines++;
    }
    //pointer zurücksetzen auf den start der Datei
    rewind(f);
    return lines;
}

void print_nachricht(Nachricht *nachricht) {
    printf("%02u.", nachricht->tag);
    printf("%02u.", nachricht->monat);
    printf("%02u\n", nachricht->jahr);
    printf("%02u:", nachricht->stunde);
    printf("%02u\n", nachricht->minute);
    printf("%s schrieb:\n", nachricht->user);
    printf("%s\n", nachricht->nachricht);
}
