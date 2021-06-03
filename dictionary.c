#include "include/dictionary.h"


void dictionary_main(char sort) {
    static bool stat_reverse = 0;
    static char sort_1 = 'A';
    char buffer[50];
    if (sort == 'r') {
        stat_reverse = !stat_reverse;
    } else if (sort != 0) {
        sort_1 = sort;
    }

    init_picture_buffer();

    switch (sort_1) {
        case 'A':
            sprintf(buffer, "Alphabetisch Sortiert - Richtung: %s\n\n",
                    stat_reverse == 0 ? "aufsteigend" : "absteigend");
            break;
        case 'a':
            sprintf(buffer, "Nach Anzahl Sortiert - Richtung: %s\n\n",
                    stat_reverse == 0 ? "aufsteigend" : "absteigend");
            break;
        case 'l':
            sprintf(buffer, "Nach Laenge Sortiert - Richtung: %s\n\n",
                    stat_reverse == 0 ? "aufsteigend" : "absteigend");
            break;
    }
    print_to_buffer(buffer, 0, 0);
    if (sort_1 == 'a' || sort_1 == 'l') {
        global_first_word = rearange_tree(NULL, global_first_word, sort_1);
        print_dictionary(global_first_word, stat_reverse);
        global_first_word = rearange_tree(NULL, global_first_word, 'A');
    } else {
        print_dictionary(global_first_word, stat_reverse);
    }
}

void dictionary_select() {
    global_arrow_keys = 's';
    clear_screen();
    draw_picture_buffer();

    global_arrow_keys = 0;
}

int relative_word_count(Dictionary *ptr) {
    int ret = 0;
    if (ptr == NULL) return 0;
    ret += 1;
    ret += relative_word_count(ptr->left);
    ret += relative_word_count(ptr->right);
    return ret;
}

int find_longest_word(int longest, Dictionary *ptr) {
    if (ptr == NULL) return longest;

    if (longest < ptr->length_word) {
        longest = ptr->length_word;
    }
    longest = find_longest_word(longest, ptr->left);
    if (longest < ptr->length_word) {
        longest = ptr->length_word;
    }
    longest = find_longest_word(longest, ptr->right);
    if (longest < ptr->length_word) {
        longest = ptr->length_word;
    }
    return longest;
}

int find_most_word(int most, Dictionary *ptr) {
    if (ptr == NULL) return most;

    if (most < ptr->amount) {
        most = ptr->amount;
    }
    most = find_longest_word(most, ptr->left);
    if (most < ptr->amount) {
        most = ptr->amount;
    }
    most = find_longest_word(most, ptr->right);
    if (most < ptr->amount) {
        most = ptr->amount;
    }
    return most;
}

Dictionary *rearange_tree(Dictionary *new_dict, Dictionary *dict, char type) {
    if (dict == NULL)return new_dict;
    new_dict = rearange_tree(new_dict, dict->left, type);
    new_dict = rearange_tree(new_dict, dict->right, type);
    new_dict = rearange_word(new_dict, dict, type);
    return new_dict;
}

