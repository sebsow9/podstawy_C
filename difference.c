#include "operations.h"
#include <stdlib.h>

int* difference(int* A, int* B, int* result_size){
    int* diff = malloc(sizeof(int) * (MAX_SIZE));
    if (diff == NULL) {
        exit(1); 
    }
    int diff_size = 0;
    
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            diff[diff_size] = A[j];
            diff_size++;
        }
    }


    *result_size = diff_size;
    return diff;
}