#ifndef STRUCTS_H
#define STRUCTS_H

#include "std_include.h"

typedef struct Message {
    struct Message *next;
    unsigned int day: 5;
    unsigned int month: 4;
    unsigned int year: 7;
    unsigned int hour: 5;
    unsigned int minute: 6;
    char *user;
    char *message;
    struct Message *nextUser;
} Message;

typedef struct User {
    struct User *next;
    char *name;
    Message *message;
    unsigned int message_len;
    double average_words;
    int weekday_arr[7];
    int hour_arr[24];
} User;

typedef struct word_list{
    struct word_list *next;
    char *begin_message;
    int offset;
} word_list;

typedef struct Dictionary {
    struct Dictionary *left;
    struct Dictionary *right;
    word_list *words;
    int amount;
    int length_word;
    int level;
} Dictionary;

typedef struct Option_tree {
    wchar_t *opt;

    void (*function)();

    struct Option_tree *parent;
    int n_child;
    struct Option_tree **children;
} Option_tree;

typedef struct Color {
    int r;
    int g;
    int b;
} Color;

typedef struct Pixel {
    wchar_t character;
    Color foreground;
    Color background;
} Pixel;

typedef struct Console_buffer {
    unsigned int n;
    Pixel **buffer;
    struct Console_buffer *next;
    struct Console_buffer *previous;
} Console_buffer;

typedef struct Day_count {
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int n;
} Day_count;
typedef struct Suggestions {
    char *string;
    struct Suggestions *next;
} Suggestions;

typedef struct Settings {
    Color fontcolor;
    Color barcolor;
    Color menucolor;
    Color background;
    int top_n;
    int empty_lines;
} Settings;

union uni {
    int integer;
    char character;
    void *pointer;
};

typedef struct List {
    struct List *next;
    union uni item;
} List;

#include "global.h"

Option_tree *create_option(wchar_t *opt, void (*function)(), Option_tree *parent, int n_child, int index);

Day_count *create_day_count(unsigned int day, unsigned int month, unsigned int year, unsigned int n);

List *insert_to_list(void *item, List *node, char type);

#endif //STRUCTS_H
