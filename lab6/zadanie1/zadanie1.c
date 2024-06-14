#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define max(a, b) ((a) >= (b) ? (a) : (b))


typedef struct {
    int cols_num;
    int row;
    int col;
    int value;
} Element;


int get(Element *matrix, Element e){
    int j;

    for (int i = 0; i < e.cols_num; i++){ // najpierwsz szukamy dobrej kolumny, potem szukamy w tej kolumnie odpowiedniego wiersza
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

void put_into_arr(char* arr, int* result){ // wsadzamy dane z lini ktore pobralismy dopoki nie znajdziemy znaku null
    int i = 0;
    int result_index = 0;
    while (arr[i] != '\0'){
        if (arr[i] != ' '){
            result[result_index] = arr[i] - '0';
            result_index++;
        }
        i++;
    }
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

int * max_matrix_row_or_col_element(bool horizontal, Element *matrixA, Element *matrixB, int matrix_size_A, int matrix_size_B) {
    int n = sqrt(matrix_size_A); // kwadratowe macierze
    int *maxA = (int *) malloc(sizeof(int) * n);
    int *maxB = (int *) malloc(sizeof(int) * n);
    int *result = (int *) malloc(sizeof(int) * n);
    if (maxA == NULL || maxB == NULL || result == NULL) {
        free(maxA);  //bezpieczenstwo
        free(maxB);
        free(result);
        return NULL;
    }

    // inicjalizacja maciezry
    for (int i = 0; i < n; i++) {
        maxA[i] = INT_MIN;
        maxB[i] = INT_MIN;
        result[i] = 0;
    }

    // max wartosci A
    for (int i = 0; i < matrix_size_A; i++) {
        int index = horizontal ? (i % n) : (i / n);
        maxA[index] = max(maxA[index], matrixA[i].value);
    }

    // max wartosci B
    for (int i = 0; i < matrix_size_B; i++) {
        int index = horizontal ? (i % n) : (i / n);
        maxB[index] = max(maxB[index], matrixB[i].value);
    }

    // Suma max wartosci
    for (int i = 0; i < n; i++) {
        result[i] = maxA[i] + maxB[i];
    }

    free(maxA);
    free(maxB);

    return result;
}






int main(){
    int row_colA[2], A_col, A_row, A_data[100];
    int row_colB[2], B_col, B_row, B_data[100];

    Element *Matrix_A = NULL;
    Element *Matrix_B = NULL;

    int matrix_size_A, matrix_size_B;


    printf("Podaj liczbe wierszy i kolumn, oraz elementy poszczegolnych macierzy\n");

    for (int enter_count = 0; enter_count < 4; enter_count++){ //pobieramy dane do poki nie bedzie 4 enterow
        char line[100];

        scanf("%[^\n]", line); // pobieramy do entera
        
        while(getchar() != '\n'){} //czyscimy bufor

        switch (enter_count){
        case 0:
            put_into_arr(line, row_colA); //dajemy dane do tablicy, pozniej przypisujemy zmienne z tej tablicy
            A_col = row_colA[1];
            A_row = row_colA[0];
            matrix_size_A = A_col * A_row;
            break;
        case 1:
            put_into_arr(line, A_data);
            Matrix_A = malloc((A_row * A_col) * sizeof(Element)); //tworzymy strukture do przechowywania col * row struktur typu Element i ja inicjalizujemy
            put_into_matrix(A_data, Matrix_A, A_row, A_col);
            break;
        case 2:
            put_into_arr(line, row_colB); //dajemy dane do tablicy, pozniej przypisujemy zmienne z tej tablicy
            B_col = row_colB[1];
            B_row = row_colB[0];
            matrix_size_B = B_col * B_row;
            break;
        case 3:
            put_into_arr(line, B_data);
            Matrix_B = malloc((B_row * B_col) * sizeof(Element)); //tworzymy strukture do przechowywania col * row struktur typu Element i ja inicjalizujemy
            put_into_matrix(B_data, Matrix_B, B_row, B_col);

            break;
        }
        
    }

    Element element1 = {A_col, 1, 1, 0};
    int value = get(Matrix_A, element1);
    int* max_arr = max_matrix_row_or_col_element(false, Matrix_A, Matrix_B, matrix_size_A, matrix_size_B);

    for (int i = 0; i < max(Matrix_A[0].cols_num, Matrix_B[0].cols_num); i++) {
        printf("%d ", max_arr[i]);
    }
    printf("\n");


    free(Matrix_A);
    free(Matrix_B);
    return 0;
}