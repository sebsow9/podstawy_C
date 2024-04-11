#include "operations.h"
#include <stdlib.h>
#include <stdio.h>


int** read(int* isEOF){
    
    int** A_B = malloc(sizeof(int*)*2);
    if (!A_B) {
        printf("Memory allocation failed for A_B\n");
        *isEOF = 1;
        return NULL;
    }

    int* A = malloc(sizeof(int)*MAX_SIZE);
    if (!A) {
        printf("Memory allocation failed for A\n");
        free(A_B); // Clean up previously allocated memory
        *isEOF = 1;
        return NULL;
    }

    int* B = malloc(sizeof(int)*MAX_SIZE);
    if (!B) {
        printf("Memory allocation failed for B\n");
        free(A);   
        free(A_B); 
        return NULL;
    }
        printf("Podaj %d elementow tablicy A: ", MAX_SIZE);
        for(int i = 0; i < MAX_SIZE; i++){
            if (scanf("%d", &A[i]) != 1) {
                printf("EOF or input error encountered\n");
                free(A);
                free(B);
                free(A_B);
                *isEOF = 1; 
                printf("EOF encountered\n");
                return NULL;
            }
        }
        
        printf("Podaj %d elementow tablicy B: ", MAX_SIZE);
        for(int i = 0; i < MAX_SIZE; i++){
            if (scanf("%d", &B[i]) != 1) {
                printf("EOF or input error encountered\n");
                free(A);
                free(B);
                free(A_B);
                *isEOF = 1; 
                printf("EOF encountered\n");
                return NULL;
            }
        }
        A_B[0] = A;
        A_B[1] = B;
        return A_B;
}
