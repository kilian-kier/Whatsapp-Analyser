#ifndef INFORMATIK_PROJEKT_STRUCTS_H
#define INFORMATIK_PROJEKT_STRUCTS_H

#include "stdlib.h"
#include "global.h"

typedef struct Nachricht{
    struct Nachricht *next;
    unsigned int tag :5;
    unsigned int monat :4;
    unsigned int jahr :7;
    unsigned int stunde :5;
    unsigned int minute :6;
    char *user;
    char *nachricht;
    struct Nachricht *nextUser;
    struct Nachricht *previous;
} Nachricht;

typedef struct User{
    struct User *next;
    char *name;
    Nachricht *nachrichten;
    unsigned int nachrichten_len;
    unsigned int total_words;
    struct User *previous;
} User;

typedef struct Woerterbook{
    struct Woerterbook *next;
    char *wort;
} Woerterbook;

Nachricht *get_nachricht(int index);
User *get_user(int index);
void insert_user(User *ptr, int index);
void append_nachricht(Nachricht *ptr);
void insert_nachricht(Nachricht *ptr, int index);
void delete_nachricht(Nachricht *ptr);

#endif //INFORMATIK_PROJEKT_STRUCTS_H
