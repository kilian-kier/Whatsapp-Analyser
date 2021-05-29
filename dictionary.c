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
        printf("%d\n",array[0]->anzahl);
    }

}
void find_most_rec(Dictionary**array,int arraysize, Dictionary*ptr){
    if(ptr==NULL)return;

    for(int i=0;i<arraysize;i++){
        if(ptr->anzahl>array[
                i]->anzahl);
        shift_pointer_array((char**)array,i,arraysize);
        array[i]=ptr;
        printf("anzahl: %d\n",ptr->anzahl);
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
    if(longest<ptr->laenge){
        longest=ptr->laenge;

    }
    return longest;
}
void create_dictionary() {
    global_first_word = NULL;
    int laenge, offset;
    char *anfang;
    Message *ptr = global_first_message->next->next->next;
    while (ptr->next != NULL) {
        if ((strcmp(ptr->message, "<medien ausgeschlossen>\n")) == 0) {
            ptr = ptr->next;
            continue;
        }
        offset = 0;
        while (ptr->message[offset] != '\0') {
            anfang = ptr->message + offset;
            laenge = 0;
            while ((check_char(*(anfang+laenge)))!= 0) laenge++;
            if (laenge == 0) offset++;
            else {
                global_first_word = insert_word(anfang, laenge, global_first_word);
                offset += laenge;
            }
        }
        ptr = ptr->next;
    }
}

int check_char(char c){
    if (c == ' ' || c == '.' ||
        c == ',' || c == ':' ||
        c == '!' || c == '?' ||
        c == '\n' || c == '\0' ||
        c == '<' || c == '>' ||
        c == '|' || c == '/'
        || c == '"' || c == ';'
        || c == '(' || c == ')' || c == '*' || c == '=' || c == '[' || c == ']' || c == '^' || c == '{' || c == '}' || c == '\\'  ) return 0;
    else return 1;
}

Dictionary *insert_word(char *anfang, int l, Dictionary *temp) {
    int h_left, h_right, balance, y;
    if (temp == NULL) {
        temp = (Dictionary *) malloc(sizeof(Dictionary));
        temp->left = NULL;
        temp->right = NULL;
        temp->anzahl = 1;
        temp->wortanfang = anfang;
        temp->laenge = l;
        temp->level = 1;
        if (global_first_word == NULL) global_first_word = temp;
        return temp;
    } else {
        if (l <= temp->laenge) y = l;
        else y = temp->laenge;
        if (l == temp->laenge && strncmp (anfang, temp->wortanfang, l) == 0) {
            temp->anzahl++;
            return temp;
        } else if (strncmp(anfang, temp->wortanfang, y) < 0) temp->left = insert_word(anfang, l, temp->left);
        else if (strncmp(anfang, temp->wortanfang, y) > 0) temp->right = insert_word(anfang, l, temp->right);
    }
    return temp;

   /* //Höhe ermitteln
    h_left = height(temp->left);
    h_right = height(temp->right);
    temp->level = (h_right < h_left) ? h_left : h_right;

    //Balance ausrechnen
    balance = h_left-h_right;

    //Überprüfen in welche richtung der Baum "verzogen" ist
    // Linker Linker Fall
    if(balance > 1 && strncmp(temp->wortanfang,temp->left->wortanfang , (temp->laenge <= temp->left->laenge)? temp->laenge : temp->left->laenge) < 0){
        return right_rotaition(temp);
    }
    // Rechter Rechter Fall
    else if(balance < -1 && strncmp(temp->wortanfang,temp->right->wortanfang, (temp->laenge <= temp->right->laenge)? temp->laenge : temp->right->laenge) > 0){
        return left_rotaition(temp);
    }
    // Linken rechten Fall
    else if (balance > 1 && strncmp(temp->wortanfang,temp->left->wortanfang, (temp->laenge <= temp->left->laenge)? temp->laenge : temp->left->laenge) > 0){
        temp->left = left_rotaition(temp);
        return right_rotaition(temp);
    }
    else if(balance < -1 && strncmp(temp->wortanfang, temp->right->wortanfang , (temp->laenge <= temp->right->laenge)? temp->laenge : temp->right->laenge) < 0){
        temp->right = right_rotaition(temp);
        return left_rotaition(temp);
    }
    else return temp;*/
}

//inorder print
void print_dictionary(Dictionary *ptr) {
    char buffer[200];
    char buffer2[200];
    if (ptr == NULL) return;
    print_dictionary(ptr->left);
    strncpy(buffer, ptr->wortanfang, ptr->laenge);
    buffer[ptr->laenge] = '\0';
    sprintf(buffer2,"%s %d\n",buffer,ptr->anzahl);
    print_to_buffer(buffer2,-1,-1,white,black);
    print_dictionary(ptr->right);
}


/*
//Geht vom Blatt zur Wurzel
int height(Dictionary *temp){
    if (temp == NULL) return 0;
    else return temp->level;
}


Dictionary *left_rotaition(Dictionary *temp){
    Dictionary  *x, *y;
    x = temp->right;
    y = temp->right->left;
    x->left = temp;
    temp->right = y;
    temp->level = (height(temp->left) > height(temp->right)? height(temp->left) : height(temp->right));
    x->level = (height(x->left) > height(x->right)? height(x->left) : height(x->right));
    return x;
}

Dictionary *right_rotaition(Dictionary *temp){
    Dictionary  *x, *y;
    x = temp->left;
    y = temp->left->right;
    x->right = temp;
    temp->left = y;
    temp->level = (height(temp->left) > height(temp->right)? height(temp->left) : height(temp->right));
    x->level = (height(x->left) > height(x->right)? height(x->left) : height(x->right));
    return x;
}
*/