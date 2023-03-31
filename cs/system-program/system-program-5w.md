# 시스템프로그램 5주 차

intel processor의 명령어를 배울 것이다.

## Data Movement Instructions

- mov
  - movb, movw, movl, movq
  - memory to memory는 x86-64에서는 지원하지 않는다.
- movs
  - sign expansion으로 upper bits를 채움
- movz
  - zero expansion으로 upper bits를 채움

크게는 3가지가 있다.

### mov

``` machine code
movq S, D
```

S는 source, D는 destination이다. S와 D는 memory나 register가 될 수 있다.

``` machine code
movabsq I, R
```

I는 immediate value, R은 register이다. I는 64bit이어야 한다.

> movabsq는 mov와 다르게 register에만 immediate value를 넣을 수 있다.

### 5 possible forms of mov

- movq imm, reg
  - movq $0, %rax
  - temp = 0
  - 보통 local variable은 regsiter에 저장한다.
- movq imm, mem
  - movq $0, (%rax)
  - *p = 0
- movq reg, reg
  - movq %rax, %rbx
  - temp2 = temp
- movq reg, mem
  - movq %rax, (%rbx)
  - *p = temp
- movq mem, reg
  - movq (%rax), %rbx
  - temp = *p

> ()는 memory address를 의미한다. $는 immediate value를 의미한다.

### movz

``` machine code
movzbq S, R
```

S는 source, R은 register이다. S는 memory나 register가 될 수 있다. S의 lower 8bit를 R의 lower 8bit에 넣고 upper 56bit는 0으로 채운다.

- movzbw
  - byte to word
- movzbl
  - byte to long
- movzwl
  - word to long
- movzbq
  - byte to quad
- movzwq
  - word to quad

movzlq가 없는 이유는 저번에 설명했던 것 처럼 long은 32bit이기 때문에 자동으로 expansion이 되기 때문에 없다.

### movs

``` machine code
movsbq S, R
```

S는 source, R은 register이다. S는 memory나 register가 될 수 있다. S의 lower 8bit를 R의 lower 8bit에 넣고 upper 56bit는 S의 sign bit로 채운다.

- movsbw
  - byte to word
- movsbl
  - byte to long
- movswl
  - word to long
- movsbq
  - byte to quad
- movswq
  - word to quad
- movslq
  - long to quad
- cltq <- 특별한 부분
  - convert long to quad
  - 따로 주소를 지정하지 않고 명령어 단독으로 사용
  - eax를 sign expand하여 rax에 저장

#### Function Example

``` c
void swap(long *xp, long *yp) {
    long t0 = *xp;
    long t1 = *yp;
    *xp = t1;
    *yp = t0;
}
```

argument xp는 rdi, yp는 rsi에 저장된다.

``` machine code
swap:
  movq (%rdi), %rax
  movq (%rsi), %rdx
  movq %rdx, (%rdi)
  movq %rax, (%rsi)
  ret
```

### Stack

top이 the lowest address를 가리킨다. 즉 bottom이 the highest address를 가리킨다.


``` machine code
pushq R
popq R
```

- pushq
  - push quad
  - stack에 값을 넣는다.
- popq
  - pop quad
  - stack에서 값을 뺀다.

## Arithmetic Instructions / Logical Instructions

- Load Effective Address
  - leaq
- Unary
- Binary
- Shift

위 4가지 classes로 나누어서 설명한다.

### Load Effective Address

``` machine code
leaq 8(%rbx, %rcx, 4), %rax
```

mov는 값을 복사하지만 leaq는 값을 복사하지 않고 address를 저장한다. 앞 부분이 source, 뒷 부분이 destination이다.

> 8(%rbx, %rcx, 4)는 8 + rbx + rcx * 4이다.

참고로 leaq를 사용해서 some arithmetic을 할 수 있다.

``` machine code
leaq 7(%rax, %rax, 2), %rax
```

위 코드는 3 * rax + 7이다.

### Unary

``` machine code
incq R
decq R
negq R
notq R
```

- inc
  - increment
  - R = R + 1
- dec
  - decrement
  - R = R - 1
