#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

int* common_part(int* A, int* B,int* result_size){
    int* common = malloc(sizeof(int) * (MAX_SIZE));
    if (common == NULL) {
        exit(1); 
    }
    int common_size = 0;
    for(int j = 0; j< MAX_SIZE; j++){
        for (int g = 0; g< MAX_SIZE; g++){
            int already_exist = 0;
            if (A[j] == B[g]){
                for (int x = 0; x <=common_size; x++){
                    if (common[x] == A[j]){
                        already_exist = 1;
                    }
                }
                if(already_exist == 0){
                    common[common_size] = A[j];
                    common_size++;
                }       
            }
        }
    }
    *result_size = common_size;
    return common;
}