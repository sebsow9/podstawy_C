#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <string.h>
#define N 10  

typedef struct {
    int items[N];
    int front;
    int rear;
    int size;
} Queue;

void Queue__init(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int Queue__push(Queue *q, int number) {
    if (q->size == N) {
        return -1;
    }
    q->items[q->rear] = number;
    q->rear = (q->rear + 1) % N;
    q->size++;
    return 0;
}

int Queue__pop(Queue *q) {
    if (q->size == 0) {
        return -2;
    }
    int item = q->items[q->front];
    q->front = (q->front + 1) % N;
    q->size--;
    return item;
}

void RadixSort(int arr[], int n) {
    Queue queues[10]; 
    for (int i = 0; i < 10; i++) {
        Queue__init(&queues[i]);
    }

    
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        
        for (int i = 0; i < n; i++) {
            int bucket = (arr[i] / exp) % 10;
            Queue__push(&queues[bucket], arr[i]);
        }

        
        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (queues[i].size != 0) {
                arr[index++] = Queue__pop(&queues[i]);
            }
        }
    }
}

int fill(int arr[], char* argv[], int argc){
    for(int i = 0; i < argc-1; i++){
        arr[i] = atoi(argv[i+1]);
    }
}

int main(int argc, char *argv[]) {
    int arr[argc-1];
    fill(arr, argv, argc);
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    RadixSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
