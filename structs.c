#include "include/structs.h"

Option_tree *create_option(wchar_t *opt, void (*function)(), Option_tree *parent, int n_child, int index) {
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

Day_count *create_day_count(unsigned int day, unsigned int month, unsigned int year, unsigned int n) {
    Day_count *ret = malloc(sizeof(Day_count));
    ret->day = day;
    ret->month = month;
    ret->year = year;
    ret->n = n;
    return ret;
}

List *insert_to_list(void *item, List *node, char type) {
    if (node == NULL) {
        node = malloc(sizeof(List));
        union uni uni;
        switch (type) {
            case 'i':
                uni.integer = *(int *)item;
                break;
            case 'c':
                uni.character = *(char *)item;
                break;;
            case 'p':
                uni.pointer = item;
            default:
                break;
        }
        node->item = uni;
        node->next = NULL;
        return node;
    }
    node->next = insert_to_list(item, node->next, type);
    return node;
}