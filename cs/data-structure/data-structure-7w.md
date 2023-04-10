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

trail이 없기 때문에 first를 이용해서 x를 찾아야한다. 따라서 first가 x를 가리키고 있을 때는 바로 다음 링크를 first로 바꿔주면 된다. 아니면 first를 temp 안에 넣고 temp가 x를 가리킬 때까지 while문을 돌려서 x를 찾아야 한다. 그리고 x를 찾았을 때는 temp를 x의 다음 링크로 바꿔주면 된다. 마지막으론 free(x)를 해주면 이를 통해 x가 가리키던 메모리를 해제할 수 있다.

### Quiz 20

multiple queue에서 addq 부분을 rear 배열 없이 구현하라.

만약에 front[i]에 아무것도 없다면 front[i]를 temp로 바꿔주고, 아니라면 link가 NULL이 될 때까지 while문을 돌려서 link가 NULL이 되는 곳에 temp를 넣어준다.

### Quiz 21

polyPointer에서 특정 ptr을 찾아서 삭제하는 함수를 while문에서 for문으로 바꾸어라.

선언 부분엔 temp에 ptr을 넣어주고, 조건 부분엔 *ptr을 넣어주고 그 다음엔 temp에 또 ptr을 넣어준다. for 문 안에는 *ptr을 다음 ptr로 바꿔주고, temp를 free해준다.
