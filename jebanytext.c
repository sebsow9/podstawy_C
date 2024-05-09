#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>



#define BUFFER_SIZE 1024


void bubbleSort(char* arr[], int n, int index) {
    int i, j; 
    char* temp = NULL;
    for (i = 0; i < n-1; i++) {
        
        for (j = 1; j < n-i-1; j++) {
            if (((int) arr[j][index]) > ( (int) arr[j+1][index])) {
                
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void sort(char tab[], int index){
    char* line[BUFFER_SIZE];
    int line_index = 0;
    int current_line = 0;

    line[current_line] = malloc(BUFFER_SIZE);

        if(line[current_line] == NULL){
            printf("Critical error");
        }

        for (int i = 0; i <= index; i++){

            if(tab[i] == '\n' || tab[i] == '\0'){

                line[current_line][line_index] = '\0';

                if(tab[i] == '\n' && i != index -1){

                    current_line++;
                    line_index = 0;

                    line[current_line] = malloc(BUFFER_SIZE);

                    if(line[current_line] == NULL) {
                        printf("Critical error");
                        break;
                        }


                }
            }

            else{

                line[current_line][line_index++] = tab[i];

            }
        }

    int i=0;
    int j=0;/* tu jest ile slow ma 1 wiersz*/
    int k =0;
    char words_1line[15][15];
    int words_len[3];
    while (line[0][i] != '\0')
    {
        if(line[0][i] == ' '){
            words_len[j] = k-1;
            j++;
            i++;
            
            k=0;
            
        }
        else{
            words_1line[j][k] = line[0][i];
            i++;
            k++;
        }  
    }
    words_len[j] = k-1;
    if (j == 0){

        bubbleSort(line, current_line + 1, 0);
        for(int i = 1; i<=current_line; i++){

            printf("%s\n", line[i]);

        }
    }
    if (j == 1){
        regex_t regex;
        int ret;
        ret = regcomp(&regex, "-k[[:digit:]]+", REG_EXTENDED);
        
        ret = regexec(&regex, line[0], 0, NULL, 0);
        if(ret == 0){
            int k = words_len[1];
            char temp[k];
            int i = 0;
            while (i+1 != k)
            {   
                temp[i] = words_1line[1][i+2];
                i++;
            }
            int number = atoi(temp);

            bubbleSort(line, current_line + 1, number-1);
            
            for(int i = 1; i<=current_line; i++){

                printf("%s\n", line[i]);

            }
        }


            

        

        regfree(&regex);
    }
    

    
    for (int i = 0; i <= current_line; i++) {

            free(line[i]);

        }

}



int fun_define(char* tab){
    
    regex_t regex;
    int ret;
    char words[15][7] = {};
    int i =0;
    int j =0;
    int k = 0;
    while (tab[i] != '\0'){
        
        words[j][k] = tab[i];
        i++;
        k++;
        if(tab[i] == ' '){
            words[j][k-1] = '\0';
            j++;
            i++;
            k=0; 
        } 
    }
    ret = regcomp(&regex, words[0], 0);
    if (ret != 0) {
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        printf("Regex compilation failed: %s\n", error_message);
        return -1;
    }

    ret = regexec(&regex, "grep", 0, NULL, 0);
    if (ret == 0) {
        regfree(&regex);
        return 1;
    }

    ret = regexec(&regex, "tail", 0, NULL, 0);
    if (ret == 0) {
        regfree(&regex);
        return 2;
    }

    ret = regexec(&regex, "sort", 0, NULL, 0);
    if (ret == 0) {
        regfree(&regex);
        return 3;
    }

    
    regfree(&regex);
    
    printf("No pattern found\n");
    return -1;
}




int main(){
    char buffer[BUFFER_SIZE];
    char* line[BUFFER_SIZE];
    int line_index;
    int current_line;
    int index;
    while(1){
        line_index = 0;
        current_line = 0;
        index = 0;
        printf("Podaj komende: \n");
        

        int ch = 0;
        while(index < BUFFER_SIZE - 1 && (ch=getchar()) != EOF){
            buffer[index++] = (char)ch;
        }
        buffer[index] = '\0';
        if(index == 0 && ch == EOF){
            printf("Koniec programu!\n");
            break;
        }
        
        
        line[current_line] = malloc(BUFFER_SIZE);

        if(line[current_line] == NULL) return -1;

        for (int i = 0; i <= index; i++){

            if(buffer[i] == '\n' || buffer[i] == '\0'){

                line[current_line][line_index] = '\0';

                if(buffer[i] == '\n' && i != index -1){

                    current_line++;
                    line_index = 0;

                    line[current_line] = malloc(BUFFER_SIZE);

                    if(line[current_line] == NULL) return -1;

                }
            }

            else{

                line[current_line][line_index++] = buffer[i];

            }
        }
        int function = fun_define(line[0]);
        switch (function){
            case -1:
                break;
            case 1:
                printf("\nGrep\n");
                break;
            case 2:
                printf("\nTail\n");
                break;
            case 3:
                printf("\nSort\n");
                sort(buffer, index);
                break;


        }
        for (int i = 0; i <= current_line; i++) {

            free(line[i]);

        }
        
        clearerr(stdin);

    }
    

    
    return 0;
}
