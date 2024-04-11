#include "operations.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_suma() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {6, 7, 8, 9, 10};
    int expected[MAX_SIZE * 2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* result = suma(A, B);

    for (int i = 0; i < MAX_SIZE * 2; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
    printf("test_suma passed.\n");
}

void test_common_part() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {3, 4, 5, 6, 7};
    int expected[] = {3, 4, 5};
    int result_size = 0;
    int* result = common_part(A, B, &result_size);

    assert(result_size == 3);
    for (int i = 0; i < result_size; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
    printf("test_common_part passed.\n");
}

void test_difference() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {4, 5, 6, 7, 8};
    int expected[] = {1, 2, 3};
    int result_size = 0;
    int* result = difference(A, B, &result_size);

    assert(result_size == 3);
    for (int i = 0; i < result_size; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
    printf("test_difference passed.\n");
}

void test_sym_diff() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {4, 5, 6, 7, 8};
    int expected[] = {1, 2, 3, 6, 7, 8};
    int result_size = 0;
    int* result = sym_diff(A, B, &result_size);

    assert(result_size == 6);
    for (int i = 0; i < result_size; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
    printf("test_sym_diff passed.\n");
}

void test_is_equal() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {1, 2, 3, 4, 5};
    int C[MAX_SIZE] = {5, 4, 3, 2, 1};

    assert(is_equal(A, B) == true);
    assert(is_equal(A, C) == false);
    printf("test_is_equal passed.\n");
}

void test_checkSetsRelation() {
    int A[MAX_SIZE] = {1, 2, 3, 4, 5};
    int B[MAX_SIZE] = {1, 2, 3, 4, 5};
    int C[MAX_SIZE] = {1, 2, 3};
    int D[MAX_SIZE] = {1, 2, 3, 4, 5};

    assert(checkSetsRelation(A, B) == 0); // A and B are equal
    assert(checkSetsRelation(A, C) == 1); // A includes C
    assert(checkSetsRelation(C, A) == 2); // C is included in A
    assert(checkSetsRelation(A, D) == 3); // A and D are not equal
    printf("test_checkSetsRelation passed.\n");
}

int main() {
    test_suma();
    test_common_part();
    test_difference();
    test_sym_diff();
    test_is_equal();
    test_checkSetsRelation();

    return 0;
}
