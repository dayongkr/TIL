# 자료구조개론 7주 차

## Linked List

연속된 일반적인 Array를 사용하면 sorted list를 만들기가 어렵다. 그래서 linked list를 사용한다.

``` c
typedef struct node {
  int data;
  struct node *next;
};
```

C에서는 struct를 이용하여 linked list를 만들 수 있다. 구현 방법은 흔히 알고 있는 것과 같기 때문에 생략한다.

이러한 linked list를 개념을 사용해서 linked stack, linked queue, Polynomials등을 만들 수 있다.

pointer가 한 번 날라가면 다시 돌아올 수 없기 때문에, linked list를 사용할 때는 항상 주의해야 한다.

## Quiz

### Quiz 19

delete 함수를 수정하여 2개의 인수 first와 x만 가지고 구현하라.

