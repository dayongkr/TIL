# 시스템프로그램 6주 차

## Control Instruction

compiler에 가장 잘 맞는 types of loops는 do-while loop이다.

### do-while loop

```c
do {
    // statements
} while (condition);
```

```c
loop: // goto version
    // statements
    if(condition) goto loop;
```

```asm
loop:
    // statements
    cmp condition, 0
    jxx loop
```

위와 같이 do-while loop은 1 대 1로 변환될 수 있다.

### while loop

Whlie문은 2가지로 나뉜다.

#### Jump to middle (while)

loop 부분이 먼저 나오고, condition이 나오는 경우이다.

```c
while (condition) {
    // statements
}
```

```c
goto test;
loop: // goto version
    // statements
test:
    if(condition) goto loop;
```

```asm
jmp test
loop:
    // statements
test:
    cmp condition, 0
    jxx loop
```

#### Guarded-do (while)

loop 부분이 나중에 나오고, condition이 먼저 나오는 경우이다.

```c

do-while loop과 같이 변환된다. 따라서 더 최적화된 형태로 변환된다.

```c
if (!condition) goto done;
loop: // goto version
    // statements
    if(condition) goto loop;
done:
```

```asm
cmp condition, 0
jxx done
loop:
    // statements
    cmp condition, 0
    jxx loop
done:
```

> gcc -Og은 Jump to middle 방식으로 변환하고 -O1은 Guarded-do 방식으로 변환한다.

### For loop

For loop도 While과 같이 Jump to middle과 Guarded-do로 나뉜다.

일단 init 부분을 빼내고 while문 안에 update 부분을 넣는 방식으로 while문으로 일단 변환하고 while문의 변환 방식에 따라 변환한다.

### Switch

jump table이라고 불리는 자료구조를 사용해서 효율적으로 구현한다. if-else보다 더 효과적이다. 하지만 case values에 따라 compiler 판단에 따라서는 if-else로 변환될 수 있다.

> 예를 들어 sparse switch 즉 value가 dense하지 않은 경우에는 if-else로 변환된다.

Jump table는 배열으로 각 요소에는 label이 들어있다. 각 index는 switch의 case value에 해당한다.

> e.g. case value -> index, 100 -> 0, 101 -> 1, 102 -> 2, 103 -> 3

```asm
.section .rodata
    .align 8
.L4
  .quad .L3 // 100
  .quad .L8 // 101
  .quad .L5 // 102
  .quad .L6 // 103
  .quad .L7 // 104
  .quad .L8 // 105
  .quad .L7 // 106
```

위 처럼 jump table을 만든다.

### Procedures

- control transfer
  - 함수 부분으로 이동하고 반환할 때 다시 돌아가는 동작
- Passing of data
  - parameter와 return value를 전달하는 동작
- Allocating space for local variables and deallocating them
  - 지역 변수를 위한 공간을 할당하고 해제하는 동작
- saving some regs values
  - 필요한 register 값을 저장하는 동작
- return address도 저장한다.

위 동작들을 program stack 조작을 통해 관리한다.

각 함수들은 각자의 stack frame을 가지고 있는데 이 stack frame은 함수가 호출될 때 생성되고 함수가 끝나면 해제된다. stack frame은 local variables, argument, return address, callee-save registers, caller-save registers 등을 포함한다. 참고로 argument는 뒤에 있는 것 부터 저장된다.

#### Procedure Instruction

- pushq src
  - stack pointer를 8 byte 감소시키고 그 위치에 src의 값을 저장한다.
- popq dst
  - stack pointer에 해당하는 위치의 값을 dst에 저장하고 stack pointer를 8 byte 증가시킨다.
- call label, call *operand
  - call instruction은 call label과 call *operand로 나뉜다.
  - call label은 label로 이동하고 return address를 stack으로 push한다.
  - call *operand는 operand가 가리키는 주소로 이동하고 return address를 stack으로 push한다.
- ret
  - return address를 pop해서 해당 주소로 이동한다.

#### Example - call

```assm
callq 8048b90 <main>
mov %rax, %rdx
```

```binary
804854e: e8 3d 06 00 00
8048553: 48 89 c2
```

e8은 call instruction을 뜻하고 나머지 4 byte는 주소인데 call은 pc-relative address이기 때문에 서로 다르게 생겼다. 또한 인텔은 little endian이기 때문에 읽을 때 뒤에서 부터 읽어야 하기 때문에 00 00 06 3d가 된다. 따라서 0x804854e + 0x5 + 0x0000063d = 0x8048b90이 된다.

이 때 현재 pc인 0x8048553는 stack에 return address로 push되고 pc인 %rip에 0x8048b90이 저장되면서 해당 pc로 이동한다.

#### Example - return

```asm
retq
```

```binary
8048591: c3
```

c3은 ret instruction을 뜻한다. ret instruction은 stack에 저장된 return address를 pop해서 %rip를 가져와 해당 주소로 이동한다.

#### Data transfer

6개의 integral argument까지는 register를 통해 전달하고 그 이상은 stack을 통해 전달한다. return value는 %rax에 저장한다.

> 따라서 function을 정의할 때 6개 이상의 arguments를 사용하지 않는 것이 성능상 좋다.

- argument
  - 1st argument : %rdi, %edi, %di, %dil
  - 2nd argument : %rsi, %esi, %si, %sil
  - 3rd argument : %rdx, %edx, %dx, %dl
  - 4th argument : %rcx, %ecx, %cx, %cl
  - 5th argument : %r8, %r8d, %r8w, %r8b
  - 6th argument : %r9, %r9d, %r9w, %r9b

size는 64, 32 , 16, 8 bit로 나뉜다.

#### Local storage on the stack

일반적으론 local data는 regs에 저장하지만 몇 가지 경우에는 stack에 저장한다.

- & 연산자를 사용해서 address를 구할 때
- local data를 저장하기 위한 공간이 부족할 때
- 배열 또는 구조체를 저장할 때

#### Local storage in registers

caller와 callee가 같은 register를 사용할 수 있도록 사전에 저장하고 사용 후 다시 복구하는 과정이 필요하다.

- callee-saved registers
  - callee가 사용하려면 저장해야 하는 register
  - %rbx, %rbp, %rsp, %r12, %r13, %r14, %r15
- caller-saved registers
  - caller가 사용하려면 저장해야 하는 register
  - 위에서 나온 regs를 제외한 나머지 regs

위와 같은 convention을 따라서 직접 구현 해야 한다.

