#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *arr, int arrSize) {
    for (int i = 1; i < arrSize; i++) {
        int key = arr[i];
        int emptyIndex = i;
        for(int j = i-1; j >= 0; j--) {
            if(arr[j] > key) {
                arr[emptyIndex] = arr[j];
                emptyIndex = j;
            }
        }
        arr[emptyIndex] = key;
    }
}

int main(void) {
    int arr[10] = {0,};
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    insertionSort(arr, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
}