#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

int* suma(int* A, int* B){
    int* sum = malloc(sizeof(int) * (MAX_SIZE * 2));
    if (sum == NULL) {
        exit(1); 
    }
    for (int i = 0; i < MAX_SIZE; ++i) {
        sum[i] = A[i];
        sum[i + MAX_SIZE] = B[i];
    }
    return sum;
}