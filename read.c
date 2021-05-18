#include "include/read.h"
#include "include/analyser.h"
#include <stdbool.h>

void *readFile(void *f) {
    if ((FILE *)f == NULL)
        perror("fopen_readFile");
    else {
        char buffer[buffersize];
        char two_char_buffer[3];
        //strtol convert String to Integer
        char *strtol_buffer[1];
        Nachricht *ptr = (Nachricht *)malloc(sizeof(Nachricht));
        global_first_nachricht = ptr;
        int size = 0;
        while (getMessage(buffer,f) != NULL) {
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
                ptr->nachricht = string_convert(buffer,20 + strlen(ptr->user));
            } else {
                ptr->user = NULL;
                ptr->nachricht = string_convert(buffer,20);
            }
            Nachricht *next = (Nachricht *) malloc(sizeof(Nachricht));
            ptr->next = next;
            next->previous = ptr;
            ptr = ptr->next;
        }
        ptr->next = NULL;
        count_nachrichten();
        pthread_create(&read_user_tread, NULL, read_user, NULL);
        pthread_create(&weekday_thread, NULL, count_weekday, NULL);
        pthread_create(&hour_thread, NULL, count_hours, NULL);
        pthread_create(&month_thread, NULL, count_month, NULL);
    }
}
char * getMessage(char *buffer,FILE *f){
    buffer[0]=0;
    char * ret=NULL;
    char temp[buffersize];
    int position=0;
    do{
        ret=fgets(buffer+strlen(buffer), buffersize, f);
        position=ftello(f);
        fgets(temp,buffersize,f);
        fseeko(f, position, SEEK_SET);
    }while(ret!=NULL && !checkNewString(temp));
    return ret;
}
bool checkNewString(const char *string){
    bool valid=true;
    if (strlen(string) < 9)
        return false;
    if(string[2]!='.' || string[5]!='.' || string[8]!=','){
        valid=false;
    }
    return valid;
}
int lenght(const char buffer[buffersize], char suche,int anfang){
    int x = 0;
    while(x < buffersize){
        if(buffer[x+anfang] == suche) break;
        x++;
    }
    return x;
}


char * string_convert(char *string, int offset) {
    int len = strlen(string), y = 0;
    char string2[len];
    for(int i=offset; i<len; i++) {
        if(string[i] >= 'A' && string[i] <= 'Z') string2[y] = string[i] + 32;
        else if (string[i] == -61 && (string[i+1] == -92 || string[i+1] == -100)){
            string2[y] = 'a';
            y++;
            string2[y] = 'e';
            i++;
        }
        else if (string[i] == -61 && (string[i+1] == -74 || string[i+1] == -106)){
            string2[y] = 'o';
            y++;
            string2[y] = 'e';
            i++;
        }
        else if (string[i] == -61 && (string[i+1] == -68) || string[i+1] == -124){
            string2[y] = 'u';
            y++;
            string2[y] = 'e';
            i++;
        }
        else if (string[i] == -61 && string[i+1] == -97){
            string2[y] = 's';
            y++;
            string2[y] = 's';
            i++;
        }

        else if (string[i] < 0) {
            string2[y] = ' ';
            i += 3;
        }
        else if (string[i] == 13) string2[y] = ' ';
        else string2[y] = string[i];
        y++;
    }
    string2[y] = '\0';
    char *ptr = (char *) malloc ((y+1) * sizeof(char));
    strcpy(ptr,string2);
    return ptr;
}
