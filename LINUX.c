#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>



#define BUFFER_SIZE 1024


void bubbleSort(char* arr[], int n, int index, int flag, int start_flag_2) {
    char first_numbers[15][15];
    int act_numbers[15];
    if (flag == 1){
        int g, flaggy;
            
            for(int f=1; f<n; f++){
                g=0;
                flaggy = 0;
                while(flaggy != 1){
                    if (arr[f][g] == ' ' || arr[f][g] == '\n' || arr[f][g] == '\0'){
                        flaggy = 1;    
                    }
                    first_numbers[f][g] = arr[f][g];
                    g++;
                }
                act_numbers[f] = atoi(first_numbers[f]);
            }
    }
    if (flag == 2){
        printf("1 flaga\n");
        int g, flaggy, letter;
            for(int f=1; f<n; f++){
                g=start_flag_2-1;
                flaggy = 0;
                letter = 0;
                while(flaggy != 1){
                    printf("2 flaga\n");
                    
                    if (arr[f][g] == ' ' || arr[f][g] == '\n' || arr[f][g] == '\0'){
                        flaggy = 1;    
                    }
                    first_numbers[f][letter] = arr[f][g];
                    
                    g++;
                    letter++;
                }
                act_numbers[f] = atoi(first_numbers[f]);
                printf("Gowno : %d\n", act_numbers[f]);
            }
    }



    int i, j; 
    char* temp = NULL;

    if (flag == 0){
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
    else if (flag == 1 || flag == 2){
        int temp1 = 0;
        for (i = 0; i < n-1; i++) {
            
            for (j = 1; j < n-i-1; j++) {
                if ((act_numbers[j]) > (act_numbers[j+1])) {
                    
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    temp1 = act_numbers[j];
                    act_numbers[j] = act_numbers[j+1];
                    act_numbers[j+1] = temp1;
                }
            }
        }
    }
}
int has_option(const char *options, char option) {
    return strchr(options, option) != NULL;
}
void grep_function(char* arr[], int size, const char *options, const char *pattern) {
    regex_t regex;
    int cflags = REG_EXTENDED;
    if (has_option(options, 'i')) {
        cflags |= REG_ICASE;
    }

    if (regcomp(&regex, pattern, cflags) != 0) {
        printf("Could not compile regex\n");
        return;
    }

    int match_count = 0;
    for (int i = 1; i < size; i++) {  // start from 1 to skip the first line with options
        regmatch_t match;
        if (regexec(&regex, arr[i], 1, &match, 0) == 0) {
            if (has_option(options, 'w')) {
                if ((match.rm_so > 0 && !isspace(arr[i][match.rm_so - 1]) && arr[i][match.rm_so - 1] != '\n') ||
                    (arr[i][match.rm_eo] != '\0' && !isspace(arr[i][match.rm_eo]) && arr[i][match.rm_eo] != '\n')) {
                    continue;  // Not a whole word match
                }
            }
            
            match_count++;

            if (has_option(options, 'c')) {
                continue;  // Only count matches
            }

            if (has_option(options, 'n')) {
                printf("%d: ", i);  // Print line number
            }

            printf("%s\n", arr[i]);
        }
    }

    if (has_option(options, 'c')) {
        printf("Count of matching lines: %d\n", match_count);
    }

    regfree(&regex);
}
void parse_and_execute_grep(char* arr[], int size) {
    if (size == 0) return;

    char *options = "";
    char *pattern = arr[0];  // Default to the whole first line as a pattern

    char *token = strtok(arr[0], " ");
    if (token && strcmp(token, "grep") == 0) {
        char *next_token = strtok(NULL, " ");
        if (next_token && next_token[0] == '-') {
            options = next_token + 1;  // Skip the dash to point to options
            pattern = strtok(NULL, "\n");  // Get the pattern after options
        } else {
            pattern = next_token;  // No options, just the pattern
        }
    }

    if (!pattern) {
        printf("Invalid grep command format. No pattern provided.\n");
    } else {
        grep_function(arr, size, options, pattern);
    }
}
void print_tail(char* tab[], int size, int start, char mode) {
    if (mode == 'n') {  
        int startLine = size - start;
        if (startLine < 0) startLine = 0;
        for (int i = startLine; i < size; i++) {
            printf("%s\n", tab[i]);
        }
    } else if (mode == 'c') {  
        int char_count = 0;
        for (int i = size - 1; i >= 0 && char_count < start; i--) {
            int len = strlen(tab[i]);
            if (char_count + len < start) {
                printf("%s\n", tab[i]);
                char_count += len + 1;  
            } else {
                int startIndex = len - (start - char_count);
                printf("%s\n", &tab[i][startIndex]);
                break;
            }
        }
    } else if (mode == '+') {  
        for (int i = start; i < size; i++) {
            printf("%s\n", tab[i]);
        }
    }
}
void tail_function(char* tab[], int size) {
    char *options = tab[0];
    int count = 10;  // Default line count if not specified
    char mode = 'n'; // Default mode, show last 'n' lines

    // Parse options, assuming the first element 'tab[0]' contains them
    if (strncmp(options, "tail -n ", 8) == 0) {
        count = atoi(options + 8); // Parse number directly after '-n'
    } else if (strncmp(options, "tail -c ", 8) == 0) {
        mode = 'c'; // Set mode to count characters instead
        count = atoi(options + 8); // Parse number directly after '-c'
    } else if (options[0] == '+') {
        mode = '+'; // Set mode to start output from 'count' line
        count = atoi(options + 1) - 1; // Parse number directly after '+', convert to 0-based index
    }

    // Based on mode, print lines or characters from tail
    if (mode == 'n') {
        int start = size - count;
        if (start < 0) start = 0;
        for (int i = start; i < size; i++) {
            printf("%s\n", tab[i]);
        }
    } else if (mode == 'c') {
        // Count and output characters: similar implementation needed
    } else if (mode == '+') {
        for (int i = count; i < size; i++) {
            printf("%s\n", tab[i]);
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
    int p =0;
    char words_1line[15][15];
    int words_len[3];
    while (line[0][i] != '\0')
    {
        if(line[0][i] == ' '){
            words_len[j] = p-1;
            j++;
            i++;
            
            p=0;
            
        }
        else{
            words_1line[j][p] = line[0][i];
            i++;
            p++;
        }  
    }
    words_len[j] = p-1;
    if (j == 0){

        bubbleSort(line, current_line + 1, 0, 0, 0);
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

            bubbleSort(line, current_line + 1, number-1, 0, 0);
            
            for(int i = 1; i<=current_line; i++){

                printf("%s\n", line[i]);

            }
        }
        ret = regcomp(&regex, "-n", REG_EXTENDED);
        ret = regexec(&regex, line[0], 0, NULL,0);
        if(ret==0){
            
            bubbleSort(line, current_line+1, 0, 1, 0);
            for(int i = 1; i<=current_line; i++){
                printf("%s\n", line[i]);
            }
            
        }
        
        regfree(&regex);
    }
    if(j==2){
        int h=0;
        int m = 0;
        char start_int[15];
        int start;
        while(line[0][h] != 'k'){
            h++;
        }
        h++;
        while(line[0][h] != ' '){
            
            start_int[m] = line[0][h];
            m++;
            h++;
            
        }
        start = atoi(start_int);
        printf("%d", start);
        
        bubbleSort(line, current_line+1, 0, 2, start);
        for(int i = 1; i<=current_line; i++){
            printf("%s\n", line[i]);
        }
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

void run_tests() {
    // Example Test for Grep
    char *grep_lines[] = {
        "grep -n test",
        "This is a test",
        "Another line",
        "test again",
        "no match"
    };
    printf("Testing Grep Function:\n");
    grep_function(grep_lines, 4, "n", "test");  // Should print line numbers with 'test'

    // Example Test for Tail
    char *tail_lines[] = {
        "tail -n 2",
        "line 1",
        "line 2",
        "line 3"
    };
    printf("\nTesting Tail Function:\n");
    tail_function(tail_lines, 4);  // Should print last two lines: "line 2" and "line 3"

    // Example Test for Sort
    char sort_input[] = "sort\n3 Banana\n1 Apple\n2 Cherry";
    printf("\nTesting Sort Function:\n");
    sort(sort_input, strlen(sort_input));  // Should sort the lines alphabetically
}




int main(int argc, char *argv[]){
    if (argc>1 &&strcmp(argv[1], "test") == 0){
        run_tests();
    }
    else{
        printf("Normalne dzialanie progoramu: \n\n\n");
    
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
                printf("\nGrep\n\n");
                parse_and_execute_grep(line, current_line+1);
                break;
            case 2:
                printf("\nTail\n\n");
                tail_function(line, current_line+1);
                break;
            case 3:
                printf("\nSort\n\n");
                sort(buffer, index);
                break;


        }
        for (int i = 0; i <= current_line; i++) {

            free(line[i]);

        }
        
        clearerr(stdin);

    }
    

    }
    return 0;
}
