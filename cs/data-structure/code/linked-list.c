#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int data;
    struct listNode *next;
} listNode;

typedef struct listNode *listPointer;

listPointer new(void)
{
    return (listPointer)malloc(sizeof(listNode));
}

listPointer append(const listPointer node, int data)
{
    listPointer temp = node;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new ();
    temp->next->data = data;
}

void printList(const listPointer node)
{
    listPointer temp = node;
    while (temp)
    {
        if (temp->data || temp->data == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

listPointer invert(const listPointer node)
{
    listPointer middle, trail, head = node;
    middle = NULL;
    while (head)
    {
        trail = middle;
        middle = head;
        head = head->next;
        middle->next = trail;
    }
    return middle;
}

listPointer concat(const listPointer l, const listPointer r)
{
    listPointer tempL = l;
    if (!l)
        return r;
    if (!r)
        return l;

    while (tempL->next)
    {
        tempL = tempL->next;
    }
    tempL->next = r;
    return l;
}

void insertFront(listPointer *node, int data)
{
    listPointer head = new ();
    head->data = data;
    head->next = *node;
    *node = head;
}

int main(void)
{
    listPointer list = (listPointer)malloc(sizeof(listNode));
    list->data = 30;
    append(list, 10);
    append(list, 10);
    append(list, 10);
    append(list, 10);

    printf("append\n");
    printList(list);

    printf("invert\n");
    list = invert(list);
    printList(list);

    listPointer list2 = (listPointer)malloc(sizeof(listNode));
    list2->data = 30;
    append(list2, 20);
    append(list2, 20);
    append(list2, 20);
    append(list2, 20);
    concat(list, list2);

    printf("concat\n");
    printList(list);

    printf("insertFront\n");
    insertFront(&list, 40);
    printList(list);
}
