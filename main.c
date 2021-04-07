#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buffersize 1000
typedef struct {
    unsigned int tag :5;
    unsigned int monat :4;
    unsigned int jahr :7;
    unsigned int stunde :5;
    unsigned int minute :6;
    char *user;
    char *nachricht;
} Nachricht;

int countlines(FILE *f);
int getMessage(char *buffer,FILE *f);
void print_nachricht(Nachricht *nachricht);

int main(int argc, char *argv[]) {
    /*argc - wie viele Paramter (.exe inclusiv)
      argv - Array mit den Paramter (.exe inclusiv)*/
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        perror("fopen");
    else {
        Nachricht *arr = (Nachricht *) malloc(countlines(f) * sizeof(Nachricht));
        char buffer[buffersize];
        char two_char_buffer[3];
        //strtol convert String to Integer
        char *strtol_buffer[1];
        int i = 0;
        while (getMessage(buffer,f) != NULL) {
            strncpy(two_char_buffer, buffer, 2);
            arr[i].tag = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 3, 2);
            arr[i].monat = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 6, 2);
            arr[i].jahr = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 10, 2);
            arr[i].stunde = (short) strtol(two_char_buffer, strtol_buffer, 10);
            strncpy(two_char_buffer, buffer + 13, 2);
            arr[i].minute = (short) strtol(two_char_buffer, strtol_buffer, 10);
            //TODO: User und Nachricht kloppn no et gonz
            if (strchr(buffer + 13, ':') != NULL) {
                arr[i].user = malloc((int) (buffer + 18 - strchr(buffer, ':')) * 3 * sizeof(char));
                strncpy(arr[i].user, buffer + 18, buffer + 18 - strchr(buffer, ':'));
                arr[i].user[buffer + 18 - strchr(buffer, ':')] = '\0';
            } else {
                arr[i].user = NULL;
            }
            arr[i].nachricht = (char *) malloc((strlen(buffer + 18) + 1) * sizeof(char));
            strcpy(arr[i].nachricht, buffer + 18);
        }
        print_nachricht(&arr[3]);

        for(int j=0;j<i;j++){
            free(arr[j].nachricht);
            free(arr[j].user);
        }
        free(arr);
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
int getMessage(char *buffer,FILE *f){
    buffer[0]=0;
    int * ret=0;
    char temp[buffersize];
    int position=0;
    do{
        position=ftell(f);
        ret=fgets(temp, buffersize, f);
        printf("%s",temp);
    }while(ret!=NULL && temp[2]!='.');
    if(ret!=NULL){
        fseek(f, position+1, SEEK_SET);
    }
    strcpy(buffer,temp);
    return ret;
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
