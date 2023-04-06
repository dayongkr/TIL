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
