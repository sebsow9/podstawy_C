#include <stdio.h>
#include <stdlib.h>
#include "operations.h"


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