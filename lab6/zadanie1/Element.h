#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

typedef struct {
    int cols_num;
    int row;
    int col;
    int value;
} Element;

int get(Element *matrix, Element e);
int *max_matrix_row_or_col_element(bool horizontal, Element *matrixA, Element *matrixB, int matrix_size_A, int matrix_size_B);
void put_into_matrix(int* data, Element *matrix, int row, int col);

#endif