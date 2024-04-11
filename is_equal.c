#include "operations.h"
#include <stdlib.h>
#include <stdio.h>


bool is_equal(int* A, int* B){
    int size_arr = 0;
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 0){
            size_arr++;
        }
    }
    if (size_arr == MAX_SIZE){
        return true;
    }
    else{
        return false;
    }
}