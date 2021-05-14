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
    double average_words;
    int weekday_arr[7];
    int hour_arr[24];
    struct User *previous;
} User;

typedef struct Woerterbook{
    struct Woerterbook *next;
    char *wortanfang;
    int laenge;
} Woerterbook;


typedef struct Option_tree{
    wchar_t *opt;
    void (*function)(int, char *);
    int argc;
    char *argv;
    struct Option_tree *parent;
    int n_childs;
    struct Option_tree **childs;
} Option_tree;

Nachricht *get_nachricht(int index);
User *get_user(int index);
void insert_user(User *ptr, int index);
void append_nachricht(Nachricht *ptr);
void insert_nachricht(Nachricht *ptr, int index);
void delete_nachricht(Nachricht *ptr);
Option_tree *create_option(wchar_t *opt, void (*function)(int, char *), int argc, char *argv, Option_tree *parent, int n_childs, int index);

#endif //INFORMATIK_PROJEKT_STRUCTS_H
