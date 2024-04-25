#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int divideAndRoundUp(int numerator, int denominator) {
    if (denominator == 0) {
        printf("Dzielnik nie moze byc zerem\n");
        return -1;
    }
    return (numerator + denominator - 1) / denominator;
}




void max_heap(int* tab, int parent, int size){
    int left_index = parent * 2 + 1;
    int right_index = parent * 2 + 2;
    int largest = parent;

    
    if (left_index < size && tab[left_index] > tab[largest]) {
        largest = left_index;
        
    }

   
    if (right_index < size && tab[right_index] > tab[largest]) {
        largest = right_index;
    }

    
    if (largest != parent) {
        int temp = tab[parent];
        tab[parent] = tab[largest];
        tab[largest] = temp;
        if(left_index < size){
            max_heap(tab, left_index, size);
        }
        if(right_index < size){
            max_heap(tab, right_index, size);
        }
        
    }
}




void heapify(int* tab, int size){
    for(int i = divideAndRoundUp(size, 2) - 1; i>-1; i--){
        max_heap(tab, i, size);
        
    }
}




int main(int argc, char *argv[])
{
    int trackingEnabled = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--track") == 0) {
            trackingEnabled = 1;
            break;
        }
    }
    int N;

    printf("Podaj ilosc liczb do sortowania: ");
    scanf("%d", &N);
    
    while (getchar() != '\n'){}
    
    int heap[N];
    int sorted[N];
    for(int i=0; i<N; i++){
        heap[i] = (rand()%20)-10;
    }
    if(trackingEnabled){
        for(int i=0; i<N/2; i++){
            printf("    ");
        }
        printf("heap");
        for(int i=0; i<N/2; i++){
            printf("     ");
        }
        printf("sorted\n");
        for(int i=0; i<N/2; i++){
            printf("--------------");
        }
        printf("\n");
        printf("Krok 0 ");
        for(int i=0; i<N; i++){
            if(heap[i]>=0){
                printf(" %d ", heap[i]);
            }
            else{
                printf("%d ", heap[i]);
            }
            
        }
        for(int i=0; i<N; i++){
            printf("   ");
        }
        printf("  <- Wylosowane Dane\n");
    }
    heapify(heap, N);
    if(trackingEnabled){
        printf("Krok 1 ");
        for(int i=0; i<N; i++){
            if(heap[i]>=0){
                printf(" %d ", heap[i]);
            }
            else{
                printf("%d ", heap[i]);
            }
        }
        for(int i=0; i<N; i++){
            printf("   ");
        }
        printf("  <- Utworzenie kopca\n");
    }
    //sortujemy
    for(int i=0; i<N; i++){
        sorted[i] = heap[0];
        heap[0] = heap[N-i-1];
        heapify(heap, N-i-1);
        if(trackingEnabled){
            if(i+2>=10){
                printf("Krok %d", (i+2));
            }
            else{
                printf("Krok %d ", (i+2));
            }
                
            for(int f=0; f<i+1; f++){
                printf("   ");
            }
            for(int g=0; g<N-i-1; g++){
                
                if(heap[g]>=0){
                    printf(" %d ", heap[g]);
                }
                else{
                    printf("%d ", heap[g]);
                }
            }
            for(int f=0; f<N-i-1; f++){
                    printf("   ");
                }
            for(int j=0; j<=i; j++){
                
                if(sorted[j]>=0){
                    printf(" %d ", sorted[j]);
                }
                else{
                    printf("%d ", sorted[j]);
                }
            }
            printf("  <- Przeniesienie wierzchołka kopca do tablicy sorted oraz odtworzenie porządku kopcowego\n");
        }
        
    }

    
    
    return 0;
    
}