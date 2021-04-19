#ifndef INFORMATIK_PROJEKT_STRUCTS_H
#define INFORMATIK_PROJEKT_STRUCTS_H

#include "stdlib.h"

typedef struct Nachricht{
    unsigned int tag :5;
    unsigned int monat :4;
    unsigned int jahr :7;
    unsigned int stunde :5;
    unsigned int minute :6;
    char *user;
    char *nachricht;
    struct Nachricht *nextUser;
    struct Nachricht *previous;
    struct Nachricht *next;
} Nachricht;

typedef struct User{
    char *name;
    Nachricht *nachrichten;
    unsigned int nachrichten_len;
    unsigned int average_words;
    struct User *next;
} User;

typedef struct Woerterbook{
    char *wort;
    struct Woerterbook *next;
} Woerterbook;

Nachricht *first_nachricht;
User *first_user;
Nachricht *get_nachricht(int index);
void append_nachricht(Nachricht *ptr);
void insert_nachricht(Nachricht *ptr, int index);
void delete_nachricht(Nachricht *ptr);

#endif //INFORMATIK_PROJEKT_STRUCTS_H
