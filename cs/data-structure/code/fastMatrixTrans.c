#include <stdio.h>

#define MAX 5

typedef struct element {
    int col;
    int row;
    int value;
} element;


element arr[MAX] = {0,};
element arrT[MAX] = {0,};

int rowCount[3] = {0,};
int startPos[3] = {0,};

int main() {
    arr[0] = (element) {0, 1, 10};
    arr[1] = (element) {2, 0, 22};
    arr[2] = (element) {3, 2, 32};
    arr[3] = (element) {3, 0, 4};
    arr[4] = (element) {4, 2, 42};
    for (int i = 0; i < MAX; i++) {
        rowCount[arr[i].row]++;
    }

    for (int i = 1; i < 3; i++) {
        startPos[i] = rowCount[i - 1] + startPos[i - 1];
    }

    for (int i = 0; i < MAX; i++) {
        int temp = arr[i].col;
        arr[i].col = arr[i].row;
        arr[i].row = temp;
        arrT[startPos[arr[i].col]++] = arr[i];
    }
    for (int i = 0; i < MAX; i++) {
        printf("%d %d %d\n", arrT[i].col, arrT[i].row, arrT[i].value);
    }
};