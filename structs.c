#include "include/structs.h"

Option_tree *create_option(wchar_t *opt, void (*function)(FILE *), Option_tree *parent, int n_child, int index) {
    Option_tree *temp = malloc(sizeof(Option_tree));
    temp->opt = opt;
    temp->n_child = n_child;
    temp->parent = parent;
    temp->function = function;
    temp->children = malloc(temp->n_child * sizeof(Option_tree));
    if (temp->parent != NULL)
        temp->parent->children[index] = temp;
    return temp;
}