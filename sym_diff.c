#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

int* sym_diff(int* A, int* B, int* result_size){
    int* sym = malloc(sizeof(int) * (MAX_SIZE));
    if (sym == NULL) {
        exit(1); 
    }
    int sym_size = 0;
    
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            sym[sym_size] = A[j];
            sym_size++;
        }
    }
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (B[j] == A[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            sym[sym_size] = B[j];
            sym_size++;
        }
    }
    *result_size = sym_size;
    return sym;
}