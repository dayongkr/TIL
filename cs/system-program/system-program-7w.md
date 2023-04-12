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

#### Variable-sized array

```c
int vm_el(long n, int A[n][n], long i, long j) {
  return A[i][j];
}
```

```asm
// n in %rdi, A in %rsi, i in %edx, j in %rcx
vm_el:
  imulq %rdx, %rdi // n * i
  leaq (%rsi, %rdi, 4), %rax // A + 4 * n * i
  movl (%rax, %rcx, 4), %eax // M[A + 4 * n * i + 4 * j]
  ret
```

Variable-sized array여도 큰 차이가 없다.

## Structure

``` c
struct rec {
  int i;
  int j;
  int a[2];
  int *p;
};

void set(struct rec *r) {
  r -> j = r -> i;
}
```

``` asm
// r in %rdi
set:
  movl (%rdi), %eax // r -> i
  movl %eax, 4(%rdi) // r -> j = r -> i
  ret
```

각 멤버는 연속된 메모리 공간에 저장된다.

### Alignment restriction

Structure은 각 요소의 데이터 크기가 다르기 때문에 메모리 공간에 저장할 때 alignment restriction을 따라야 한다. 예를 들어 K Bytes를 저장할 때 주소를 K의 배수로 맞춰야 한다. 이를 통해 CPU가 더 빠르게 접근할 수 있다.

따라서 저번에 jump table에서 `.align 8`을 했던 것이 주소를 8의 배수로 맞춰서 더 빠르게 접근하기 위함이었다.

#### Alignments for structures

- 멤버마다 alignment을 따른다.
  - 각 멤버 사이에 gap을 넣어 alignment을 맞춘다.
  - 따라서 버려지는 메모리 공간이 생길 수 있다.
- Overall structure alignment는 member의 alignment 중 가장 큰 것을 따른다.
  - 17 Bytes의 structure가 있으면 8 Bytes의 alignment을 따르기 위해 9 Bytes의 gap을 넣어 24 Bytes의 메모리 공간을 차지한다.
  - 따라서 버려지는 메모리 공간이 생길 수 있다.

따라서 저장하는 순서를 바꿈으로써 버려지는 메모리 공간을 줄일 수 있다.

## Union

Structure와 달리 union은 각 멤버가 같은 메모리 공간을 공유한다. 따라서 union의 크기는 가장 큰 멤버의 크기와 같다.

예를 들어 8 Bytes의 union이 있으면 int 2개는 8 Bytes 안에 저장되는데 little endian이라면 low-order byte가 먼저 저장된다. 반대로 big endian이라면 high-order byte가 먼저 저장된다.
