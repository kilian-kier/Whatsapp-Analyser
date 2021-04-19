#include "analyser.h"

void read_user() {
    Nachricht *ptr = first_nachricht;
    while (ptr != NULL) {

    }
}


//Wochentag und Uhrzeit
//0= Montag
int *count_date(Nachricht *ptr){
    int *arr1 = (int *)malloc(7*sizeof(int));
    for(int x = 0; x < 7; x++){
        *arr1 = 0;
        arr1 ++;
    }
    short weekday;
    int h, k;
    while(ptr->next != NULL){
        if(ptr->monat <= 2){
            h = ptr->monat + 12;
            k = ptr ->jahr -1;
        }
        else{
            h = ptr->monat;
            k = ptr->jahr;
        }
        weekday = (ptr->tag+2*h+(3*h+3)/5+k+k/4-k/100+k/400+1)%7;
        switch(weekday){
            case 0: *(arr1+6) += 1; break;
            case 1: *arr1 += 1; break;
            case 2: *(arr1+1) += 1; break;
            case 3: *(arr1+2) += 1; break;
            case 4: *(arr1+3) += 1; break;
            case 5: *(arr1+4) += 1; break;
            case 6: *(arr1+5) += 1; break;
            default: perror("Fehler Wochentag!"); break;
        }
        ptr = ptr->next;
    }
    return arr1;
}


