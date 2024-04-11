#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 5


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



int* suma(int* A, int* B){
    int* sum = malloc(sizeof(int) * (MAX_SIZE * 2));
    if (sum == NULL) {
        exit(1); 
    }
    for (int i = 0; i < MAX_SIZE; ++i) {
        sum[i] = A[i];
        sum[i + MAX_SIZE] = B[i];
    }
    return sum;
}

int* common_part(int* A, int* B,int* result_size){
    int* common = malloc(sizeof(int) * (MAX_SIZE));
    if (common == NULL) {
        exit(1); 
    }
    int common_size = 0;
    for(int j = 0; j< MAX_SIZE; j++){
        for (int g = 0; g< MAX_SIZE; g++){
            int already_exist = 0;
            if (A[j] == B[g]){
                for (int x = 0; x <=common_size; x++){
                    if (common[x] == A[j]){
                        already_exist = 1;
                    }
                }
                if(already_exist == 0){
                    common[common_size] = A[j];
                    common_size++;
                }       
            }
        }
    }
    *result_size = common_size;
    return common;
}

int* difference(int* A, int* B, int* result_size){
    int* diff = malloc(sizeof(int) * (MAX_SIZE));
    if (diff == NULL) {
        exit(1); 
    }
    int diff_size = 0;
    
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            diff[diff_size] = A[j];
            diff_size++;
        }
    }


    *result_size = diff_size;
    return diff;
}
int* sym_diff(int* A, int* B, int* result_size){
    int* sym = malloc(sizeof(int) * (MAX_SIZE));
    if (sym == NULL) {
        exit(1); 
    }
    int sym_size = 0;
    
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            sym[sym_size] = A[j];
            sym_size++;
        }
    }
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (B[j] == A[g]){
                flag = 0;
            }      
        }
        if (flag == 1){
            sym[sym_size] = B[j];
            sym_size++;
        }
    }
    *result_size = sym_size;
    return sym;
}
bool is_equal(int* A, int* B){
    int size_arr = 0;
    for(int j = 0; j< MAX_SIZE; j++){
        int flag = 1;
        for (int g = 0; g< MAX_SIZE; g++){
            if (A[j] == B[g]){
                flag = 0;
            }      
        }
        if (flag == 0){
            size_arr++;
        }
    }
    if (size_arr == MAX_SIZE){
        return true;
    }
    else{
        return false;
    }
}

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



int main(void){
    int* result_list[4];
    bool result_bool[2]; 
    int** A_B_list[6];
    int result_sizes[4] = {0}; 
    int size;
    int eofEncountered = 0;
    int i = 1;
    int operation_number[6];
    printf("Podaj elementy tablicy A i B oraz numer operacji: \n");
    while (!eofEncountered && i <= 6){

        A_B_list[i-1] = read(&operation_number[i-1], &eofEncountered);
        i++;
        }
        for (int j=0; j<=i-1;j++){
            switch (operation_number[j]){
            case 1:
                result_list[0] = suma(A_B_list[j][0], A_B_list[j][1]);
                printf("\nWynik 1 operacji: ");
                for(int y = 0; y<MAX_SIZE*2; y++){
                    printf(" %d", result_list[0][y]);
                }
                
                break;
            case 2:
                result_list[1] = common_part(A_B_list[j][0], A_B_list[j][1], &size);
                result_sizes[1] = size;
                printf("\nWynik 2 operacji: ");
                for(int f = 0; f<result_sizes[1]; f++){
                    printf(" %d", result_list[1][f]);
                }
                
                break;
            case 3:
                result_list[2] = difference(A_B_list[j][0], A_B_list[j][1], &size);
                result_sizes[2] = size;
                printf("\nWynik 3 operacji: ");
                for(int h = 0; h<result_sizes[2]; h++){
                    printf(" %d", result_list[2][h]);
                }
                
                break;
            case 4:
                result_list[3] = sym_diff(A_B_list[j][0], A_B_list[j][1], &size);
                result_sizes[3] = size;
                printf("\nWynik 4 operacji: ");
                for(int k = 0; k<result_sizes[3]; k++){
                    printf(" %d", result_list[3][k]);
                }
                
                break;
            case 5:
                result_bool[0] = is_equal(A_B_list[j][0], A_B_list[j][1]);
                printf("\nWynik 5 operacji: ");
                if (result_bool[0] == true){
                    printf(" Tablice sa rowne");
                }
                else{
                    printf(" Tablice nie sa rowne");
                }
                break;
            case 6:
                int relation = checkSetsRelation(A_B_list[j][0], A_B_list[j][1]);
                printf("\nWynik 6 operacji: ");
                switch (relation)
                {
                case 0:
                    printf("Zbiory sa rowne");
                    break;
                case 1:
                    printf("Zbior A zawiera sie w zbiorze B");
                    break;
                case 2:
                    printf("Zbior B zawiera sie w zbiorze A");
                    break;
                case 3:
                    printf("Zbiory nie sa rowne");
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
    for (int i = 0; i < 6; i++) {
        free(A_B_list[i][0]);
        free(A_B_list[i][1]);
        free(A_B_list[i]);
    }
    for (int i = 0; i < 6; i++) {
        free(result_list[i]);
    }
    

    
    return 0;
}
