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

    int max_amount=floor(log10(find_most_word(0,global_first_word)))+1;

    print_to_buffer(buffer, 0, 0, global_settings.menucolor, global_settings.background);
    print_to_buffer("Anzahl: Wort\n", -1, -1, global_settings.menucolor, global_settings.background);
    if (sort_1 == 'a' || sort_1 == 'l') {
        global_first_word = rearange_tree(NULL, global_first_word, sort_1);
        print_dictionary(global_first_word, stat_reverse,max_amount);
        global_first_word = rearange_tree(NULL, global_first_word, 'A');
    } else {
        print_dictionary(global_first_word, stat_reverse,max_amount);
    }
}
void dictionary_select(){
    char buffer[100];
    char input=0;
    Dictionary*ret=NULL;
    do{
        clear_screen();
        init_picture_buffer();
        dictionary_main(0);
        draw_picture_buffer();
        print_banner();
        foreground_color(global_settings.menucolor);

        ret=get_string_tree(buffer,100,(char*)global_first_word);
        if(ret==NULL){
            global_input_buffer='';
            return;
        }
        print_word_stats(ret);
        do {
            input = (char)global_input_buffer;
            Sleep(sync_delay/2);
        } while (input!='' && input !=10 && input !=13 && input!='n');
        if(input=='n'){
            //deinefunktion
        }
    }while(true);
}
void print_word_stats(Dictionary*dict){
    clear_screen();
    init_picture_buffer();
    print_banner();
    char string[x_size];
    char temp[x_size];

    sprintf(string,"Wort: %.*s\n",dict->length_word<x_size-7?dict->length_word:x_size-7,dict->words->current_message->message+dict->words->offset);
    print_to_buffer(string,0,0,global_settings.menucolor,global_settings.background);
    sprintf(string,"Laenge: %d\n",dict->length_word);
    print_to_buffer(string,-1,-1,global_settings.menucolor,global_settings.background);
    sprintf(string,"Anzahl der Vorkommnisse: %d\n",dict->amount);
    print_to_buffer(string,-1,-1,global_settings.menucolor,global_settings.background);
    print_to_buffer("\nDas Wort kommt in folgenden Nachrichten vor (""n"" zeigt Nachrichten im Kontext):\n\n",-1,-1,global_settings.highlight_font,global_settings.background);

    word_list* words=dict->words;
    do{
        sprintf(temp, "%d.%d.%d, %02d:%02d - %s: %.*s", (int) words->current_message->day, (int) words->current_message->month,
                (int) words->current_message->year,
                (int) words->current_message->hour, (int) words->current_message->minute, words->current_message->user, x_size - 15,
                words->current_message->message);
        print_to_buffer(temp,-1,-1,global_settings.fontcolor,global_settings.background);
        words=words->next;
    }while(words!=NULL);

    draw_picture_buffer();
    global_input_buffer=0;
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

    longest = find_longest_word(longest, ptr->left);
    if (longest < ptr->length_word) {
        longest = ptr->length_word;
    }
    longest = find_longest_word(longest, ptr->right);
    return longest;
}

int find_most_word(int most, Dictionary *ptr) {
    if (ptr == NULL) return most;

    most = find_most_word(most, ptr->left);
    if (most < ptr->amount) {
        most = ptr->amount;
    }
    most = find_most_word(most, ptr->right);
    return most;
}

