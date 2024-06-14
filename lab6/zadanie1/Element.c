// Element.c
#include "Element.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define max(a, b) ((a) >= (b) ? (a) : (b))

int get(Element *matrix, Element e){
    int j;
    for (int i = 0; i < e.cols_num; i++){
        if (matrix[i].col == e.col){
            j = i;
            while (true){
                if (matrix[j].row == e.row){
                    return matrix[j].value;
                }
                j = j + e.cols_num; 
            }
        }
    }
}

int *max_matrix_row_or_col_element(bool horizontal, Element *matrixA, Element *matrixB, int matrix_size_A, int matrix_size_B) {
    int n = sqrt(matrix_size_A);
    int *maxA = (int *) malloc(sizeof(int) * n);
    int *maxB = (int *) malloc(sizeof(int) * n);
    int *result = (int *) malloc(sizeof(int) * n);
    if (maxA == NULL || maxB == NULL || result == NULL) {
        free(maxA);
        free(maxB);
        free(result);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        maxA[i] = INT_MIN;
        maxB[i] = INT_MIN;
    }

    for (int i = 0; i < matrix_size_A; i++) {
        int index = horizontal ? (i % n) : (i / n);
        maxA[index] = max(maxA[index], matrixA[i].value);
    }

    for (int i = 0; i < matrix_size_B; i++) {
        int index = horizontal ? (i % n) : (i / n);
        maxB[index] = max(maxB[index], matrixB[i].value);
    }

    for (int i = 0; i < n; i++) {
        result[i] = maxA[i] + maxB[i];
    }

    free(maxA);
    free(maxB);

    return result;
}
void put_into_matrix(int* data, Element *matrix, int row, int col){

    int current_row = 1;
    for(int i = 1; i <= row*col; i++){ //przechodzimy po kolumnach, czyli wypelniamy wiersze po kolei 1 wiersz potem drugi itd
        matrix[i-1].row = current_row;
        matrix[i-1].col = ((i-1) % col)+1;
        matrix[i-1].value = data[i-1];
        matrix[i-1].cols_num = col;
        printf("current value is %d, current row: %d current col: %d\n",matrix[i-1].value, matrix[i-1].row, matrix[i-1].col );
        if((i)%col == 0){
            current_row++;
        } 
    }
}

