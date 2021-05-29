#ifndef STRUCTS_H
#define STRUCTS_H

#include "std_include.h"

typedef struct Message{
    struct Message *next;
    unsigned int day :5;
    unsigned int month :4;
    unsigned int year :7;
    unsigned int hour :5;
    unsigned int minute :6;
    char *user;
    char *message;
    struct Message *nextUser;
} Message;

typedef struct User{
    struct User *next;
    char *name;
    Message *message;
    unsigned int message_len;
    double average_words;
    int weekday_arr[7];
    int hour_arr[24];
} User;

typedef struct Dictionary{
    struct Dictionary *left;
    struct Dictionary *right;
    char *begin_word;
    int amount;
    int length_word;
    int level;
} Dictionary;

typedef struct Option_tree{
    wchar_t *opt;
    void (*function)(FILE *f);
    struct Option_tree *parent;
    int n_child;
    struct Option_tree **children;
} Option_tree;

typedef struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}Color;

typedef struct Pixel{
    char character;
    Color foreground;
    Color background;
}Pixel;

#include "global.h"

Option_tree *create_option(wchar_t *opt, void (*function)(FILE *), Option_tree *parent, int n_child, int index);

#endif //STRUCTS_H