Dictionary *get_string_tree(char *string, int size, char *pointer) {
    global_arrow_keys = 's';
    int max_amount=floor(log10(find_most_word(0,global_first_word)))+1;
    int i = 0, j = 0;
    global_input_buffer = 0;
    global_send_input = false;

    List *suggestions = NULL;
    List *temp_suggestions = NULL;
    Dictionary *last_suggestion = NULL;
    bool changed_string = true;

    printf("   ");
    string[0]=0;
    while (global_input_buffer != 13 && global_input_buffer != '\n' || i==0) {
        if (j % 66 < 33) {
            cursor_blink(true, i);
        } else {
            cursor_blink(false, i);
        }

        if (global_send_input == true) {
            if (global_input_buffer < 256) {
                switch (global_input_buffer) {
                    case 10:
                    case 13:
                        break;
                    case 8:
                        if (i > 0) {
                            printf(" ");
                            delete_n_char(2);
                            i--;
                            string[i] = 0;
                            global_send_input = false;
                            changed_string=true;
                        }
                        break;
                    case '':
                        free_list(suggestions);
                        global_arrow_keys = 0;
                        return NULL;
                    case 9:
                        if(string[0]!=0) {
                            if (pointer != NULL) {
                                if (changed_string) {
                                    suggestions=free_list(suggestions);
                                    List tmp;
                                    tmp.next = NULL;
                                    get_suggestions_from_dict_tree(global_first_word, &tmp, string);
                                    suggestions = tmp.next;
                                    temp_suggestions = suggestions;
                                    changed_string = false;
                                }
                                if (suggestions != NULL) {
                                    if (temp_suggestions == NULL) {
                                        temp_suggestions = suggestions;
                                    }
                                    strncpy(string, temp_suggestions->i.dict->words->current_message->message +
                                                    temp_suggestions->i.dict->words->offset,
                                            temp_suggestions->i.dict->length_word);
                                    string[temp_suggestions->i.dict->length_word] = 0;
                                    foreground_color(global_settings.menucolor);
                                    printf(" ");
                                    delete_n_char(i + 1);
                                    i = strlen(string);
                                    printf("%s", string);
                                }
                                global_send_input = false;
                            }
                        }
                        break;
                    default:
                        string[i] = global_input_buffer;
                        printf("%c", string[i]);
                        global_send_input = false;
                        if (i < size) {
                            i++;
                            string[i] = 0;
                        } else {
                            break;
                        }
                        changed_string = true;
                        break;
                }
                if(changed_string==true) {
                    if (string[0] != 0) {
                        Dictionary *suggestion = find_similar_in_tree(global_first_word, string);
                        if (suggestion != NULL && suggestion != last_suggestion) {
                            global_current_pos = suggestion->position;
                            if (last_suggestion != NULL) {
                                change_color(last_suggestion->length_word+max_amount+2, 1, max_amount+2, last_suggestion->position/(global_settings.empty_lines + 1),
                                             global_settings.fontcolor, global_settings.background);
                            }
                            change_color(suggestion->length_word, 1, max_amount+2, suggestion->position/(global_settings.empty_lines + 1),
                                         global_settings.highlight_font, global_settings.highlight_back);
                            draw_picture_buffer();
                            last_suggestion = suggestion;
                            foreground_color(global_settings.menucolor);
                        }
                    } else {
                        global_current_pos = 0;
                        if (last_suggestion != NULL) {
                            change_color(last_suggestion->length_word, 1, max_amount+2, last_suggestion->position/(global_settings.empty_lines + 1),
                                         global_settings.fontcolor, global_settings.background);
                            draw_picture_buffer();
                            foreground_color(global_settings.menucolor);
                            last_suggestion=NULL;
                        }
                    }
                }else if(temp_suggestions!=NULL){
                        global_current_pos = temp_suggestions->i.dict->position;

                        if (last_suggestion != NULL) {
                            change_color(last_suggestion->length_word, 1, max_amount+2, last_suggestion->position/(global_settings.empty_lines + 1),
                                         global_settings.fontcolor, global_settings.background);
                        }
                        change_color(temp_suggestions->i.dict->length_word, 1, max_amount+2, temp_suggestions->i.dict->position/(global_settings.empty_lines + 1),
                                     global_settings.highlight_font, global_settings.highlight_back);
                        draw_picture_buffer();
                        foreground_color(global_settings.menucolor);

                        last_suggestion=temp_suggestions->i.dict;
                        temp_suggestions = temp_suggestions->next;
                    }
            }else {
                global_input_buffer-=256;
                switch(global_input_buffer){
                    case key_right:
                            if (global_current_pos < global_page_count * y_size - y_size) {
                                global_current_pos++;
                                draw_picture_buffer();
                            }
                        break;
                    case key_left:
                            if (global_current_pos > 0) {
                                global_current_pos--;
                                draw_picture_buffer();
                            }
                            break;
                    case key_up:
                            if (global_current_pos - y_size > 0) {
                                global_current_pos -= y_size;
                                draw_picture_buffer();
                            }
                        break;
                    case key_down:
                            if (global_current_pos + y_size < global_page_count * y_size - y_size + 1) {
                                global_current_pos += y_size;
                                draw_picture_buffer();
                            }
                        break;
                }
                foreground_color(global_settings.menucolor);
                global_input_buffer=0;
                global_send_input=false;
            }
        }
        j++;
        Sleep(sync_delay / 2);
    }
    suggestions=free_list(suggestions);

    string[i] = 0;
    global_arrow_keys = 0;
    return last_suggestion;
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
              if (strncmp(dict->words->current_message->message + dict->words->offset, new_dict->words->current_message->message + new_dict->words->offset,(dict->length_word < new_dict->length_word) ? dict->length_word: new_dict->length_word) < 0) {
                  new_dict->left = rearange_word(new_dict->left,dict,type);
              }
             else {
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
             if (balance > 1 && strncmp(new_dict->words->current_message->message + new_dict->words->offset,new_dict->left->words->current_message->message + new_dict->left->words->offset,(new_dict->length_word < new_dict->left->length_word)? new_dict->length_word : new_dict->left->length_word) <= 0) return right_rotate(new_dict);
             if (balance < -1 && strncmp(new_dict->words->current_message->message + new_dict->words->offset,new_dict->right->words->current_message->message + new_dict->right->words->offset,(new_dict->length_word < new_dict->right->length_word)? new_dict->length_word : new_dict->right->length_word) >= 0) return left_rotate(new_dict);
             if (balance > 1 && strncmp(new_dict->words->current_message->message + new_dict->words->offset,new_dict->left->words->current_message->message + new_dict->left->words->offset,(new_dict->length_word < new_dict->left->length_word)? new_dict->length_word : new_dict->left->length_word) >= 0) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  strncmp(new_dict->words->current_message->message + new_dict->words->offset,new_dict->right->words->current_message->message + new_dict->right->words->offset,(new_dict->length_word < new_dict->right->length_word)? new_dict->length_word : new_dict->right->length_word) <= 0) {
                 new_dict->right = right_rotate(new_dict->right);
                 return left_rotate(new_dict);
             }
             break;
         case 'l':
             if (balance > 1 && new_dict->length_word <= new_dict->left->length_word) return right_rotate(new_dict);
             if (balance < -1 && new_dict->length_word >= new_dict->right->length_word) return left_rotate(new_dict);
             if (balance > 1 && new_dict->length_word >= new_dict->left->length_word) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  new_dict->length_word <= new_dict->right->length_word) {
                 new_dict->right = right_rotate(new_dict->right);
                 return left_rotate(new_dict);
             }
             break;
         case 'a':
             if (balance > 1 && new_dict->amount <= new_dict->left->amount) return right_rotate(new_dict);
             if (balance < -1 && new_dict->amount>=new_dict->right->amount) return left_rotate(new_dict);
             if (balance > 1 && new_dict->amount >= new_dict->left->amount) {
                 new_dict->left = left_rotate(new_dict->left);
                 return right_rotate(new_dict);
             }
             if (balance < -1 &&  new_dict->amount<=new_dict->right->amount) {
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
            message_count ++;
            ptr = ptr->next;
            continue;
        }
        offset = 0;
        while (ptr->message[offset] != '\0') {
            length = 0;
            while ((check_char(*(ptr->message + offset + length))) != 0) length++;
            if (length == 0) offset++;
            else {
                global_first_word = insert_word(ptr, offset, length, global_first_word,message_count);
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

Dictionary *insert_word(Message *ptr, int offset, int length, Dictionary *temp, int message_number) {
    if (temp == NULL) {
        temp = (Dictionary *) malloc(sizeof(Dictionary));
        word_list *new;
        if ((new = (word_list *) malloc(sizeof(word_list))) == NULL) perror("Malloc Fail");
        temp->left = NULL;
        temp->right = NULL;
        temp->amount = 1;
        //new->current_message->message = ptr->message;
        new->offset = offset;
        new->number_message = message_number;
        new->current_message = ptr;
        new->next = NULL;
        temp->words = new;
        temp->length_word = length;
        temp->level = 1;
        return temp;
    } else {
        if (length == temp->length_word &&
            strncmp(ptr->message + offset, temp->words->current_message->message + temp->words->offset, length) == 0) {
            word_list *add = temp->words;
            while (add->next != NULL) add = add->next;
            if ((add->next = (word_list *) malloc(sizeof(word_list))) == NULL) perror("Malloc Fail");
            add->next->offset = offset;
            add->next->number_message = message_number;
            //add->next->current_message->message = ptr->message;
            add->next->current_message = ptr;
            add->next->next = NULL;
            temp->amount++;
            return temp;
        } else if (strncmp(ptr->message + offset, temp->words->current_message->message + temp->words->offset,
                           (length > temp->length_word) ? length : temp->length_word) < 0)
            temp->left = insert_word(ptr, offset, length, temp->left,message_number);
        else if (strncmp(ptr->message + offset, temp->words->current_message->message + temp->words->offset,
                         (length > temp->length_word) ? length : temp->length_word) > 0)
            temp->right = insert_word(ptr, offset, length, temp->right,message_number);
    }

    temp->level = max_height(height(temp->left), height(temp->right)) + 1;
    int balance = get_balanced(temp);

    if (balance > 1 && strncmp(temp->words->current_message->message + temp->words->offset,
                               temp->left->words->current_message->message + temp->left->words->offset,
                               (temp->length_word < temp->left->length_word) ? temp->length_word
                                                                             : temp->left->length_word) <= 0)
        return right_rotate(temp);

    if (balance < -1 && strncmp(temp->words->current_message->message + temp->words->offset,
                                temp->right->words->current_message->message + temp->right->words->offset,
                                (temp->length_word < temp->right->length_word) ? temp->length_word
                                                                               : temp->right->length_word) >= 0)
        return left_rotate(temp);

    if (balance > 1 && strncmp(temp->words->current_message->message + temp->words->offset,
                               temp->left->words->current_message->message + temp->left->words->offset,
                               (temp->length_word < temp->left->length_word) ? temp->length_word
                                                                             : temp->left->length_word) >= 0) {
        temp->left = left_rotate(temp->left);
        return right_rotate(temp);
    }

    if (balance < -1 && strncmp(temp->words->current_message->message + temp->words->offset,
                                temp->right->words->current_message->message + temp->right->words->offset,
                                (temp->length_word < temp->right->length_word) ? temp->length_word
                                                                               : temp->right->length_word) <= 0) {
        temp->right = right_rotate(temp->right);
        return left_rotate(temp);
    }
    return temp;
}

void print_dictionary(Dictionary *ptr, bool reverse,int max_amount) {
    char buffer[x_size+1];
    char buffer2[max_amount+1];
    if (ptr == NULL) return;
    if(reverse){
        print_dictionary(ptr->right,reverse,max_amount);
    }else{
        print_dictionary(ptr->left,reverse,max_amount);
    }
    if(ptr->length_word>x_size-(max_amount+7)){
        strncpy(buffer+max_amount+7, ptr->words->current_message->message + ptr->words->offset, x_size-(max_amount+7));
        strcpy(&buffer[x_size-(max_amount+5)],"...");
        buffer[x_size-1]=0;
        buffer[x_size-2]='\n';
    }else{
        strncpy(buffer+max_amount+2, ptr->words->current_message->message + ptr->words->offset, ptr->length_word);
        buffer[ptr->length_word+max_amount+3] = '\0';
        buffer[ptr->length_word+max_amount+2]='\n';
    }
    itoa(ptr->amount,buffer2,10);
    int len=strlen(buffer2);
    for(int i=0;i<max_amount;i++){
        if(i<len){
            buffer[i]=buffer2[i];
        }else{
            buffer[i]=' ';
        }
    }
    buffer[max_amount]=':';
    buffer[max_amount+1]=' ';

    ptr->position = print_to_buffer(buffer, -1, -1, global_settings.fontcolor, global_settings.background);
    if(reverse){
        print_dictionary(ptr->left,reverse,max_amount);
    }else{
        print_dictionary(ptr->right,reverse,max_amount);
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

Tree *find_word(Dictionary *tree_node, const char *string, Tree *ret, int n_word) {
    if (tree_node == NULL)
        return ret;
    ret = find_word(tree_node->left, string, ret, n_word);
    if (string[0] == tree_node->words->current_message->message[tree_node->words->offset])
        if (check_word(tree_node, string) == true) {
            word_list *temp = tree_node->words;
            while (temp != NULL) {
                ret = insert_to_tree(temp, ret, NULL, n_word);
                temp = temp->next;
            }
        }
    ret = find_word(tree_node->right, string, ret, n_word);
    return ret;
}

bool check_word(Dictionary *tree_node, const char *string) {
    int x;
    if (tree_node->length_word >= strlen(string)) {
        char *word = malloc(tree_node->length_word);
        strncpy(word, tree_node->words->current_message->message + tree_node->words->offset, tree_node->length_word);
        x = strncmp(string, tree_node->words->current_message->message + tree_node->words->offset, strlen(string));
    } else
        x = 1;
    if (x == 0)
        return true;
    else
        return false;
}
Dictionary* find_similar_in_tree(Dictionary*ptr, char*search){

    if(ptr==NULL) return NULL;

    int comparison=comparison=strncmp(search,ptr->words->current_message->message+ptr->words->offset,strlen(search));
    if(comparison==0){
        Dictionary *temp= find_similar_in_tree(ptr->left, search);
        if(temp==NULL){
            return ptr;
        }
        return temp;
    }else if(comparison<0){
        return find_similar_in_tree(ptr->left, search);
    }else{
        return find_similar_in_tree(ptr->right, search);
    }

}
List* get_suggestions_from_dict_tree(Dictionary*ptr, List*suggestions, char*search){
    int comparison;

    if(ptr==NULL) return suggestions;

    comparison=strncmp(search,ptr->words->current_message->message+ptr->words->offset,strlen(search));

    suggestions = get_suggestions_from_dict_tree(ptr->left, suggestions, search);

    if(comparison==0) {
        suggestions->next = malloc(sizeof(List));
        if (suggestions->next == NULL) {
            perror("malloc");
            return suggestions;
        }
        suggestions->next->next = NULL;
        suggestions->next->i.dict = ptr;
        suggestions = suggestions->next;
    }
    return get_suggestions_from_dict_tree(ptr->right, suggestions, search);
}