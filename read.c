#include "read.h"

void readFile(FILE *f) {
    if (f == NULL)
        perror("fopen");
    else {
        int size = countlines(f);
        Nachricht arr[size];
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
