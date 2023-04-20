#include <stdio.h>
#include <stdlib.h>

typedef struct polynomial polynomial;
typedef struct polynomial *polynomialPointer;
typedef struct polynomial {
    int exp;
    int coef;
    polynomialPointer next;
} polynomial;

polynomialPointer poly = NULL;
polynomialPointer avail = NULL;

polynomialPointer getNode(int exp, int coef) {
    if (avail) {
        polynomialPointer temp = avail;
        avail = avail->next;
        return temp;
    } else {
        polynomialPointer new = (polynomialPointer) malloc(sizeof(polynomial));
        new->exp = exp;
        new->coef = coef;
        new->next = NULL;
        return new;
    }
}

void addPolynomial(int exp, int coef) {
    polynomialPointer temp = poly;
    polynomialPointer pre = NULL;
    if (temp) {
        while (1) {
            if (temp) {
                if (temp->exp == exp) {
                    temp->coef += coef;
                    break;
                } else if (temp->exp < exp) {
                    if (pre) {
                        pre->next = getNode(exp, coef);
                        pre->next->next = temp;
                    } else {
                        poly = getNode(exp, coef);
                        poly->next = temp;
                    }
                    break;
                }
            } else {
                pre->next = getNode(exp, coef);
                break;
            }
            pre = temp;
            temp = temp->next;
        }
    } else {
        poly = getNode(exp, coef);
    }
}

void returnNode(polynomialPointer node) {
    node->next = avail;
    avail = node;
}

void removePoli(int exp) {
    polynomialPointer temp = poly;
    polynomialPointer pre = NULL;
    while(temp) {
        if(temp->exp == exp) {
            if(pre) {
                pre->next = temp->next;
            }else {
                poly = temp->next;
            }
            returnNode(temp);
            return;
        }
        pre = temp;
        temp= temp->next;
    }
}

void printAvailCount() {
    polynomialPointer temp = avail;
    int count = 0;
    while (temp) {
        count++;
        temp = temp->next;
    }
    printf("avail count: %d\n", count);
}

void printPolynomial() {
    polynomialPointer temp = poly;
    while (temp) {
        if (temp->next) {
            printf("%dx^%d + ", temp->coef, temp->exp);
        } else {
            printf("%dx^%d\n", temp->coef, temp->exp);
        }
        temp = temp->next;
    }
}

void printAllStatus() {
    printPolynomial();
    printAvailCount();
}

int main(void) {
    addPolynomial(1, 2);
    printAllStatus();
    addPolynomial(2, 2);
    printAllStatus();
    addPolynomial(0, 5);
    printAllStatus();
    addPolynomial(100, 5);
    printAllStatus();
    addPolynomial(2, 2);
    printAllStatus();
    removePoli(2);
    printAllStatus();
    removePoli(1);
    printAllStatus();
    addPolynomial(2, 2);
    printAllStatus();
    removePoli(100);
    printAllStatus();
    return 0;
}