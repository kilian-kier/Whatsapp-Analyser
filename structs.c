#include "include/structs.h"

Nachricht *get_nachricht(int index) {
    Nachricht *ptr = global_first_nachricht;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

User *get_user(int index) {
    User *ptr = global_first_user;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

void insert_user(User *ptr, int index) {
    User *temp = get_user(index);
    User *next = temp->next;
    temp->next = ptr;
    ptr->previous = temp;
    ptr->next = next;
}

void append_nachricht(Nachricht *ptr) {
    Nachricht *temp = global_first_nachricht;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = ptr;
    ptr->previous = temp;
    ptr->next = NULL;
}
void insert_nachricht(Nachricht *ptr, int index) {
    Nachricht *temp = get_nachricht(index);
    Nachricht *next = temp->next;
    temp->next = ptr;
    ptr->previous = temp;
    ptr->next = next;
}
void delete_nachricht(Nachricht *ptr) {
    ptr->previous->next = ptr->next;
    free(ptr);
}

Option_tree *create_option(wchar_t *opt, void (*function)(int, char *), int argc, char *argv, Option_tree *parent, int n_childs, int index) {
    Option_tree *temp = malloc(sizeof(Option_tree));
    temp->opt = opt;
    temp->n_childs = n_childs;
    temp->parent = parent;
    temp->function = function;
    temp->argc = argc;
    temp->argv = argv;
    temp->childs = malloc(temp->n_childs * sizeof(Option_tree));
    if (temp->parent != NULL)
        temp->parent->childs[index] = temp;
    return temp;
}