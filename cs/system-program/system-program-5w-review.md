# 시스템프로그램 5주 차 Review

## 3-3 Data Movement & Arithmetic Instructions

C언어와 Machince code의 매핑이 어떻게 이루워지는지 정도로 공부하면 된다. 앞으로 정보 보호 쪽으로 공부를 하게 되면 이 Assembly code를 보는 것이 중요해질 것이다.

명세표에서 S는 Imm, Regs, Mem 모두 올 수 있고 D는 Regs, Mem만 올 수 있다. 그리고 간혹 I, R, M이라고 적혀있는데 이는 각 Imm, Regs, Mem을 의미한다.

### 3-3 Example

#### Function swap2()

c code -> machine code

``` c
void swap2(long * xp, long *yp) {
  long tmp;
  tmp = *xp;
  *xp = *yp;
  *yp = tmp;
}
```

``` machine code
movq (%rdi), %rdx
movq (%rsi), %rcx
movq rcx, (%rdi)
movq rdx, (%rsi)
ret
```

parameter는 6개정도 까지는 정해져있는데 이는 나중에 배우게 된다. memory to memory는 안되기 때문에 임시로 register에 저장해놓고 다시 memory에 저장하는 식으로 구현한다.

#### Arithmetic-1

|Address|Value|
|---|---|
|0x100|0xFF|
|0x104|0xAB|
|0x108|0x13|
|0x10C|0x11|

|Regsiter|Value|
|---|---|
|%eax|0x100|
|%ecx|0x1|
|%edx|0x3|

|Instruction|Desitination|Value|
|---|---|---|
|addl %ecx, (%eax)|0x100|0x100|
|imull $16, (%eax, %edx, 4)|0x10C|0x11 * 16 = 0x110|

책에 있는 예제 문제이다.

#### Arithmetic-2

machine code -> c code

``` machine code
arith2:
  orq %rsi, %rdi
  sarq $3, %rdi
  notq %rdi
  movq %rdx, %rax
  subq %rdi, %rax
  ret
```

> x in %rdi, y in %rsi, z in %rdx

``` c
long arith2(long x, long y, long z) {
  long t1 = x | y;
  long t2 = t1 >> 3;
  long t3 = ~t2;
  long t4 = z - t3;
  return t4;
}
```

## 3-4 Control instructions

Hign level program에서는 다양한 control flow 구조를 사용할 수 있지만 결국 goto문을 사용하는 것과 같다. 결국 Machine code에서는 jump와 move instruction을 사용하여 control flow를 구현한다.

- g, ge, l, le는 signed comparison이고 a, ae, b, be는 unsigned comparison이다.
- jump instruction은 Program Counter을 기반으로 주소를 계산한다.

### 3-4 Example

#### Codition codes 1

``` c
int comp(data_t a, data_t b) {
  return a COMP b;
}
```

machine code에 따르면 COMP와 data_t가 무엇일까?

``` machine code
cmp %esi, %edi
setl %al
```

data_t는 int이고 COMP는 <이다.

``` machine code
cmpb %sil, %edil
setae %al
```

data_t는 char이지만 setae이므로 unsigned char이고 COMP는 >=이다.

#### Jump instruction encodings

``` binary
4003fa: 74 02
4003fc: ff d0
```

``` machine code
je XXXXXX
callq $rax
```

XXXXXX는 다음 PC에 해당하는 주소에 원하는 만큼을 더한 주소이므로 4003fc + 0x02 = 400400이다.

> 02에 해당하는 부분은 signed byted이기 때문에 음수가 나올 수 있다.

다 교재에 나오는 문제들이기 때문에 생략하는데 꼭 한 번 풀어보자.
