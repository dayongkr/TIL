# 문제해결 4주 차

## Symbol table

compile time에 symbol table을 만들어서 변수의 semantics를 저장한다. 여기에는 변수의 이름, 타입, scope, addresses(상대적인 주소) 등이 저장된다.

## Pointer

```c
int a = 10;
int *p = &a;
```

&(reference operator) 연산자를 사용해서 변수의 주소를 알 수 있다. *(dereference operator) 연산자를 사용해서 주소에 접근할 수 있고 pointer 변수를 선언할 수 있다.

pointer 변수는 type 상관 없이 모두 8-byte unsigned integer이다. 그런데 타입을 명시하는 이유는 disreference operator를 사용해서 해당 주소에 접근할 때 타입을 알아야 몇 개의 bytes를 읽어야 하는지 알 수 있기 때문이다.

```c
int* c,d; // c는 pointer, d는 int
```

햇갈릴 수 있는 부분이다. *는 c에 대한 type annotation이다. 따라서 c는 pointer이고 d는 int이다.

### Pointer to pointer

```c
int a = 10;
int *p = &a;
int **pp = &p;
```

이중 포인터는 포인터 변수의 주소를 저장하는 포인터이다.

### Void pointer

```c
void *p = &a;
```

void pointer는 어떤 타입의 주소이든 저장할 수 있다. 하지만 void pointer를 dereference하면 segmentation fault가 발생하기 때문에 type casting을 해줘야 한다.

```c
int a = 10;
void *p = &a;
*(int*)p = 20;
```

### Pointer arithmetic

```c
int a[5] = {1,2,3,4,5};
int *p = a;
p++; // p = p + 1
```

pointer는 int 타입이기 때문에 4-byte씩 증가한다. 따라서 p가 0이라면 p+1은 1이 아니라 4가 된다. 따라서 p[n]을 *(p+n)으로 표현할 수 있다.

> void pointer는 pointer arithmetic을 할 수 없다.

### Pointer to String

```c
char *s = "hello";
while (*s) printf("%c", *s++);
```

위와 같이 후위 연산자를 사용하여 while문으로 문자열을 출력할 수 있다. 다만 위와 같이 string literal을 사용하면 read-only meomory에 저장되기 때문에 수정할 수 없다.

### Pointer to Arrays

```c
int (*p)[5];
int* p2;
int arr[5];
p = arr;
p2 = arr;

printf("%llu\n", p) // 0
printf("%llu\n", p2) // 0
printf("%llu\n", ++p) // 20
printf("%llu\n", ++p2) // 4
```

p는 arr의 주소를 저장하고 있기 때문에 0이 출력된다. p2는 arr의 첫 번째 원소의 주소를 저장하고 있기 때문에 0이 출력된다. p는 5개의 int를 저장하고 있기 때문에 20이 출력된다. p2는 1개의 int를 저장하고 있기 때문에 4가 출력된다.

### Pointer to 2D Arrays

```c
int arr[2][3] = {{1,2,3},{4,5,6}};
int *p = arr;
```

위에서 arr[1][2]에 접근하려면 p[1*num_cols+2]를 해야 한다. 2D structure가 무너지는 것이다.

```c
int arr[2][3] = {{1,2,3},{4,5,6}};
int (*p)[3] = arr;
```

위와 같이 2D array를 선언하면 2D structure가 유지된다. 따라서 p[1][2]를 하면 6이 출력된다. 그래서 만약에 2D array를 함수의 인자로 넘길 때는 매개변수를 위와 같이 선언해야 한다.

> 참고로 `int* p[3]`은 포인터 배열이다. 위와 다르다.

### Pointer to Structure

```c
struct point {
    int x;
    int y;
};

struct point p = {1,2};
struct point *pp = &p;

printf("%d %d\n", p.x, p.y); // 1 2
printf("%d %d\n", pp->x, pp->y); // 1 2
```

pointer to structure는 `->`을 사용해서 structure의 property로 접근할 수 있다. 물론 (*pp).property로도 접근할 수도 있다.

#### Passing Structure to Function

```c
void f1(struct point p) {
    p.x = 10;
    p.y = 20;
}

void f2(const struct point *pp) {
    pp->x = 10; // error
}
```

f1에서는 structure를 복사해서 넘겨주기 때문에 structure의 property를 바꿔도 main 함수에서는 바뀌지 않는다. f2에서는 structure의 주소를 넘겨주기 때문에 structure의 property를 바꾸면 main 함수에서도 바뀐다. 따라서 structure를 함수의 인자로 넘길 때는 const를 붙여서 넘겨주는 것이 좋다. 그러면 read-only이기 때문에 structure의 property를 바꿀 수 없다.

#### Const

const을 선언하는 순서에 따라 다르다.

```c
int a = 10;
int * const p2 = &a;
*p2 = 20; // ok
int b = 30;
p2 = &b; // error
```

int * const pointer는 pointer가 가리키는 주소를 바꿀 수 없다. 하지만 pointer가 가리키는 주소에 있는 값을 바꿀 수 있다.

```c
int a = 10;
const int *p3 = &a;
*p3 = 20; // error
int b = 30;
p3 = &b; // ok
```

const int * pointer는 pointer가 가리키는 주소에 있는 값을 바꿀 수 없다. 하지만 pointer가 가리키는 주소를 바꿀 수 있다.

```c
int a = 10;
const int * const p4 = &a;
*p4 = 20; // error
int b = 30;
p4 = &b; // error
```

const int * const pointer는 pointer가 가리키는 주소를 바꿀 수도 없고 pointer가 가리키는 주소에 있는 값을 바꿀 수도 없다.

### Pointer to Function

function을 argument로 받기 위해서는 function pointer를 사용한다.

```c
void (*fp)(int, int);
```

위와 같이 소괄호를 사용하고 argument는 type만 적어주면 된다.
