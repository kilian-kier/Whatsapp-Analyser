#include "structs.h"

Nachricht *get_nachricht(int index) {
    Nachricht *ptr = first;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr;
}