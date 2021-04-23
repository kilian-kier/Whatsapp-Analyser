#include "menu.h"


#define menuefarbe 255,255,0


void main_menu(){
    FILE *f = NULL;
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    init_picture_buffer(picture_buffer);
    printf("\x1b[?25l");
    // La zi testn vielleicht brauchwos a net. Do isch do Pfad auszibessern.
    //draw_picture(picture_buffer, "C:\\Users\\Martin Gamper\\Downloads\\putin.ppm", 0, 0,150,40);
    char info[]="WhatsApp Analyzer\n";
    char opt1[]="Datei oeffnen";
    char opt2[]="Exit";

    char opt1_1[]="Users";
    char opt1_2[]="Nachrichten";
    char opt1_3[]="Monat";
    char opt1_4[]="Uhrzeit";
    char opt1_5[]="Back";
    do{
        clearscreen();
        draw_picture_buffer(picture_buffer,COMBINED_MODE);
        printf("\x1b[%dB",y_pos);
        if (f != NULL) {
            switch (menu(5, 0, info, opt1_1, opt1_2, opt1_3, opt1_4, opt1_5)) {
                case 0:
                    exit(0);
                case 1:
                    read_user();
                    break;
                case 5:
                    f = NULL;
                    clearscreen();
                    break;
                default:
                    break;
            }
        }
        else {
            switch (menu(2, 0, info, opt1, opt2)) {
                case 0:
                    exit(0);
                case 1:;
                    f = fopen(get_file_name(), "rb");
                    readFile(f);
                    break;
                case 2:
                    exit(0);
                default:
                    break;
            }
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
        fflush(stdout);
    }while(input != 13);

    return select;
}
void init_picture_buffer(Pixel picture_buffer[y_size][x_size]){
    for(int y=0;y<y_size;y++){
        for(int x=0;x<x_size;x++){
            picture_buffer[y][x].character=219;
            picture_buffer[y][x].r=0;
            picture_buffer[y][x].g=0;
            picture_buffer[y][x].b=0;
        }
    }
}
void draw_picture(Pixel picture_buffer[y_size][x_size], char *file, int xpos, int ypos,int xsize, int ysize){
    char rubbish[100];
    unsigned char color;
    int ret=1;
    int columns=0;
    int rows=0;

    FILE * picture=fopen(file,"rb");
    if(picture==NULL){
        perror("fopen");
        return;
    }
    rewind(picture);

    for(int i=0;i<2;i++){
        fgets(rubbish,100,picture);
    }
    fscanf(picture,"%d %d\n",&columns,&rows);
    if(xsize+xpos>x_size || ysize+ypos>y_size){
        printf("Bild ist zu gross");
        return;
    }

    unsigned char (*buffer)[rows][columns][3]=(unsigned char(*)[rows][columns][3]) malloc(sizeof (unsigned char)*rows*columns*3);
    //perror("fehler");
    //Sleep(10000);

    fgets(rubbish,100,picture);
    for(int y=0;y<rows && ret==1;y++){
        for(int x=0;x<columns && ret==1;x++) {
            fread(&color, 1, 1, picture);
            (*buffer)[y][x][0] = color;
            fread(&color, 1, 1, picture);
            (*buffer)[y][x][1] = color;
            ret=fread(&color, 1, 1, picture);
            (*buffer)[y][x][2] = color;
        }
    }
    int newx;
    int newy;
    for(int y=0;y<ysize;y++){
        for(int x=0;x<xsize;x++){
            newx=x*columns/xsize;
            newy=y*rows/ysize;
            picture_buffer[y+ypos][x+xpos].character=219;
            picture_buffer[y+ypos][x+xpos].r=(*buffer)[newy][newx][0];
            picture_buffer[y+ypos][x+xpos].g=(*buffer)[newy][newx][1];
            picture_buffer[y+ypos][x+xpos].b=(*buffer)[newy][newx][2];
        }
    }
    free(*buffer);
    return;
}
void draw_picture_buffer(Pixel picture_buffer[y_size][x_size] ,int mode){
    int r;
    int g;
    int b;
    if(mode==FAST_MODE || mode ==3){
        CHAR_INFO *secondary_buffer= (CHAR_INFO*) malloc(sizeof(CHAR_INFO)*x_size*y_size);
        for(int y=0;y<y_size;y++){
            for(int x=0;x<x_size;x++){
                r=picture_buffer[y][x].r>100?1:0;
                g=picture_buffer[y][x].g>100?1:0;
                b=picture_buffer[y][x].b>100?1:0;
                secondary_buffer[(y)*x_size +x].Char.AsciiChar = picture_buffer[y][x].character;
                secondary_buffer[(y)*x_size +x].Attributes= r*FOREGROUND_RED | g*FOREGROUND_GREEN | b*FOREGROUND_BLUE | BACKGROUND_INTENSITY;
            }
        }
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

        WriteConsoleOutput(hStdout,secondary_buffer,coordBufSize,coordBufCoord,&srctWriteRect);
        free(secondary_buffer);
    }
    if(mode==SLOW_MODE || mode==3){
        setvbuf(stdout,NULL,_IOLBF,(x_pos+x_size)*10);
        printf("\x1b[%d;%dH",y_pos+1,x_pos+1);
        for(int y=0;y<y_size;y+=1){
            for(int x=0;x<x_size;x++){
                r = picture_buffer[y][x].r;
                g = picture_buffer[y][x].g;
                b = picture_buffer[y][x].b;
                anzeigeVordergrund(r,g, b);
                printf("%c",picture_buffer[y][x].character);
            }
            fflush(stdout);
            printf("\x1b[%dD\x1b[1B",x_size);
        }
        anzeigeVordergrund(255,255,255);
        printf("\x1b[H");
        setvbuf(stdout,NULL,_IONBF,0);
    }
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
