#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int *arr, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        int min = arr[i], minIndex = i,temp;
        for (int j = i + 1; j < arrSize; j++) {
            if(min > arr[j]) {
                min = arr[j];
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = min;
        arr[minIndex] = temp;
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
    selectionSort(arr, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
}