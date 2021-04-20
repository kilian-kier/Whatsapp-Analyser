#include "menu.h"


#define menuefarbe 255,255,0


void main_menu(){
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);

    CHAR_INFO picture_buffer[x_size*y_size];
    init_picture_buffer(picture_buffer);

    char info[]="WhatsApp Analyzer\n";
    char opt1[]="Datei oeffnen";
    char opt2[]="Analizer ausfuehren";
    char opt3[]="Exit";
    do{
        clearscreen();
        printf("\x1b[%dB",y_pos);
        draw_picture_buffer(picture_buffer);
        switch(menu(3,0,info,opt1,opt2,opt3)){
            case 0:
                exit(0);
            case 1:;
                FILE *f=fopen(get_file_name(), "rb");
                readFile(f);
                break;
            case 2:
                break;
            case 3:
                exit(0);
            default:
                break;
        }
    }while(1);
}


int menu(int quantity,int select,...){ // Koan Fehler des mitn Endless loop. CLION hot an schodn
    anzeigeHintergrund(0,0,0);
    anzeigeVordergrund(255,255,255);
    int input=0;
    int startselect=0;

    HANDLE hStdout;
    hStdout= GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cursor;
    COORD line[quantity];

    if(select==0){
        select=!select;
    }
    else{
        startselect=select;
    }
    va_list options;
    va_start(options, select);
    anzeigeVordergrund(menuefarbe);
    printf("%s\n",va_arg(options, char*));
    anzeigeVordergrund(255,255,255);
    for(int i=1;i<=quantity;i++){
        GetConsoleScreenBufferInfo(hStdout,&cursor);
        line[i-1]=cursor.dwCursorPosition;
        if(i==startselect){
            anzeigeVordergrund(menuefarbe);
        }
        if(select==i){
            printf("[*]\t");
        }
        else{
            printf("[ ]\t");
        }
        printf("%s\n",va_arg(options, char*));
        va_end(options);
        anzeigeVordergrund(255,255,255);
    }
    SetConsoleCursorPosition(hStdout,line[select-1]);
    do{
        do{
            fflush(stdin);
            input=getch();
        }while(input != 13 && input != 'w' && input != 's' && input != 27);

        switch(input){
            case 'w':
                select=select>1?select-1:quantity;
                break;
            case 's':
                select=select<quantity?select+1:1;
                break;
            case '':
                return 0;
            default:
                break;
        }
        printf("\x1b[1K\x1b[3D[ ]");
        SetConsoleCursorPosition(hStdout,line[select-1]);
        printf("\x1b[1K\x1b[3D[*]");
    }while(input != 13);

    return select;
}
void init_picture_buffer(CHAR_INFO picture_buffer[x_size*y_size]){
    for(int i=0;i<x_size*y_size;i++){
        picture_buffer[i].Char.AsciiChar=' ';
        picture_buffer[i].Attributes = BACKGROUND_INTENSITY;
    }
}
void draw_picture_buffer(CHAR_INFO picture_buffer[x_size*y_size]){
    HANDLE hStdout;
    hStdout= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordBufSize;
    COORD coordBufCoord;
    SMALL_RECT srctWriteRect;

    srctWriteRect.Top = y_pos;
    srctWriteRect.Left = x_pos;
    srctWriteRect.Bottom = y_pos+y_size;
    srctWriteRect.Right = x_pos+x_size;

    coordBufSize.Y = y_size;
    coordBufSize.X = x_size;
    coordBufCoord.X = 0;
    coordBufCoord.Y = 0;

    WriteConsoleOutput(hStdout,picture_buffer,coordBufSize,coordBufCoord,&srctWriteRect);
    return;
}

void clearscreen(){
    printf("\x1b[H\x1b[0J");
    return;
}
void anzeigeVordergrund(int r, int g, int b){
    printf("\x1b[38;2;%d;%d;%dm",r,g,b);
    return;
}
void anzeigeHintergrund(int r, int g, int b){
    printf("\x1b[48;2;%d;%d;%dm",r,g,b);
    return;
}
