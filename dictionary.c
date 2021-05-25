#include "include/dictionary.h"

void create_dictionary() {
    gloabl_first_word = NULL;
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
                gloabl_first_word = insert_word(anfang, laenge, gloabl_first_word);
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
        if (gloabl_first_word == NULL) gloabl_first_word = temp;
        return temp;
    } else {
        if (l <= temp->laenge) y = l;
        else y = temp->laenge;
        if (strncmp(anfang, temp->wortanfang, y) == 0) {
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
    if (ptr == NULL) return;
    print_dictionary(ptr->left);
    strncpy(buffer, ptr->wortanfang, ptr->laenge);
    buffer[ptr->laenge] = '\0';
    printf("%-30s\n", buffer);
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