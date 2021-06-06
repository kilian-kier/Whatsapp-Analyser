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
    Message *current_message;
    int offset;
    int number_message;
} word_list;

typedef struct Dictionary {
    struct Dictionary *left;
    struct Dictionary *right;
    word_list *words;
    int amount;
    int length_word;
    int level;
    int position;
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

typedef struct Settings {
    Color fontcolor;
    Color barcolor;
    Color menucolor;
    Color background;
    Color highlight_font;
    Color highlight_back;
    int top_n;
    int empty_lines;
    int ram_delay;
} Settings;

union uni {
    int integer;
    char character;
    void *pointer;
    Dictionary*dict;
};

typedef struct List {
    struct List *next;
    union uni i;
} List;

typedef struct Message_list {
    word_list *message;
    List *offsets;
} Message_list;

typedef struct Tree {
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
    word_list *message;
    List *offsets;
} Tree;

typedef struct Message_tree {
    List *words;
    Tree *messages;
} Message_tree;

#include "global.h"
#include "analyser.h"

Option_tree *create_option(wchar_t *opt, void (*function)(), Option_tree *parent, int n_child, int index);

Day_count *create_day_count(unsigned int day, unsigned int month, unsigned int year, unsigned int n);

List *insert(void *item, List *node, char type);
List *pop(List *node);
int get_list_length(List *list);
char *get_string_from_list(List *list_string);
List * insert_offset(int *offset, List *node, int word, int max_word);
Tree *insert_to_tree(word_list *message, Tree *node, Tree *parent, int n_word);
Tree *get_min_right(Tree *node);
Tree *get_next_item(Tree *node);
Tree *get_max_left(Tree *node);
Tree *get_previous_item(Tree *node);
Tree *delete_node(Tree *node);
Tree *update_tree(Tree *node, int words);

void free_list(List *list);

#endif //STRUCTS_H
