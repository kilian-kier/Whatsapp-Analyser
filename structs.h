#ifndef INFORMATIK_PROJEKT_STRUCTS_H
#define INFORMATIK_PROJEKT_STRUCTS_H

typedef struct{
    unsigned int tag :5;
    unsigned int monat :4;
    unsigned int jahr :7;
    unsigned int stunde :5;
    unsigned int minute :6;
    char *user;
    char nachricht[1000];
} Nachricht;

typedef struct{
    char *name;
    Nachricht *nachrichten;
    unsigned int nachrichten_len;
    unsigned int average_words;
} User;

#endif //INFORMATIK_PROJEKT_STRUCTS_H
