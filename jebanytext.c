#include <stdlib.h>
#include <stdio.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100


int main(){
    FILE *file;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINES];
    int line_count = 0;
    file = fopen("maka.txt", "r");
    if (file == NULL){
        perror("Error opening file");
        return -1;
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        lines[line_count] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));


        int i = 0;
        while (buffer[i] != '\0' && buffer[i] != '\n' && i <MAX_LINE_LENGTH){
            lines[line_count][i] = buffer[i];
            i++;
        }

        lines[line_count][i] = '\0';
        line_count++;

        if(line_count >= MAX_LINES){
            printf("Maximum reached");
            break;
        }
    }
    


    for (int i = 0; i< line_count; i++){
        printf("%s", lines[i]);
        free(lines[i]);
    }
    
    
    fclose(file);
    return 0;
}
