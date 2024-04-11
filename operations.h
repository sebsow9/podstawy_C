#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>
#include <stdio.h>


#define MAX_SIZE 5

int** read(int* isEOF);
int* suma(int* A, int* B);
int* common_part(int* A, int* B, int* result_size);
int* difference(int* A, int* B, int* result_size);
int* sym_diff(int* A, int* B, int* result_size);
bool is_equal(int* A, int* B);
int checkSetsRelation(int* A, int* B);

#endif