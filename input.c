#include "include/input.h"

char* get_string(char*string,int size,char*pointer,int type){
    int i=0;
    printf("-> ");
    global_input_buffer=0;
    global_send_input=false;
    while(global_input_buffer!=13 || global_input_buffer=='\n'){
        if(global_send_input==true){
            if(global_input_buffer==8  ){
                if(i>0) {
                    printf("\x1b[1D%c\x1b[1D", ' ');
                    global_send_input = false;
                    i--;
                }
            }else {
                string[i] = global_input_buffer;
                printf("%c", string[i]);
                global_send_input = false;
                if (i < size) {
                    i++;
                } else {
                    break;
                }
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
