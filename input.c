#include "include/input.h"

char* get_string(char*string,int size,char*pointer,int type){
    int i=0;
    int array_size=0;
    Suggestions *suggestions=NULL;
    if(pointer!=NULL && type == STRING_ARRAY){
        for(array_size =0;((char**)pointer)[array_size]!=NULL;array_size++);
        merge_sort((char**)pointer,array_size,0,'n');
    }

    printf("-> ");
    global_input_buffer=0;
    global_send_input=false;

    Suggestions* temp_suggestions=NULL;
    bool changed_string=true;

    while(global_input_buffer!=13 || global_input_buffer=='\n'){
        if(global_send_input==true){
            switch(global_input_buffer){
            case 8:
                if(i>0) {
                    printf("\x1b[1D%c\x1b[1D", ' ');
                    global_send_input = false;
                    i--;
                    string[i]=0;
                    changed_string=true;
                }
                break;
            case 9:
                if(pointer!=NULL){
                    if(type==STRING_ARRAY){
                        if(changed_string) {
                            free_suggestions(suggestions);
                            suggestions = get_suggestions_from_array((char **) pointer, array_size, string);
                            temp_suggestions=suggestions;
                            changed_string = false;
                        }
                        if(suggestions!=NULL){
                            if(temp_suggestions==NULL){
                                temp_suggestions=suggestions;
                            }
                            while(i>0){
                                printf("\x1b[1D%c\x1b[1D", ' ');
                                i--;
                            }
                            printf("%s",temp_suggestions->string);
                            strcpy(string,temp_suggestions->string);
                            i=strlen(temp_suggestions->string);
                            temp_suggestions=temp_suggestions->next;
                        }
                    }
                    global_send_input = false;
                }
                    break;
                default:
                    string[i] = global_input_buffer;
                    printf("%c", string[i]);
                global_send_input = false;
                if (i < size) {
                    i++;
                    string[i]=0;
                } else {
                    break;
                }
                changed_string=true;
                break;
            }

        }
        Sleep(sync_delay/2);
    }
    string[i]=0;
    return string;
}

void *input_thread() {
    global_input_buffer=0;

    int c;
    do {
        if(_kbhit()) {
            c = _getch();
            switch (c) {
                case 0:
                case 224:
                    c=_getch();
                    switch(c) {
                            case 80:
                                if (global_current_pos < global_page_count * y_size - y_size) {
                                    global_current_pos++;
                                    draw_picture_buffer();
                                }
                                break;
                            case 72:
                                if (global_current_pos > 0) {
                                    global_current_pos--;
                                    draw_picture_buffer();
                                }
                                break;
                            case 75:
                                if (global_current_pos - y_size > 0) {
                                    global_current_pos -= y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos != 0) {
                                    global_current_pos = 0;
                                    draw_picture_buffer();

                                }
                                break;
                            case 77:
                                if (global_current_pos + y_size < global_page_count * y_size - y_size + 1) {
                                    global_current_pos += y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos + y_size != global_page_count * y_size - y_size) {
                                    global_current_pos = (global_page_count - 1) * y_size;
                                    draw_picture_buffer();
                                }

                                break;
                        }
                        break;
                default:
                    global_input_buffer= c;
                    global_send_input=true;
                    break;
            }
        }
        Sleep(sync_delay);
    }while(1);

}

int run_input_thread(){
    pthread_t pthread;
    pthread_create(&pthread, NULL, input_thread, NULL);
    while(global_send_input == -1){
        Sleep(sync_delay);
    }
    return 0;
}
Suggestions *get_suggestions_from_array(char**array,int size,char*search){
    if(search[0]==0){
        return NULL;
    }
    Suggestions first_suggestion;
    Suggestions *suggestions=&first_suggestion;
    suggestions->next=NULL;
    suggestions->string=NULL;

    char *result = (char*)binary_search(array,search,size);
    if(result ==NULL){
        return NULL;
    }

    int index=(int)((unsigned long long)result-(unsigned long long)array)/8;
    suggestions->next=malloc(sizeof(Suggestions));
    if(suggestions->next==NULL){
        perror("malloc");
        return NULL;
    }
    suggestions->next->string=array[index];
    suggestions->next->next=NULL;
    suggestions=suggestions->next;

    int temp_index=index;
    while(index-1>0 && strncmp(search,array[index-1],strlen(search))==0) {
        suggestions->next = malloc(sizeof(Suggestions));
        if (suggestions->next == NULL) {
            perror("malloc");
            return NULL;
        }
        suggestions->next->string = array[index - 1];
        suggestions->next->next=NULL;
        suggestions=suggestions->next;
        index--;
    }
    index=temp_index;
    while(index+1<size && strncmp(search,array[index+1],strlen(search))==0) {
        suggestions->next = malloc(sizeof(Suggestions));
        if (suggestions->next == NULL) {
            perror("malloc");
            return NULL;
        }
        suggestions->next->string = array[index + 1];
        suggestions->next->next=NULL;
        suggestions=suggestions->next;
        index++;
    }
    return first_suggestion.next;
}
void free_suggestions(Suggestions *suggestions){
    Suggestions*temp;
    while(suggestions!=NULL){
        temp=suggestions->next;
        free(suggestions);
        suggestions=temp;
    }
}