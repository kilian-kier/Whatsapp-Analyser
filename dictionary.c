#include "include/dictionary.h"


void dictionary_main(FILE *f){
    int words;
    int most;
    int longest;

    static FILE* loaded=NULL;
    if(f!=loaded || loaded==NULL){
        create_dictionary();
    }
    init_picture_buffer();
    print_to_buffer("",0,0,white,black);
/*
    words=relative_word_count(global_first_word);
    longest=find_longest_word(0,global_first_word);
    find_most_word();
    printf("\n\n%d %d %d\n",words,longest,most);
    Sleep(100000);*/
    print_dictionary(global_first_word);
}
int relative_word_count(Dictionary *ptr) {
    int ret=0;
    if (ptr == NULL) return 0;
    ret+=1;
    ret+= relative_word_count(ptr->left);
    ret+= relative_word_count(ptr->right);
    return ret;
}
Dictionary** find_most_word(){
    Dictionary** array=malloc(sizeof(Dictionary**)*(y_size/2));
    find_most_rec(array,y_size/2,global_first_word);
    for(int i=0;i<y_size/2;i++){
        printf("%d\n",array[0]->amount);
    }

}
void find_most_rec(Dictionary**array,int arraysize, Dictionary*ptr){
    if(ptr==NULL)return;

    for(int i=0;i<arraysize;i++){
        if(ptr->amount>array[
                i]->amount);
        shift_pointer_array((char**)array,i,arraysize);
        array[i]=ptr;
        printf("anzahl: %d\n",ptr->amount);
    }
    find_most_rec(array,arraysize,ptr->left);
    find_most_rec(array,arraysize,ptr->right);
    return;
}
void shift_pointer_array(char **array,int index, int size){
    for(int i=size;i>index;i--){
        array[size]=array[size-1];
    }
}
int find_longest_word(int longest,Dictionary*ptr) {
    if (ptr == NULL) return 0;

    longest=find_longest_word(longest,ptr->left);
    longest=find_longest_word(longest,ptr->right);
    if(longest<ptr->length_word){
        longest=ptr->length_word;

    }
    return longest;
}
int get_balanced(Dictionary * temp){
    if (temp == NULL) return 0;
    else return height(temp->left) - height(temp->right);
}
void create_dictionary() {
    gloabl_first_word = NULL;
    int length, offset;
    char *word_begin;
    Message *ptr = global_first_message;
    while (ptr->next != NULL) {
        if ((strcmp(ptr->message, "<medien ausgeschlossen>\n")) == 0) {
            ptr = ptr->next;
            continue;
        }
        offset = 0;
        while (ptr->message[offset] != '\0') {
            word_begin = ptr->message + offset;
            length = 0;
            //if(*word_begin == '<' && *(word_begin + 1) == '\\' && *(word_begin + 2) == '1' && *(word_begin + 3) == '>')word_begin += 4;
            while ((check_char(*(word_begin + length))) != 0) length++;
            if (length == 0) offset++;
            else {
                gloabl_first_word = insert_word(word_begin, length, gloabl_first_word);
                char buffer[100];
                for (int i = 0; i < 100; i++) buffer[i] = '\0';
                strncpy(buffer, word_begin, length);
                offset += length;
            }
        }
        ptr = ptr->next;
    }
    update_height(gloabl_first_word, 1);
}

void update_height(Dictionary *temp, int level){
    if (temp == NULL) return;
    temp->level = level;
    update_height(temp->left, level+1);
    update_height(temp->right, level+1);
}
int check_char(char c) {
    if (c == ' ' || c == '.' ||
        c == ',' || c == ':' ||
        c == '!' || c == '?' ||
        c == '\n' || c == '\0' ||
        c == '<' || c == '>' ||
        c == '|' || c == '/'
        || c == '"' || c == ';'
        || c == '(' || c == ')' || c == '*' || c == '=' || c == '[' || c == ']' || c == '^' || c == '{' || c == '}' ||
        c == '\\' || c == '`' || c == '\t' ||c == '\1')
        return 0;
    else return 1;
}

Dictionary *insert_word(char *word_begin, int length, Dictionary *temp) {
    if (temp == NULL) {
        temp = (Dictionary *) malloc(sizeof(Dictionary));
        temp->left = NULL;
        temp->right = NULL;
        temp->amount = 1;
        temp->begin_word = word_begin;
        temp->length_word = length;
        temp->level = 1;
        return temp;
    } else {
        if (length == temp->length_word && strncmp(word_begin, temp->begin_word, length) == 0) {
            temp->amount++;
            return temp;
        } else if (strncmp(word_begin, temp->begin_word, (length < temp->length_word)? length : temp->length_word) < 0)
            temp->left = insert_word(word_begin, length, temp->left);
        else if (strncmp(word_begin, temp->begin_word, (length < temp->length_word)? length : temp->length_word) > 0)
            temp->right = insert_word(word_begin, length, temp->right);
    }

    temp->level =  max_height(height(temp->left), height(temp->right)) + 1;
    int balance = get_balanced(temp);

    if (balance > 1 && strncmp(temp->begin_word,temp->left->begin_word,(temp->length_word < temp->left->length_word)? temp->length_word : temp->left->length_word) <= 0) return right_rotate(temp);

    if (balance < -1 && strncmp(temp->begin_word,temp->right->begin_word,(temp->length_word < temp->right->length_word)? temp->length_word : temp->right->length_word) >= 0) return left_rotate(temp);

    if (balance > 1 && strncmp(temp->begin_word,temp->left->begin_word,(temp->length_word < temp->left->length_word)? temp->length_word : temp->left->length_word) >= 0) {
        temp->left = left_rotate(temp->left);
        return right_rotate(temp);
    }

    if (balance < -1 &&  strncmp(temp->begin_word,temp->right->begin_word,(temp->length_word < temp->right->length_word)? temp->length_word : temp->right->length_word) <= 0) {
        temp->right = right_rotate(temp->right);
        return left_rotate(temp);
    }
    return temp;
}


void print_dictionary(Dictionary *ptr) {
    char buffer[200];
    char buffer2[200];
    if (ptr == NULL) return;
    print_dictionary(ptr->left);
    strncpy(buffer, ptr->begin_word, ptr->length_word);
    buffer[ptr->length_word] = '\0';
    sprintf(buffer2,"%s %d\n",buffer,ptr->amount);
    print_to_buffer(buffer2,-1,-1,white,black);
    print_dictionary(ptr->right);
}

int height(Dictionary *temp) {
    if (temp == NULL) return 0;
    else return temp->level;
}

int max_height(int left, int right){
    if (left > right) return left;
    else return right;
}

Dictionary *left_rotate(Dictionary *temp) {
    if(temp->right == NULL) return temp;
    Dictionary *x = temp->right;
    Dictionary *y = temp->right->left;
    x->left = temp;
    temp->right = y;
    temp->level = max_height(height(temp->left), height(temp->right)) +1;
    x->level = max_height(height(x->left), height(x->right)) +1;
    return x;
}

Dictionary *right_rotate(Dictionary *temp) {
    if(temp->left == NULL) return temp;
    Dictionary *x = temp->left;
    Dictionary *y = temp->left->right;
    x->right = temp;
    temp->left = y;
    temp->level = max_height(height(temp->left), height(temp->right)) +1;
    x->level = max_height(height(x->left), height(x->right)) +1;
    return x;
}