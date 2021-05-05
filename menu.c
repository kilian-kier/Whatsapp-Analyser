#include <time.h>


#include "menu.h"
#define menuefarbe 255,255,0

void main_menu(){
    FILE *f = NULL;
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    init_picture_buffer(picture_buffer);
    printf("\x1b[?25l");
    //Tests
    bool menu1;
    bool menu2;
    draw_picture(picture_buffer, "whatsapptest.ppm", 0, 0,100,40);
    //print_to_buffer("Hallo Welt\nHallo Welt",-1,-1,(Color){255,0,0},black);
    //print_to_buffer("Hallo Welt\nHallo Welt",50,20,white,black);
    //draw_rect(0,0,1,5,white,1,1);
    char info[]="WhatsApp Analyzer\n";
    char opt1[]="Datei oeffnen";
    char opt2[]="Exit";
    char opt_back[]="Zurueck";

    char opt1_1[]="Users";

    char opt1_1_1[]="Anzahl geschriebene Nachrichten";
    char opt1_1_2[]="prozentual geschriebene Nachrichten";
    char opt1_1_3[]="durchschnittliche Woerteranzahl pro Nachricht";

    int is_read = 0;

    do{
        clearscreen();
        draw_picture_buffer(picture_buffer);
        printf("\x1b[%dB",y_pos);
        if (f != NULL) {
            menu2=true;
            clearscreen();
            do{
                printf("\x1b[%dB",y_pos);
                switch (menu(2, 0, info, opt1_1, opt_back)) {
                case 0:
                    exit(0);
                case 1:
                    if (is_read != 1) {
                        if (pthread_join(read_file_tread, NULL) != 0)
                            readFile(f);
                        if (pthread_join(read_user_tread, NULL) != 0)
                            read_user();
                        is_read = 1;
                    }
                    menu1=true;
                    clearscreen();
                    do {
                        printf("\x1b[%dB",y_pos);
                        switch (menu(4, 0, info, opt1_1_1, opt1_1_2, opt1_1_3, opt_back)) {
                            case 0:
                                exit(0);
                            case 1:
                                print_nachricht_len(0);
                                break;
                            case 2:
                                print_nachricht_len(1);
                                break;
                            case 4:
                                clearscreen();
                                printf("\x1b[%dB",y_pos);
                                menu1=false;
                                break;
                        }
                        draw_picture_buffer(picture_buffer);
                    }while(menu1);
                    break;
                case 2:
                    f = NULL;
                    menu2=false;
                    clearscreen();
                    break;
                default:
                    break;
            }
            }while(menu2);
        }
        else {
            switch (menu(2, 0, info, opt1, opt2)) {
                case 0:
                    exit(0);
                case 1:
                    f = fopen(get_file_name(), "rb");
                    pthread_create(&read_file_tread, NULL, readFile, (void *)f);
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
            picture_buffer[y][x].character=' ';
            picture_buffer[y][x].foreground= white;
            picture_buffer[y][x].background= black;

        }
    }
}
void print_to_buffer(char string[], int xpos,int ypos,Color foreground,Color background){
    static int y=0;
    static int x=0;
    if(xpos>=0){
        x=xpos;
    }
    if(ypos>=0){
        y=ypos;
    }
    int toprint=strlen(string);
    for(int i=0;i<toprint;i++){
        if(y>=y_size){
            return;
        }
        if(string[i]=='\n'){
            y++;
            if(xpos>0){
                x=xpos;
            }else{
                x=0;
            }
            continue;
        }
        picture_buffer[y][x].character=string[i];
        picture_buffer[y][x].foreground=foreground;
        picture_buffer[y][x].background=background;
        x++;
    }
    return;
}
void draw_rect(int xpos,int ypos,int xsize, int ysize, Color color, bool fill, bool layer){
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (fill || (!x || !y || y == ysize - 1 || x == xsize - 1)) {
                if (layer) {
                    picture_buffer[y + ypos][x + xpos].character = 219;
                    picture_buffer[y + ypos][x + xpos].foreground = color;
                } else {
                    picture_buffer[y + ypos][x + xpos].character = ' ';
                    picture_buffer[y + ypos][x + xpos].background = color;
                }
            }
        }
    }
    return;
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
            picture_buffer[y+ypos][x+xpos].character=' ';
            picture_buffer[y+ypos][x+xpos].background=(Color){(*buffer)[newy][newx][0],(*buffer)[newy][newx][1],(*buffer)[newy][newx][2]};
        }
    }
    free(*buffer);
    return;
}
void draw_picture_buffer(Pixel picture_buffer[y_size][x_size]){
    int r=0;
    int br;
    int g=0;
    int bg;
    int b=0;
    int bb;
        setvbuf(stdout,NULL,_IOFBF,(x_pos+x_size)*(y_pos+y_size)*25);
        printf("\x1b[%d;%dH",y_pos+1,x_pos+1);
        for(int y=0;y<y_size;y+=1){
            for(int x=0;x<x_size;x++){
                if(picture_buffer[y][x].background.r!=br ||picture_buffer[y][x].background.g!=bg ||picture_buffer[y][x].background.b!=bb){
                    br = picture_buffer[y][x].background.r;
                    bg = picture_buffer[y][x].background.g;
                    bb = picture_buffer[y][x].background.b;
                    anzeigeHintergrund(br,bg, bb);
                }
                if(picture_buffer[y][x].foreground.r!=br ||picture_buffer[y][x].foreground.g!=bg ||picture_buffer[y][x].foreground.b!=bb){
                    r = picture_buffer[y][x].foreground.r;
                    g = picture_buffer[y][x].foreground.g;
                    b = picture_buffer[y][x].foreground.b;
                    anzeigeVordergrund(r,g, b);
                }

                printf("%c",picture_buffer[y][x].character);
            }
            printf("\x1b[%dD\x1b[1B",x_size);
        }
        fflush(stdout);
        anzeigeVordergrund(255,255,255);
        printf("\x1b[H");
        setvbuf(stdout,NULL,_IONBF,0);
    return;
}

void clearscreen(){
    printf("\x1b[H\x1b[0J");
    return;
}
void anzeigeVordergrund(int r, int g, int b){
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
    return;
}
void anzeigeHintergrund(int r, int g, int b){
    printf("\x1b[48;2;%d;%d;%dm",r,g,b);
    return;
}
