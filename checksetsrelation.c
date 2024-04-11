#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

int checkSetsRelation(int* A, int* B) {
    int countAinB = 0, countBinA = 0;
    
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            if (A[i] == B[j]) {
                countAinB++;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            if (B[i] == A[j]) {
                countBinA++;
                break;
            }
        }
    }
    if (countAinB == MAX_SIZE && countBinA == MAX_SIZE) return 0;
    else if (countAinB == MAX_SIZE) return 1; 
    else if (countBinA == MAX_SIZE) return 2; 
    else return 3;
} 