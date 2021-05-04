#include "structs.h"

Nachricht *get_nachricht(int index) {
    Nachricht *ptr = first_nachricht;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

User *get_user(int index) {
    User *ptr = first_user;
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
    Nachricht *temp = first_nachricht;
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