Dictionary *rearange_word(Dictionary *new_dict, Dictionary *dict, char type) {
    if (new_dict == NULL) {
         new_dict = dict;
         new_dict->left = NULL;
         new_dict->right = NULL;
         new_dict->level = 1;
         return new_dict;
     } else {
         switch(type) {
             case 'A':
              if (strncmp(dict->words->begin_message + dict->words->offset, new_dict->words->begin_message + new_dict->words->offset,(dict->length_word < new_dict->length_word) ? dict->length_word: new_dict->length_word) < 0) {
                  new_dict->left = rearange_word(new_dict->left,dict,type);
              }
             else if (strncmp(dict->words->begin_message + dict->words->offset, new_dict->words->begin_message + new_dict->words->offset,(dict->length_word < new_dict->length_word) ? dict->length_word : new_dict->length_word) >0) {
                  new_dict->right = rearange_word(new_dict->right,dict,type);
              }
             break;
             case 'l':
                 if (dict->length_word<new_dict->length_word) {
                     new_dict->left = rearange_word(new_dict->left,dict,type);
                 }
                 else{
                     new_dict->right = rearange_word(new_dict->right,dict,type);
                 }
                 break;
             case 'a':
                 if (dict->amount<new_dict->amount) {
                     new_dict->left = rearange_word(new_dict->left,dict,type);
                 }
                 else{
                     new_dict->right = rearange_word(new_dict->right,dict,type);
                 }
                 break;
         }
     }
     new_dict->level =  max_height(height(new_dict->left), height(new_dict->right)) + 1;
     int balance = get_balanced(new_dict);

     switch(type) {
         case 'A':
             if (balance > 1 && strncmp(new_dict->words->begin_message + new_dict->words->offset,new_dict->left->words->begin_message + new_dict->left->words->offset,(new_dict->length_word < new_dict->left->length_word)? new_dict->length_word : new_dict->left->length_word) <= 0) return right_rotate(new_dict);
             if (balance < -1 && strncmp(new_dict->words->begin_message + new_dict->words->offset,new_dict->right->words->begin_message + new_dict->right->words->offset,(new_dict->length_word < new_dict->right->length_word)? new_dict->length_word : new_dict->right->length_word) >= 0) return left_rotate(new_dict);
             if (balance > 1 && strncmp(new_dict->words->begin_message + new_dict->words->offset,new_dict->left->words->begin_message + new_dict->left->words->offset,(new_dict->length_word < new_dict->left->length_word)? new_dict->length_word : new_dict->left->length_word) >= 0) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  strncmp(new_dict->words->begin_message + new_dict->words->offset,new_dict->right->words->begin_message + new_dict->right->words->offset,(new_dict->length_word < new_dict->right->length_word)? new_dict->length_word : new_dict->right->length_word) <= 0) {
                 new_dict->right = right_rotate(new_dict->right);
                 return left_rotate(new_dict);
             }
             break;
         case 'l':
             if (balance > 1 && new_dict->length_word < new_dict->left->length_word) return right_rotate(new_dict);
             if (balance < -1 && new_dict->length_word > new_dict->right->length_word) return left_rotate(new_dict);
             if (balance > 1 && new_dict->length_word > new_dict->left->length_word) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  new_dict->length_word < new_dict->right->length_word) {
                 new_dict->right = right_rotate(new_dict->right);
                 return left_rotate(new_dict);
             }
             break;
         case 'a':
             if (balance > 1 && new_dict->amount < new_dict->left->amount) return right_rotate(new_dict);
             if (balance < -1 && new_dict->amount>new_dict->right->amount) return left_rotate(new_dict);
             if (balance > 1 && new_dict->amount > new_dict->left->amount) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  new_dict->amount<new_dict->right->amount) {
                 new_dict->right = right_rotate(new_dict->right);
                 return left_rotate(new_dict);
             }
             break;
     }
    return new_dict;
}


int get_balanced(Dictionary *temp) {
    if (temp == NULL) return 0;
    else return height(temp->left) - height(temp->right);
}

void *create_dictionary() {
    global_first_word = NULL;
    int length, offset, message_count = 0;
    Message *ptr = global_first_message;
    while (ptr->next != NULL) {
        if ((strcmp(ptr->message, "<medien ausgeschlossen>\n")) == 0) {
            ptr = ptr->next;
            continue;
        }
        offset = 0;
        while (ptr->message[offset] != '\0') {
            length = 0;
            while ((check_char(*(ptr->message + offset + length))) != 0) length++;
            if (length == 0) offset++;
            else {
                global_first_word = insert_word(ptr->message, offset, length, global_first_word,message_count);
                offset += length;
            }
        }
        message_count ++;
        ptr = ptr->next;
    }
    update_height(global_first_word, 1);
}

void update_height(Dictionary *temp, int level) {
    if (temp == NULL) return;
    temp->level = level;
    update_height(temp->left, level + 1);
    update_height(temp->right, level + 1);
}

int check_char(char c) {
    char check[27] = {' ','.',',',':','!','?','\n','\0','<','>','|','/','"',';','(',')','*','=','[',']','^','{','}','\\','`','\t','\1'};
    for(int i = 0; i < 27; i ++){
        if (c == check[i]) return 0;
    }
    return 1;
}

