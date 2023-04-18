// zero-indexed

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

typedef struct node {
    int value;
    node *next;
} node;


void printLinkedList(const node *linkedList) {
    node *temp = linkedList;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

node *createNode(int value) {
    node *new = (node *) malloc(sizeof(node));
    new->next = NULL;
    new->value = value;
    return new;
}

void linkNode(node *linkedList, int value) {
    node *temp = linkedList;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = createNode(value);
}

void unlinkNode(node *linkedList, int index) {
    node *temp = linkedList;
    node *target;
    if (index == 0) {
        *linkedList = *temp->next;
    } else {
        index--;
        while (temp->next != NULL && index > 0) {
            temp = temp->next;
            index--;
        }
        if (!index) {
            target = temp->next;
            temp->next = temp->next->next;
            free(target);
        }
    }
}

int pop(node *linkedList) {
    int result;
    node *temp = linkedList;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    result = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    return result;
}

int main(void) {
    node *linkedList = createNode(0);
    linkNode(linkedList, 1);
    linkNode(linkedList, 2);
    unlinkNode(linkedList, 0);
    linkNode(linkedList, 1);
    linkNode(linkedList, 2);
    linkNode(linkedList, 3);
    printLinkedList(linkedList);
    printf("pop: %d\n", pop(linkedList));
    printLinkedList(linkedList);
}