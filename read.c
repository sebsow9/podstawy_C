#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int** read(int* operation_number, int* isEOF) {
    int** A_B = malloc(sizeof(int*) * 2);
    if (A_B == NULL) {
        exit(1);  // Brak pamięci
    }

    int* A = malloc(sizeof(int) * MAX_SIZE);
    int* B = malloc(sizeof(int) * MAX_SIZE);
    if (A == NULL || B == NULL) {
        free(A);  // Zwalniamy A, jeśli B nie mogło zostać zaalokowane
        free(B);
        free(A_B);
        exit(1);  // Brak pamięci
    }

    char input_line[256];
    if (fgets(input_line, sizeof(input_line), stdin) == NULL) {
        *isEOF = 1;
        free(A);
        free(B);
        free(A_B);
        return NULL;
    }

    // Usuń znak nowej linii, jeśli istnieje
    input_line[strcspn(input_line, "\n")] = 0;

    

    int num_scanned = sscanf(input_line, "%d : %d %d %d %d %d %d %d %d %d %d",
                             operation_number,
                             &A[0], &A[1], &A[2], &A[3], &A[4],
                             &B[0], &B[1], &B[2], &B[3], &B[4]);                    

    if (num_scanned != 11) {  // 1 dla numeru operacji + 5 dla A + 5 dla B
        *isEOF = 1;
        free(A);
        free(B);
        free(A_B);
        return NULL;
    }

    A_B[0] = A;
    A_B[1] = B;
    fflush(stdin);
    return A_B;
}

