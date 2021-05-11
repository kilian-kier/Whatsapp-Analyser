#include "include/sort.h"

void merge(char **arr, int size,int offset,char type){
    char ** arr2[size];
    int j=0;
    int middle=size/2;
    int k=middle;
    int i=0;

    switch(type){
        case 'u':
            for (i = 0; k < size && j < middle; i++) {
                if ((*((unsigned int *) (((char *) arr[j]) + offset))) <
                    (*((unsigned int *) (((char *) arr[k]) + offset)))) {
                    arr2[i] = arr[k];
                    k++;
                } else {
                    arr2[i] = arr[j];
                    j++;
                }
            }
            break;
        case 's':
            for(i=0;k<size && j<middle;i++){
                if(strcmp((*((char**)(((char*)arr[j])+offset))),(*((char**)(((char*)arr[k])+offset))))>=0){
                    arr2[i]=arr[k];
                    k++;
                }
                else{
                    arr2[i]=arr[j];
                    j++;
                }
            }
            break;
        case 'd':
            for (i = 0; k < size && j < middle; i++) {
                if ((*((double *) (((char *) arr[j]) + offset))) <
                    (*((double *) (((char *) arr[k]) + offset)))) {
                    arr2[i] = arr[k];
                    k++;
                } else {
                    arr2[i] = arr[j];
                    j++;
                }
            }
            break;
        default:
            printf("Merge: Unbekanntes Format");
            break;
    }
    if(j<middle){
        for(i;j<middle;i++){
            arr2[i]=arr[j];
            j++;
        }
    }
    else if(k<size){
        for(i;k<size;i++){
            arr2[i]=arr[k];
            k++;
        }
    }
    arr_cpy(size,arr2,arr);
    return;
}
char ** merge_sort(char **arr,int size, int offset,char type){
    int middle=size/2;
    if(size>=2){
        merge_sort(arr,size/2,offset,type);
        merge_sort(&arr[middle],size-size/2,offset,type);
        merge(arr,size,offset,type);
    }
    return arr;
}
void arr_cpy(int size, char**arr1,char**arr2){
    for(int i=0;i<size;i++){
        arr2[i]=arr1[i];
    }
    return;
}
