#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 16
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int Stack__push(int stack[], int number){
    
    if(stack[0] == N){
        return -1;
    }
    else{
        stack[0]++;
        stack[stack[0]] = number;
        return 0;
    }
}


int Stack__pop(int stack[]){
    if(stack[0] > 0){
        int temp = stack[stack[0]];
        for(int i=stack[0]; i < N; i++){
            stack[i] = stack[i+1];
        }
        
        stack[0]--;
        return temp;
    }
    else{
        return -2;
    }
        
}

void Stack__print(int stack[]){
    for(int i = 1; i<=stack[0]; i++){
        printf(" %d", stack[i]);
    }
    printf("\n");
}


int* check_parenteses(int stack[], char* argv[], int argc, int map[]){
    int nawiasy[argc-1];
    for(int i =1; i<argc; i++){
        if(strcmp(argv[i], "(") == 0){
            Stack__push(stack, 2);
            nawiasy[i-1] = 2;
        }
        else if(strcmp(argv[i], "{") == 0){
            Stack__push(stack, 12);
            nawiasy[i-1] = 12;
        }
        else if(strcmp(argv[i], "[") == 0){
            Stack__push(stack, 8);
            nawiasy[i-1] = 8;
        }
        else{
            nawiasy[i-1] = 0;
        }
    }
    for(int j=1; j<argc; j++){
        if(strcmp(argv[j], ")") == 0){
            if(Stack__pop(stack) == 2);{
                
                nawiasy[j-1] = 3;
            }
        }
        else if(strcmp(argv[j], "}") == 0){
            if(Stack__pop(stack) == 12);{
                
                nawiasy[j-1] = 13;
            }
            
        }
        else if(strcmp(argv[j], "]") == 0){
            if(Stack__pop(stack) == 8);{
                nawiasy[j-1] = 9;
            }
        }
    }
    
    for(int i = 0; i<argc-1; i++){
        map[i] = 0;
    }
    for(int i = 0; i<argc-1; i++){
        int number = nawiasy[i];
        
        if(number != 0 && map[i]!=1 && map[i]!=2){
            map[i] = 1;
            for(int g = i+1; g<argc-1; g++){
                
                if(number - nawiasy[g] == -1){
                    map[g] = 2;
                    map[i] = 0;
                    break;
                }
                
                
                if(number == nawiasy[g] && number%2 == 0){
                    map[g] = 1;
                }
                else if(number == nawiasy[g] && number%2 == 1){
                    map[i] = 1;
                }
                    
                
            }
        }
        else if(map[i] == 2){
            for(int g = i+1; g<argc-1; g++){
                if(number - nawiasy[g] == 1){
                    break;
                }

                if(number == nawiasy[g]){
                    map[i] = 1;
                    map[g] = 2;
                }
            }
        }

    }
    for(int i = 0; i<argc-1; i++){
        if(map[i]==2){
            map[i] = 0;
        }
    }
    

    return map;
}




int main(int argc, char *argv[]){
    int stack[N+1];
    stack[0] = 0;
    int map[argc - 1];
    check_parenteses(stack, argv, argc, map);
    printf("\n");
    //Stack__print(stack);
    for(int i = 0; i<argc-1; i++){
        printf(" %d", map[i]);
    }
    printf("\n");
    for(int i = 1; i<argc; i++){
        if(map[i-1] == 1){
            printf(RED" %s" RESET, argv[i]);
        }
        else{
            printf(" %s", argv[i]);
        }
        
        
    }
    printf("\n");






    return 0;
}
