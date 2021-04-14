#include "read.h"

void readFile(FILE *f) {
    if (f == NULL)
        perror("fopen");
    else {
        char buffer[buffersize];
        char two_char_buffer[3];
        //strtol convert String to Integer
        char *strtol_buffer[1];
        Nachricht *ptr = (Nachricht *)malloc(sizeof(Nachricht));
        first_nachricht = ptr;
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
                string_to_lower(ptr->user);
                size = lenght(buffer,'\n',size+18);
                ptr->nachricht = (char *) malloc(size * sizeof(char));
                strncpy(ptr->nachricht, buffer+18+strlen(ptr->user)+2,size);
            } else {
                ptr->user = NULL;
                size = lenght(buffer,'\n',size+18);
                ptr->nachricht = (char *) malloc(size * sizeof(char));
                strncpy(ptr->nachricht, buffer + 18, size);
            }
            string_to_lower(ptr->nachricht);
            Nachricht *next = (Nachricht *) malloc(sizeof(Nachricht));
            ptr->next = next;
            next->previous = ptr;
            ptr = ptr->next;
        }
        ptr->next = NULL;
        print_nachricht(get_nachricht(15));
    }
}

int lenght(const char buffer[1000], char suche,int anfang){
    int x = 0;
    while(x < buffersize){
        if(buffer[x+anfang] == suche) break;
        x++;
    }
    return x;
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
bool checkNewString(char *string){
    bool valid=true;
    if(string[2]!='.' || string[5]!='.' || string[8]!=','){
        valid=false;
    }
    return valid;
}

char * string_to_lower(char *string) {
    int i;
    int len = strlen(string);
    for(i=0; i<len; i++) {
        if(string[i] >= 'A' && string[i] <= 'Z') {
            string[i] += 32;
        }
    }
    return string;
}