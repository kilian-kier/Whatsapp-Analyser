#include "menu.h"
#include "main.h"

#define menuefarbe 255,255,0


void main_menu(){
    char info[]="WhatsApp Analyzer\n";
    char opt1[]="Datei oeffnen";
    char opt2[]="Analizer ausfuehren";
    char opt3[]="Exit";
    do{
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
    if(select==0){
        select=!select;
    }
    else{
        startselect=select;
    }
    va_list options;
    do{
        clearscreen();
        va_start(options, select);
        anzeigeVordergrund(menuefarbe);
        printf("%s\n",va_arg(options, char*));
        anzeigeVordergrund(255,255,255);
        for(int i=1;i<=quantity;i++){
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
    }while(input != 13);

    return select;
}


void clearscreen(){
    printf("\x1b[H");
    printf("\x1b[0J");
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
