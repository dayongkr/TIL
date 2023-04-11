# 시스템프로그램 7주 차

## Review: arrays and pointers in C

배열과 포인터는 C에서 가장 중요한 개념 중 하나이다. 배열은 연속된 메모리 공간을 할당받아서 그 공간에 값을 저장하는 것이다.

2차원 배열은 Row-major order로 저장된다. 즉 첫 번째 행의 모든 열을 저장한 후 두 번째 행의 모든 열을 저장한다. 또한 각 행의 첫 번째 열의 주소는 해당 행의 요소만큼만 관리한다.

``` asm
movl (%rdx, %rcx, 4), %eax
```

위의 Assembly code는 %rdx + %rcx * 4의 값을 %eax에 저장한다. %rdx는 배열의 주소 %rcx는 배열의 인덱스이다. 따라서 int형 배열인 a의 i번째 요소 즉 a[i]를 %eax에 저장하는 것이다.

|Expression|Type|Assembly code|
|:-:|:-:|:-:|
|E|int *|movq %rdx, %rax|
|E[0]|int|movl (%rdx), %eax|
|E[i]|int|movl (%rdx, %rcx, 4), %eax|
|&E[2]|int *|leaq 8(%rdx), %rax|
|E + i - 1|int *|leaq -4(%rdx, %rcx, 4), %rax|
|*(E + i - 3)|int|movl -12(%rdx, %rcx, 4), %eax|
|&E[i] - E|long|movq %rcx, %rax|

배열의 bound checking은 하지 않는다. 따라서 배열의 인덱스가 배열의 크기를 넘어가면 segmentation fault가 발생한다.

### Example Array & loop

``` c
typedef zip[5];
...
long zip2int(zip z) {
  int i;
  long zr = 0;
  for (i = 0; i < 5; i++) {
    zr = 10 * zr + z[i];
  }
  return zr;
}
```

Array code를 pointer code로 바꿔서 compile한다.

```c
long zip2int(zip z) {
  int i;
  long zr = 0;
  for (i = 0; i < 5; i++) {
    zr = 10 * zr + *(z + i);
  }
  return zr;
}
```

for 문을 do-while문으로 바꾼다.

```c
long zip2int(zip z) {
  long zr = 0;
  long *zend = z + 4;
  do {
    zr = 10 * zr + *(z);
    z++;
  } while (z <= zend);
  return zr;
}
```

이를 Assembly code로 바꾼다.

```asm
// z in %rdi, zr in %rax, zend in %rbx

xorq %rax, %rax // zr = 0
leaq 32(%rdi), %rbx // zend = z + 4
.L59:
leaq (%rax, %rax, 4), %rdx // 5 * zr
movq (%rdi), %rax // get *z
addq $8, %rdi // z++
leaq (%rax, %rdx, 2), %rax // 10 * zr + *z
cmpq %rbx, %rdi // z - zend
jle .L59 // if z <= zend, go to .L59
ret
```

### Nested array

2차원 배열로 예를 든다. 모든 배열은 연속된 메모리 공간에 저장된다. A[R][C]가 있으면 A[i]는 A + i \* C * sizeof(int)의 주소를 가진다.

```c
int pgh[4][5];

int *get_pgh_zip(int i){
  return pgh[i];
}
```

```asm
leaq (%rdi, %rdi, 4), %rax
leaq pgh(,%rax,4), %rax
ret
```

A\[i][j]는 A + (i \* C + j) * sizeof(int)의 주소를 가진다.

```c
int pgh[4][5];

int get_pgh_digit(int i, int j){
  return pgh[i][j];
}
```

```asm
leaq 0(,%rsi,4), %rdx
leaq (%rdi, %rdi, 4), %rax
movl pgh(%rdx, %rax, 4), %eax
ret
```


