#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"
#include "output.h"

void free_messages(Message *ptr);

void free_users(User *ptr);

void free_dictionary(Dictionary *ptr);

void free_tree(Tree *node);

void free_memory();

List *free_list(List *list);

void memory_thread();

#endif //MEMORY_H
