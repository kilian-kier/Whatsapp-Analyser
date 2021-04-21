#include "analyser.h"

int anz_nachrichten = 0;

void read_user() {
    Nachricht *ptr = first_nachricht;
    while (ptr != NULL) {

    }
}


//Nachrichten anhand der Wochentage zählen
int *count_weekday(){
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *)malloc(7*sizeof(int));
    for(int x = 0; x < 7; x++){
        *(arr1+x) = 0;
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


void count_nachrichten(){
    Nachricht *ptr = first_nachricht;
    while(ptr != NULL){
        anz_nachrichten ++;
        ptr = ptr->next;
    }
}

//Nachrichten anhand von Stunden zählen
int *count_hours(){
    Nachricht *ptr = first_nachricht;
    int *arr1 = (int *)malloc(24*sizeof(int));
    for(int x = 0; x < 24; x++){
        *(arr1+x) = 0;
    }
    while(ptr->next != NULL){
        switch(ptr->stunde){
            case 0: *(arr1) += 1; break;
            case 1: *(arr1+1) += 1; break;
            case 2: *(arr1+2) += 1; break;
            case 3: *(arr1+3) += 1; break;
            case 4: *(arr1+4) += 1; break;
            case 5: *(arr1+5) += 1; break;
            case 6: *(arr1+6) += 1; break;
            case 7: *(arr1+7) += 1; break;
            case 8: *(arr1+8) += 1; break;
            case 9: *(arr1+9) += 1; break;
            case 10: *(arr1+10) += 1; break;
            case 11: *(arr1+11) += 1; break;
            case 12: *(arr1+12) += 1; break;
            case 13: *(arr1+13) += 1; break;
            case 14: *(arr1+14) += 1; break;
            case 15: *(arr1+15) += 1; break;
            case 16: *(arr1+16) += 1; break;
            case 17: *(arr1+17) += 1; break;
            case 18: *(arr1+18) += 1; break;
            case 19: *(arr1+19) += 1; break;
            case 20: *(arr1+20) += 1; break;
            case 21: *(arr1+21) += 1; break;
            case 22: *(arr1+22) += 1; break;
            case 23: *(arr1+23) += 1; break;
            default: perror("Fehler Uhrzeit!"); break;
        }
        ptr = ptr->next;
    }
    return arr1;
}