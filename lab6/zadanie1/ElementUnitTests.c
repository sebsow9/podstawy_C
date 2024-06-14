// gcc Element.c ElementTests.c -o ElementTests -lm
//./ElementTests

#include "Element.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_get() {
    Element test_matrix[] = {{3, 1, 1, 10}, {3, 1, 2, 20}, {3, 1, 3, 30},
                             {3, 2, 1, 40}, {3, 2, 2, 50}, {3, 2, 3, 60}};
    Element query = {3, 2, 3, 0};
    int result = get(test_matrix, query); //sprawdzamy czy pobrany element jest rowny
    assert(result == 60);
    printf("test_get() passed\n");
}

void test_max_matrix_row_or_col_element() {
    Element matrixA[] = {{2, 1, 1, 1}, {2, 1, 2, 2}, {2, 2, 1, 3}, {2, 2, 2, 4}}; //{cols_num, row, col, value}
    Element matrixB[] = {{2, 1, 1, 5}, {2, 1, 2, 6}, {2, 2, 1, 7}, {2, 2, 2, 8}};
    int matrix_size = 4;

    int *result_col = max_matrix_row_or_col_element(true, matrixA, matrixB, matrix_size, matrix_size);
    assert(result_col[0] == 10 && result_col[1] == 12);

    int *result_row = max_matrix_row_or_col_element(false, matrixA, matrixB, matrix_size, matrix_size);
    assert(result_row[0] == 8 && result_row[1] == 12);

    free(result_col);
    free(result_row);

    printf("test_max_matrix_row_or_col_element() passed\n");
}

int main() {
    test_get();
    test_max_matrix_row_or_col_element();
    printf("All tests passed!\n");
    return 0;
}
