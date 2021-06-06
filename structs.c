#include "include/structs.h"


Option_tree *create_option(wchar_t *opt, void (*function)(), Option_tree *parent, int n_child, int index,int settings) {
    Option_tree *temp = malloc(sizeof(Option_tree));
    temp->opt = opt;
    temp->n_child = n_child;
    temp->parent = parent;
    temp->function = function;
    temp->settings=settings;
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

List *insert(void *item, List *node, char type) {
    if (node == NULL) {
        node = malloc(sizeof(List));
        union uni uni;
        switch (type) {
            case 'i':
                uni.integer = *(int *) item;
                break;
            case 'c':
                uni.character = *(char *) item;
                break;;
            case 'p':
                uni.pointer = item;
            default:
                break;
        }
        node->i = uni;
        node->next = NULL;
        return node;
    }
    node->next = insert(item, node->next, type);
    return node;
}
List* free_list(List *list){
    while(list!=NULL){
        free(list);
        list=list->next;
    }
    return NULL;
}

List *pop(List *node) {
    if (node->next == NULL) {
        free(node);
        return NULL;
    } else if (node->next->next == NULL) {
        free(node->next);
        node->next = NULL;
        return node;
    }
    node->next = pop(node->next);
    return node;
}

int get_list_length(List *list) {
    int ret = 0;
    List *temp = list;
    for (ret = 0; temp != NULL; ret++)
        temp = temp->next;
    return ret;
}

char *get_string_from_list(List *list_string) {
    int i, n = get_list_length(list_string);
    char *ret_string = malloc((n + 1) * sizeof(char));
    List *temp = list_string;
    for (i = 0; i < n; i++) {
        ret_string[i] = temp->i.character;
        temp = temp->next;
    }
    ret_string[i] = 0;
    return ret_string;
}

List *insert_offset(int *offset, List *node, int word, int max_word) {
    if (node == NULL) {
        node = malloc(sizeof(List));
        node->next = NULL;
        node->i.pointer = NULL;
    }
    if (word == max_word) {
        List *temp = (List *) node->i.pointer;
        temp = insert(offset, temp, 'i');
        node->i.pointer = temp;
        return node;
    }
    node->next = insert_offset(offset, node->next, word + 1, max_word);
    return node;
}

Tree *insert_to_tree(word_list *message, Tree *node, Tree *parent, int n_word) {
    if (node == NULL) {
        if (n_word == 0) {
            node = malloc(sizeof(Tree));
            List *offsets = NULL;
            offsets = insert(&message->offset, offsets, 'i');
            node->offsets = NULL;
            node->offsets = insert(offsets, node->offsets, 'p');
            node->message = message;
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
            return node;
        } else
            return NULL;
    }
    if (message->number_message == node->message->number_message) {
        node->offsets = insert_offset(&message->offset, node->offsets, 0, n_word);
        return node;
    } else if (message->number_message < node->message->number_message)
        node->left = insert_to_tree(message, node->left, node, n_word);
    else
        node->right = insert_to_tree(message, node->right, node, n_word);
    return node;
}

Tree *get_min_right(Tree *node) {
    if (node->left == NULL)
        return node;
    return get_min_right(node->left);
}

Tree *get_next_item(Tree *node) {
    if (node->right != NULL) {
        return get_min_right(node->right);
    } else {
        Tree *temp = node->parent;
        while (temp->message->number_message < node->message->number_message) {
            if (temp->parent == NULL)
                return NULL;
            else
                temp = temp->parent;
        }
        return temp;
    }
}

Tree *get_max_left(Tree *node) {
    if (node->right == NULL)
        return node;
    return get_max_left(node->right);
}

Tree *get_previous_item(Tree *node) {
    if (node->left != NULL) {
        return get_max_left(node->left);
    } else {
        Tree *temp = node->parent;
        while (temp->message->number_message > node->message->number_message) {
            if (temp->parent == NULL)
                return NULL;
            else
                temp = temp->parent;
        }
        return temp;
    }
}

Tree *delete_node(Tree *node) {
    if (node == NULL)
        return NULL;
    Tree *temp;
    if (node->left == NULL) {
        temp = node->right;
        free(node);
        return temp;
    }
    else if (node->right == NULL) {
        temp =  node->left;
        free(node);
        return temp;
    }
    else {
        temp = get_min_right(node->right);
        node->offsets = temp->offsets;
        node->message = temp->message;
        node->right = delete_node(temp);
    }
    return node;
}

Tree *update_tree(Tree *node, int words) {
    if (node == NULL)
        return node;
    node->left = update_tree(node->left, words);
    while (node != NULL && get_list_length(node->offsets) < words)
        node = delete_node(node);
    if (node != NULL)
        node->right = update_tree(node->right, words);
    return node;
}