- neg
  - Negate (2's complement)
  - R = -R
- not
  - bitwise not (1's complement)
  - R = ~R

### Binary

``` machine code
addq S, D
subq S, D
imulq S, D
andq S, D
xorq S, D
orq S, D
```

이름 그대로의 기능들을 수행한다.

### Shift

``` machine code
salq I, R
shlq I, R
sarq I, R
shrq I, R
```

> a는 arithmetic shift, h은 logical shift이다. l은 left, r은 right이다.

I는 immediate value, R은 register이다. R의 lower 64bit를 I만큼 shift한다. 만약에 I에 Immediate value를 사용 안하고 register를 사용할거면 1 byte인 %cl을 사용해야 한다.

만약에 R이 8 bit이라면 8 bit를 넘어가는 shift는 무시된다.

### Special Instructions

``` machine code
imulq S
mulq S
cqto
idivq S
divq S
```

- imulq
  - signed multiply
  - %rdx:%rax = %rax * S
  - 16byte를 저장하기 위해 rdx와 rax를 사용한다.
- mulq
  - unsigned multiply
- cqto
  - convert quad to octuple
- idivq
  - signed divide
  - %rax = %rdx:%rax / S
  - %rdx = %rdx:%rax % S
  - 몫과 나머지를 각각 저장
- divq
  - unsigned divide

## Control Instructions

Codition codes 즉 eflags를 사용해서 control한다. 그 안에 CF, ZF, SF, OF등이 있는데 implicit하게 most recent arithmetic/logical operation에 의해 set된다.

- CF
  - carry flag
  - unsigned overflow
- ZF
  - zero flag
  - 결과가 0이면 1
- SF
  - sign flag
  - 결과의 MSB을 가져옴
- OF
  - overflow flag
  - signed overflow

### special things about condition codes (optional)

- leaq는 condition codes를 변경하지 않는다.
- xor과 같은 logcial operation은 CF, OF를 0으로 set한다.
- Shift operation은 CF를 shifted out된 마지막 bit으로 set하고 OF를 0으로 set한다.
- inc, dec는 CF를 변경하지 않는다.

### Compare and Test Instructions

``` machine code
cmpq b, a
testq b, a
```

- cmpq
  - compare quad
  - (a - b)가 0이면 같다는 사실을 통해 comparison을 한다.
  - ZF = (a == b)
  - SF = (a < b)
- testq
  - logical and quad
  - (a & b )연산을 통해 condition codes를 set한다.
  - ZF = (a & b == 0)
  - SF = (a & b < 0)
  - CF, OF = 0

### Accessing Condition Codes

| Instruction | Effect | Description |
| --- | --- | --- |
| sete D | D = ZF | set if equal |
| setne D | D = ~ZF | set if not equal |
| sets D | D = SF | set if negative |
| setns D | D = ~SF | set if not negative |
| setg D | D = ~(SF ^ OF) & !ZF | set if greater than (signed) |
| setge D | D = ~(SF ^ OF) | set if greater than or equal (signed) |
| setl D | D = (SF ^ OF) | set if less than (signed) |
| setle D | D = (SF ^ OF) \| ZF | set if less than or equal (signed) |
| seta D | D = ~CF & ~ZF | set if above (unsigned) |
| setae D | D = ~CF | set if above or equal (unsigned) |
| setb D | D = CF | set if below (unsigned) |
| setbe D | D = CF | ZF | set if below or equal (unsigned) |

### Jump Instructions

- Unconditional Jump
  - jmp .L1
- Conditional Jump (based on condition codes)
  - jXX
  - XX에는 위에 set에서 봤던 것처럼 set 뒤에 있는 e, ne등이 들어간다.
  - 동작도 set과 같다.

#### Conditional branch Tips

c 언어 코드에서의 if문으로 goto version으로 바꿔서 생각하면 machine code로 바꾸기 편하다.

> intel에서는 .L1 처럼 Label 이름 앞에 마침표를 붙인다.

### Coditional Move

``` machine code
cmovXX S, D
```

XX에는 위에 set에서 봤던 것처럼 set 뒤에 있는 e, ne등이 들어간다. S는 regs, memory이고 D는 regs이다.

``` c
v = test_expr ? then_expr : else_expr;
```

를 conditional assignment로 바꾸면

``` c
v = then_expr;
ve = else_expr;
t = test_expr;
if (!t) v = ve;
```

이다. 그래서 위의 코드를 machine code로 바꾸면

``` machine code
movq then_expr, %rax // v = then_expr
movq else_expr, %rcx // ve = else_expr
movq test_expr, %rdx // t = test_expr
testq %rdx, %rdx // if (!t)
cmovne %rcx, %rax // v = ve
```

Conditional control transfers(e.g. jmp)보다 conditional move가 더 빠르다. 그 이유는 나중에 배우게 된다.
