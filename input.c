#include "include/input.h"

char *get_string(char *string, int size, char *pointer) {

    int i = 0, j = 0;
    int array_size = 0;
    if (pointer != NULL) {
        for (array_size = 0; ((char **) pointer)[array_size] != NULL; array_size++);
        merge_sort((char **) pointer, array_size, 0, 'n');
    }
    global_input_buffer = 0;
    global_send_input = false;

    List*suggestions=NULL;
    List *temp_suggestions = NULL;
    Dictionary*last_suggestion=NULL;
    bool changed_string = true;

    printf("   ");


        while (global_input_buffer != 13 && global_input_buffer != '\n') {
            if (j % 66 < 33) {
                cursor_blink(true,i);
            } else {
                cursor_blink(false,i);
            }

            if (global_send_input == true) {
                switch (global_input_buffer) {
                    case 10:
                    case 13:
                        break;
                    case 8:
                        if (i > 0) {
                            global_send_input = false;
                            printf(" ");
                            delete_n_char(2);
                            i--;
                            string[i] = 0;
                            changed_string = true;
                        }
                        break;
                    case '':
                        return NULL;
                    case 9:
                        if (pointer != NULL) {
                            if (changed_string) {
                                free_list(suggestions);
                                    suggestions = get_suggestions_from_array((char **) pointer, array_size, string);

                                temp_suggestions = suggestions;
                                changed_string = false;
                            }
                            if (suggestions != NULL) {
                                if (temp_suggestions == NULL) {
                                    temp_suggestions = suggestions;
                                }
                                strcpy(string, temp_suggestions->i.pointer);

                                printf(" ");
                                delete_n_char(i+1);
                                i = strlen(string);
                                printf("%s", string);
                                temp_suggestions = temp_suggestions->next;
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
                            string[i] = 0;
                        } else {
                            break;
                        }
                        changed_string = true;
                        break;
                }

            }
            j++;
            Sleep(sync_delay / 2);
        }
    free_list(suggestions);
    string[i] = 0;
    return string;
}

void *input_thread() {
    global_input_buffer = 0;

    int c;
    do {
        if (_kbhit()) {
            c = _getch();
            switch (c) {
                case 0:
                case 224:
                    c = _getch();
                    if(global_arrow_keys=='s'){
                        global_input_buffer=c+256;
                        global_send_input=true;
                        break;
                    }
                    switch (c) {
                        case key_right:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos < global_page_count * y_size - y_size) {
                                    global_current_pos++;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 1) {
                                if (global_settings.empty_lines != 0)
                                    global_settings.empty_lines--;
                            } else if (global_arrow_keys == 2) {
                                if (global_settings.top_n != 0)
                                    global_settings.top_n--;
                            }
                            break;
                        case key_left:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos > 0) {
                                    global_current_pos--;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 1)
                                global_settings.empty_lines++;
                            else if (global_arrow_keys == 2)
                                global_settings.top_n++;
                            break;
                        case key_up:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos - y_size > 0) {
                                    global_current_pos -= y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos != 0) {
                                    global_current_pos = 0;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 2) {
                                if (global_settings.top_n >= 11)
                                    global_settings.top_n -= 10;
                            }
                            break;
                        case key_down:
                            if (global_arrow_keys == 0) {
                                if (global_current_pos + y_size < global_page_count * y_size - y_size + 1) {
                                    global_current_pos += y_size;
                                    draw_picture_buffer();
                                } else if (global_current_pos + y_size != global_page_count * y_size - y_size) {
                                    global_current_pos = (global_page_count - 1) * y_size;
                                    draw_picture_buffer();
                                }
                            } else if (global_arrow_keys == 2) {
                                global_settings.top_n += 10;
                            }

                            break;
                    }
                    break;
                default:
                    global_input_buffer = c;
                    global_send_input = true;
                    break;
            }
        }
        Sleep(sync_delay);
    } while (1);

}

int run_input_thread() {
    pthread_t pthread;
    pthread_create(&pthread, NULL, input_thread, NULL);
    while (global_send_input == -1) {
        Sleep(sync_delay);
    }
    return 0;
}
Dictionary* find_in_tree(Dictionary*ptr,char*search){

    if(ptr==NULL) return NULL;

    int comparison=comparison=strncmp(search,ptr->words->current_message->message+ptr->words->offset,strlen(search));
    if(comparison==0){
        if(ptr->left!=NULL){
            comparison=strncmp(search,ptr->left->words->current_message->message+ptr->left->words->offset,strlen(search));
        }
        if(ptr->left!=NULL && comparison==0){
            return find_in_tree(ptr->left,search);
        }else{
            return ptr;
        }

    }else if(comparison<0){
        return find_in_tree(ptr->left,search);
    }else{
        return find_in_tree(ptr->right,search);
    }


    return ptr;
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
List *get_suggestions_from_array(char **array, int size, char *search) {
    if (search[0] == 0) {
        return NULL;
    }
    List first_suggestion;
    List *suggestions = &first_suggestion;
    suggestions->next = NULL;

    char *result = (char *) binary_search(array, search, size);
    if (result == NULL) {
        return NULL;
    }

    int index = (int) ((unsigned long long) result - (unsigned long long) array) / 8;
    suggestions->next = malloc(sizeof(List));
    if (suggestions->next == NULL) {
        perror("malloc");
        return NULL;
    }

    suggestions->next->i.pointer = array[index];

    int temp_index = index;
    while (index - 1 > 0 && strncmp(search, array[index - 1], strlen(search)) == 0) {
        suggestions->next = malloc(sizeof(List));
        if (suggestions->next == NULL) {
            perror("malloc");
            return NULL;
        }
        suggestions->next->i.pointer = array[index - 1];
        suggestions->next->next = NULL;
        suggestions = suggestions->next;
        index--;
    }
    index = temp_index;

    while (index + 1 < size && strncmp(search, array[index + 1], strlen(search)) == 0) {
        suggestions->next = malloc(sizeof(List));
        if (suggestions->next == NULL) {
            perror("malloc");
            return NULL;
        }
        suggestions->next->i.pointer = array[index + 1];
        suggestions->next->next = NULL;
        suggestions = suggestions->next;
        index++;
    }
    return first_suggestion.next;
}


void delete_n_char(int n){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hStdout, &bufferInfo);
    bufferInfo.dwCursorPosition.X-=n;
    SetConsoleCursorPosition(hStdout,bufferInfo.dwCursorPosition);
    for(int i=0;i<n;i++){
        printf(" ");
    }
    SetConsoleCursorPosition(hStdout,bufferInfo.dwCursorPosition);
}
void cursor_blink(bool on,int offset){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hStdout, &bufferInfo);
    bufferInfo.dwCursorPosition.X-=(offset+3);
    SetConsoleCursorPosition(hStdout,bufferInfo.dwCursorPosition);
    printf("-> ");
    bufferInfo.dwCursorPosition.X+=(offset+3);
    SetConsoleCursorPosition(hStdout,bufferInfo.dwCursorPosition);
    if(on){
        printf("%c",179);
    }else{
        printf(" ");
    }
    SetConsoleCursorPosition(hStdout,bufferInfo.dwCursorPosition);
}
