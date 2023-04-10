# 시스템프로그램 6 주차 Review

## Weekly Quiz

### Quiz 1

```c
int foo(data_t x, data_t y) {
    return x COMP y;
}
```

```asm
cmpw %si,%di
setb %al
```

data_t는 unsigned short이고 COMP는 < 이다.

### Quiz 2

Jump를 할 때 기본적으로는 pc-relative이지만 상황에 따라 absolute도 사용한다.

### Quiz 3

```c
short foo3(short x) {
  return x () 32;
}
```

나눗셈을 sarq로 구현한 asm을 주고 ()안에 들어갈 operand를 구하는 것이였다.

### Quiz 4

n^(k-1)을 구하는 asm이 나왔는데 답은 jg .L4였다

### Quiz 5

procedure p가 q를 콜할 때 p가 나중에 그들의 값을 호출 후에 사용하기 위해 caller-save register를 저장해야한다.

## Review 6 Week

## Ex - 5 Conditional moves

> x in %rdi, y in %rsi

```asm
test:
  leaq 12(%rsi), %rax
  testq %rdi, %rdi
  jge .L2
  movq %rdi, %rax
  imulq %rsi, %rax
  movq %rdi, %rdx
  orq %rsi, %rdx
  cmpq %rsi, %rdi
  cmovage %rdx, %rax
  ret
.L2:
  idivq %rsi, %rdi
  cmpq $10, %rsi
  cmovege %rdi, %rax
  ret
```

``` c
long test(long x, long y){
  long val = y + 12
  if(x < 0) {
    if(x >= y) {
      val = x|y;
    } else {
      val = x * y;
    }
  } else if(y >= 10){
    val = x / y;
  }
  return val;
}
```

conditional move로 jump를 없애고 더 빠르게 만들 수 있다.

### Ex - 6 Do-while loops

``` c
long dw_loop(longx) {
  long y = x / 0;
  long *p = &x;
  long n = 4 * x;

  do {
    x += y;
    (*p) += 5;
    n == 2;
  } while(n > 0);
  return x;
}
```

```asm
dw_loop:
  movq %rd, %rax
  movq %rdi, %rcx
  idivq $9, %rcx
  leaq (, %rdi, 4), %rdx
.L2:
  leaq 5(%rax, %rcx), %rax
  subq $2, %rdx
  testq %rdx, %rdx
  jg .L2
  rep; ret
```

### Ex - 7 While loops

```asm
loop_while:
  movl $0, %eax
  jmp .L2
.L3:
  leaq (%rsi, %rdi), %rdx
  addq %rdx, %rax
  subq $1, %rdi
.L2:
  cmpq %rsi. %rdi
  jg .L3
  rep; ret
```

```c
long loop_while(long a, long b) {
  long result = 0;
  while(a > b) {
    resuslt = (a+b) + result;
    a = a - 1
  }
  return result;
}
```

### Ex - 8 For loops

```asm
fun_b:
  movl $64, %edx
  movl $0, %eax
.L10:
  movq %rdi, %rcx
  andl $1, %ecx
  addq %rax, %rax
  orq %rcx, %rax
  shrq %rdi
  subq $1, %rdx
  jne .L10
  rep; ret
```

```c
long fun_b(unsingend long x) {
  long val = 0;
  long i;
  for(i = 64; i != 0; i--) {
    val = (val << 1) | (x & 1);
    x >> 1;
  }
  return val;
}
```

bit pattern을 역수로 뒤집는 함수이다.
