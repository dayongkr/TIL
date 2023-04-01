# 문제해결 5주 차

## Dynamic Memory Allocation

runtime에 memory를 할당하는 방법을 Dynamic Memory Allocation이라고 한다.

- static memory allocation
  - compile time에 memory를 할당한다.
  - global variable
- automatic memory allocation
  - compile time에 memory를 할당한다.
  - local variable

``` c
#include <stdlib.h>
int * ptr = (int *)malloc(size_t size);
free(ptr);
```

C에서는 `malloc`이라는 함수를 통해 Dynamic Memory Allocation을 할 수 있다. free로 해제를 하는데 OS에 Dynamic Memory Allocation에 대한 정보를 가지고 있어 따로 크기를 지정해주지 않아도 된다.

### Common Mistakes

- sizeof는 data type에 대한 크기를 알려주기 때문에 포인터 변수에 정수 배열이 있더라도 sizeof(ptr) = sizeof(int *)과 같다.
- Dangling pointers
  - free한 pointer를 다시 사용하는 경우

### malloc for structure

``` c
typedef struct node {
  int data;
} node;

node * ptr = (node *)malloc(sizeof(node));
printf("%d\n", ptr->data); // (*ptr).data
```

arrow를 사용하면 좀 더 명확하게 동적할당된 구조체의 멤버에 접근할 수 있다.

### malloc for 2D Array

``` c
// malloc for 2D array
int ** ptr = (int **)malloc(sizeof(int *) * n);
for (int i = 0; i < n; i++) {
  ptr[i] = (int *)malloc(sizeof(int) * m);
}
// free 2D array
for (int i = 0; i < n; i++) {
  free(ptr[i]);
}
free(ptr);
```

포인터 변수를 가르키는 포인터 변수(`int **`)를 사용해 2차원 배열을 동적할당할 수 있다.

## Preprocessor

컴파일러가 컴파일하기 전에 미리 처리하는 것을 Preprocessor라고 한다. Preprocessor directive를 처리하는 과정으로 directive는 `#include`, `#define`, `#ifdef` 등이 있다.

### \#include

``` c
#include <stdio.h>
#include "myheader.h"
```

`#include <stdio.h>`는 표준 라이브러리에 있는 헤더 파일을 포함시키는 것이고 `#include "myheader.h"`는 현재 디렉토리에 있는 헤더 파일을 포함시키는 것이다.

### \#define

identifier를 정의한다. const 변수와 비슷하지만 const 변수는 compile time에 정의되고 `#define`은 compile time이 아닌 preprocess time에 정의된다.

``` c
#define PI 3.141592
```

이를 통해 명확하게 PI를 사용할 수 있다.

``` c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int a = MAX(1, 2); // 2
```

값만 정의할 수 있는 건 아니라 함수 및 연산자도 정의할 수 있다.

### \#ifdef

``` c
#ifdef DEBUG
  printf("debugging\n");
#endif
```

`#ifdef`는 identifier가 정의되어 있는지 확인한다. `#ifndef`는 identifier가 정의되어 있지 않은지 확인한다.

## Bitwise Tricks

- 2의 power를 곱하거나 나누는 경우
  - `<<` : 곱하기 2
  - `>>` : 나누기 2
- XOR swap
  - `a ^= b; b ^= a; a ^= b;`
- ith bit set
  - `x |= (1 << i)`
  - ith bit가 1이 되도록 한다.
- ith bit unset
  - `x &= ~(1 << i)`
  - ith bit가 0이 되도록 한다.
- ith bit toggle
  - `x ^= (1 << i)`
  - ith bit가 반전된다.
- ith bit check
  - `x & (1 << i)`
  - ith bit가 1인지 확인한다.