Dictionary *insert_word(char *ptr, int offset, int length, Dictionary *temp, int message_number) {
    if (temp == NULL) {
        temp = (Dictionary *) malloc(sizeof(Dictionary));
        word_list *new;
        if ((new = (word_list *) malloc(sizeof(word_list))) == NULL) perror("Malloc Fail");
        temp->left = NULL;
        temp->right = NULL;
        temp->amount = 1;
        new->begin_message = ptr;
        new->offset = offset;
        new->number_message = message_number;
        new->next = NULL;
        temp->words = new;
        temp->length_word = length;
        temp->level = 1;
        return temp;
    } else {
        if (length == temp->length_word &&
            strncmp(ptr + offset, temp->words->begin_message + temp->words->offset, length) == 0) {
            word_list *add = temp->words;
            while (add->next != NULL) add = add->next;
            if ((add->next = (word_list *) malloc(sizeof(word_list))) == NULL) perror("Malloc Fail");
            add->next->offset = offset;
            add->next->number_message = message_number;
            add->next->begin_message = ptr;
            add->next->next = NULL;
            temp->amount++;
            return temp;
        } else if (strncmp(ptr + offset, temp->words->begin_message + temp->words->offset,
                           (length > temp->length_word) ? length : temp->length_word) < 0)
            temp->left = insert_word(ptr, offset, length, temp->left,message_number);
        else if (strncmp(ptr + offset, temp->words->begin_message + temp->words->offset,
                         (length > temp->length_word) ? length : temp->length_word) > 0)
            temp->right = insert_word(ptr, offset, length, temp->right,message_number);
    }

    temp->level = max_height(height(temp->left), height(temp->right)) + 1;
    int balance = get_balanced(temp);

    if (balance > 1 && strncmp(temp->words->begin_message + temp->words->offset,
                               temp->left->words->begin_message + temp->left->words->offset,
                               (temp->length_word < temp->left->length_word) ? temp->length_word
                                                                             : temp->left->length_word) <= 0)
        return right_rotate(temp);

    if (balance < -1 && strncmp(temp->words->begin_message + temp->words->offset,
                                temp->right->words->begin_message + temp->right->words->offset,
                                (temp->length_word < temp->right->length_word) ? temp->length_word
                                                                               : temp->right->length_word) >= 0)
        return left_rotate(temp);

    if (balance > 1 && strncmp(temp->words->begin_message + temp->words->offset,
                               temp->left->words->begin_message + temp->left->words->offset,
                               (temp->length_word < temp->left->length_word) ? temp->length_word
                                                                             : temp->left->length_word) >= 0) {
        temp->left = left_rotate(temp->left);
        return right_rotate(temp);
    }

    if (balance < -1 && strncmp(temp->words->begin_message + temp->words->offset,
                                temp->right->words->begin_message + temp->right->words->offset,
                                (temp->length_word < temp->right->length_word) ? temp->length_word
                                                                               : temp->right->length_word) <= 0) {
        temp->right = right_rotate(temp->right);
        return left_rotate(temp);
    }
    return temp;
}

void print_dictionary(Dictionary *ptr, bool reverse) {
    char buffer[200];
    char buffer2[200];
    if (ptr == NULL) return;
    if(reverse){
        print_dictionary(ptr->right,reverse);
    }else{
        print_dictionary(ptr->left,reverse);
    }
    if(ptr->length_word>x_size-10){
        strncpy(buffer, ptr->words->begin_message + ptr->words->offset, x_size-10);
        strcpy(&buffer[x_size-10],"..");
        buffer[x_size-8]=0;
    }else{
        strncpy(buffer, ptr->words->begin_message + ptr->words->offset, ptr->length_word);
        buffer[ptr->length_word] = '\0';
    }
    sprintf(buffer2,"%s %d\n",buffer,ptr->amount);
    print_to_buffer(buffer2,-1,-1);
    if(reverse){
        print_dictionary(ptr->left,reverse);
    }else{
        print_dictionary(ptr->right,reverse);
    }
}

int height(Dictionary *temp) {
    if (temp == NULL) return 0;
    else return temp->level;
}

int max_height(int left, int right) {
    if (left > right) return left;
    else return right;
}

Dictionary *left_rotate(Dictionary *temp) {
    if (temp->right == NULL) return temp;
    Dictionary *x = temp->right;
    Dictionary *y = temp->right->left;
    x->left = temp;
    temp->right = y;
    temp->level = max_height(height(temp->left), height(temp->right)) + 1;
    x->level = max_height(height(x->left), height(x->right)) + 1;
    return x;
}

Dictionary *right_rotate(Dictionary *temp) {
    if (temp->left == NULL) return temp;
    Dictionary *x = temp->left;
    Dictionary *y = temp->left->right;
    x->right = temp;
    temp->left = y;
    temp->level = max_height(height(temp->left), height(temp->right)) + 1;
    x->level = max_height(height(x->left), height(x->right)) + 1;
    return x;
}