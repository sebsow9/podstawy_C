// gcc Element.c ElementIntegrationTests.c -o IntegrationTests -lm
//./IntegrationTests

#include "Element.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void run_integration_test(int *input_dataA, int *input_dataB, int rows, int cols, int expected_max_row, int expected_max_col) {
    int matrix_size = rows * cols;


    Element *Matrix_A = malloc(matrix_size * sizeof(Element));
    Element *Matrix_B = malloc(matrix_size * sizeof(Element));
    if (!Matrix_A || !Matrix_B) {
        printf("Memory allocation failed\n"); //czy dziala alokacja pamieci
        return;
    }

    // wpuszczmay dane do macierzy
    put_into_matrix(input_dataA, Matrix_A, rows, cols);
    put_into_matrix(input_dataB, Matrix_B, rows, cols);

    // sprawdzamy maxima maxierzy
    int *max_row = max_matrix_row_or_col_element(false, Matrix_A, Matrix_B, matrix_size, matrix_size);
    int *max_col = max_matrix_row_or_col_element(true, Matrix_A, Matrix_B, matrix_size, matrix_size);

    if (max_row[0] != expected_max_row || max_col[0] != expected_max_col) {
        printf("Failed: Expected max_row[0] = %d, got %d; Expected max_col[0] = %d, got %d\n",
               expected_max_row, max_row[0], expected_max_col, max_col[0]);
    }

    // porownujemy czy jest rowne
    assert(max_row[0] == expected_max_row);
    assert(max_col[0] == expected_max_col);

    // zwalniamy pamiec
    free(Matrix_A);
    free(Matrix_B);
    free(max_row);
    free(max_col);

    printf("Integration test passed for %d x %d matrix.\n", rows, cols);
}

int main() {
    // prosty przyklad macierzy 2x2
    int input_dataA1[] = {1, 2, 3, 4}; // format: {pierwsza kolumna, druga kolumna, pierwsz kolumna, druga kolumna}, {pierwszy wiersz, pierwszy wiersz, drugi wiersz...}
    int input_dataB1[] = {5, 6, 7, 8};
    run_integration_test(input_dataA1, input_dataB1, 2, 2, 8, 10);  // sprawdzamy czy maksima sie sobie rownaja, format: (data, data, row, col, max w 1 row, max w 1 col)

    // Zera
    int zerosA[] = {0, 0, 0, 0};
    int zerosB[] = {0, 0, 0, 0};
    run_integration_test(zerosA, zerosB, 2, 2, 0, 0); 

    // ujemne wartosci
    int negA[] = {-1, -2, -3, -4}; 
    int negB[] = {-5, -6, -7, -8};
    run_integration_test(negA, negB, 2, 2, -6, -6); 

    // mieszane
    int mixedA[] = {1, -2, 0, -3, 4, 5, 6, 0, -1};
    int mixedB[] = {0, 6, -1, 2, -4, -5, 1, 2, 3};
    run_integration_test(mixedA, mixedB, 3, 3, 7, 8); 

    // wieksze macierze
    int largeA[] = {1, 5, 2, 8, 3, 6, 7, 4, 5, 2, 8, 1, 7/*najwieksza wartosc col 1*/, 4, 3, 6};
    int largeB[] = {2, 6, 3, 9, 4, 7, 8, 5, 6, 3, 9, 2, 8 /*najwieksza wartosc col 1*/, 5, 4, 7};
    run_integration_test(largeA, largeB, 4, 4, 17, 15); 



    return 0;
}
