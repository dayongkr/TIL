#include <stdio.h>
#include <string.h>

char tempStr[1000] = "aabcddaabbaabcddaabc";
int failureTable[1000] = {0,};

int main(void) {
    int size = strlen(tempStr), find= 0;
    failureTable[0] = -1;
    for (int i = 1; i < size; i++) {
        int failureIndex = i-1;
        find = 0;
        while (failureIndex != -1) {
            failureIndex = failureTable[failureIndex];
            if (tempStr[failureIndex + 1] == tempStr[i]) {
                find = 1;
                break;
            }
        }
        failureTable[i] = find ? failureTable[i] = failureIndex + 1 : failureIndex;

    }
    for (int i = 0; i < size; i++) {
        printf("%d ", failureTable[i]);
    }
    return 0;
}