#include "include/sort.h"

User **sort_user(int n, int offset, char type) {
    User **arr = malloc((n + 1) * sizeof(char *));
    User *temp = global_first_user;
    int i = 0;
    while (temp->next != NULL) {
        arr[i] = temp;
        temp = temp->next;
        i++;
    }
    merge_sort((char **) arr, n, offset, type);
    return arr;
}

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
                    arr2[i] = (char **) arr[k];
                    k++;
                } else {
                    arr2[i] = (char **) arr[j];
                    j++;
                }
            }
            break;
        case 's':
            for(i=0;k<size && j<middle;i++){
                if(strcmp((*((char**)(((char*)arr[j])+offset))),(*((char**)(((char*)arr[k])+offset))))>=0){
                    arr2[i] = (char **) arr[k];
                    k++;
                }
                else{
                    arr2[i] = (char **) arr[j];
                    j++;
                }
            }
            break;
        case 'n':
            for(i=0;k<size && j<middle;i++){
                if(strcmp(arr[j],arr[k])>=0){
                    arr2[i] = (char **) arr[k];
                    k++;
                }
                else{
                    arr2[i] = (char **) arr[j];
                    j++;
                }
            }
            break;
        case 'd':
            for (i = 0; k < size && j < middle; i++) {
                if ((*((double *) (((char *) arr[j]) + offset))) <
                    (*((double *) (((char *) arr[k]) + offset)))) {
                    arr2[i] = (char **) arr[k];
                    k++;
                } else {
                    arr2[i] = (char **) arr[j];
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
            arr2[i] = (char **) arr[j];
            j++;
        }
    }
    else if(k<size){
        for(i;k<size;i++){
            arr2[i] = (char **) arr[k];
            k++;
        }
    }
    arr_cpy(size, (char **) arr2, arr);
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
}
char** binary_search(char**array,char*search, int size){
    int middle=size/2;
    int cmp = strncmp(search, array[middle], strlen(search));
    if(size>1) {
        if (cmp == 0) {
            return &array[middle];
        } else if (cmp < 0) {
            return binary_search(array, search, middle);
        } else if (cmp > 0) {
            return binary_search(&array[middle], search, size - middle);
        }
    }else{
        if (cmp == 0) {
            return &array[middle];
        }
        return NULL;
    }
}
