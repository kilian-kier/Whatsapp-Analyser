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
            //TODO: User und Nachricht kloppn no et gonz
            if (strchr(buffer + 13, ':') != NULL) {
                ptr->user = malloc((int) (buffer + 18 - strchr(buffer, ':')) * 3 * sizeof(char));
                strncpy(ptr->user, buffer + 18, buffer + 18 - strchr(buffer, ':'));
                ptr->user[buffer + 18 - strchr(buffer, ':')] = '\0';
            } else
                ptr->user = NULL;
            strcpy(ptr->nachricht, buffer + 18);
            Nachricht *next = (Nachricht *) malloc(sizeof(Nachricht));
            ptr->next = next;
            next->previous = ptr;
            ptr = ptr->next;
        }
        ptr->next = NULL;
        print_nachricht(get_nachricht(3));
    }
}
