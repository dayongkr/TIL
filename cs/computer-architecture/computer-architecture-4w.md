# 컴퓨터구조개론 4주 차

## Machine code

RISC-V instrutions은 4 bytes length를 가지지만 CISC는 가변 길이(1 ~ 15 bytes)를 가진다.

> 가변 길이를 가지면 CPU가 operation마다의 길이를 알고 이를 불러올 수 있도록 하는 부분을 구현해야 하므로 더 복잡해진다.

### R-format Instruction

|funct7|rs2|rs1|funct3|rd|opcode|
|-|-|-|-|-|-|
|7 bits|5 bits|5 bits|3 bits|5 bits|7 bits|

- opcode
  - 7 bits
- rd
  - destination regs number
  - 5 bits
- funct3
  - additional opcode
  - 3 bits
- rs1
  - first source regs num
- rs2
  - second source regs num
- funct7
  - additional opcode
  - 7 bits

비슷한 operation의 opcode는 서로 같고 보통 funct3 또는 funct7로 어떤 operation인지 구분한다.

#### R-format example

``` risc
add x9, x20, x21
```

위 instruction을  R-format으로 나타내면 아래와 같다.

|0|21|20|0|9|51|
|-|-|-|-|-|-|

``` risc
sub x9, x20, x21
```

sub instruction은 위에서 func7 을 32로만 바꾸면 된다.

#### R-format Immediate and load

|immediate|rs1|funct3|rd|opcode|
|-|-|-|-|-|
|12 bits|5 bits|3 bits|5 bits|7 bits|

위와 같이 immediate Arithmetic instruction에는 funct7 과 rs2 대신 immediate 부분이 있다.

#### R-format Immediate example

``` risc
addi x9, x20, 123
```

위 instruction을  R-format으로 나타내면 아래와 같다.

|123|20|0|9|19|
|-|-|-|-|-|

#### Sign Extension

서로 다른 bit끼리 연산하기 위해 더 큰 bit로 맞춰야 하는데 이를 Sign Extension이라고 한다. Sign Extension을 수행할 때 sign bit을 왼쪽에 비어 있는 부분에 복제한다.

li를 하면 기본적으로 sign-extend를 사용하고 lh, lb는 sign-extends, lhu, lbu는 zero-extends (0으로 채우는 extend)을 수행한다.

#### Memory addressing

주소 또한 32bit(non-negative) integer로 되어 있다. mem -> regs를 load, regs -> mem을 store이라고 한다.

#### Memory Operand Example

``` c
g = h + A[8]; // # A의 element는 int data type이다.
```

g는 x1, h는 x2, A의 base address는 x3에 있다고 가정 했을 때 위 코드를 machine code로 변환하면?

``` risc
lw x10, 32(x3)
add x1, x2, x10
```

lw는 load word라는 operand으로 위 instruction은 x3에 저장되어 있는 base address에 32를 더한 주소에 있는 값을 x10 regs 주소로 load한다.

``` c
A[12] = h + A[8];
````

를 instruction으로 바꾸면 아래와 같다.

``` risc
lw x10, 32(x3)
add x11, x2, x10
sw x11, 48(x3)
```

sw는 store word operand이다.

#### Memory Operand I-format

``` risc
lw x9, 123(x20)
```

을 I-format으로 나타내면 아래와 같다.

|immediate|x20|funct3|x9|Load|
|-|-|-|-|-|
|-123|20|2|9|3|

#### Memory Operand S-format

|imm[11:5]|rs2|rs1|funct3|imm[4:0]|opcode|
|-|-|-|-|-|-|

immediate의 11~5 bit은 imm[11:5]에 저장하고 4~0bit은 imm[4:0]에 저장한다.

``` risc
sw x9, -123(x20)
```

를 S-format으로 나타내면 아래와 같다.

|-123[11:5]|x9|x20|funct3|-123[4:0]|Store|
|-|-|-|-|-|-|

#### 32-bit Constants

12bit만 해도 대부분의 상황에서 충분하지만 만약에 32-bit 상수를 사용하고 싶으면 lui와 addi instruction 조합으로 가능하다.

``` risc
lui x19 976
addi x19 x19 1280
```

위와 같이 먼저 lui instruction으로 upper 20-bit를 먼저 복사하고 addi로 lower 12-bit를 넣으면 32-bit constant를 사용할 수 있다.

#### Endianness

Risc-V는 little endian을 사용한다. little endian은 LSB가 가장 작은 주소에 저장되는 방식이다. 반대로 big endian은 MSB가 가장 작은 주소에 저장되는 방식이다.

### Conditional Operations

Conditional operation은 branch instruction을 사용한다.

- beq
  - branch if equal
  - e.g. beq rs1, rs2, L1 (if rs1 == rs2 then goto L1)
- bne
  - branch if not equal
  - e.g. bne rs1, rs2, L1 (if rs1 != rs2 then goto L1)
- blt
  - branch if less than
  - e.g. blt rs1, rs2, L1 (if rs1 < rs2 then goto L1)
- bge
  - branch if greater than or equal
  - e.g. bge rs1, rs2, L1 (if rs1 >= rs2 then goto L1)

blt와 bge는 signed comparison이고 bgeu와 bltu는 unsigned comparison이다.

위와 같은 branch instruction을 사용해서 Loop Statements를 구현할 수 있다.

> e.g. `beq x0, x0, L1`을 사용하여 loop를 구현할 수 있다.

#### Jump Instruction

branch instruction과 달리 conditional operation이 없는 instruction이다. 다만 jump 이후에 다시 돌아오기 위해 PC를 저장할 regs 주소를 지정해야 한다. 현재 PC를 저장하지 않는 이유는 다시 기존 PC로 오면 다시 jump instruction을 수행하기 때문이다. 따라서 다음 instruction을 수행하기 위해 PC + 4를 저장한다.

> 함수를 호출할 때에도 Jump instruction을 사용한다.

- jal
  - jump and link
  - e.g. jal x1, L1 (x1 = PC + 4; goto L1)
- jalr
  - jump and link register
  - e.g. jalr x1, Offset(x2) (x1 = PC + 4; goto x2)
- j
  - jump (Pseudo instruction)
  - e.g. j L1 (goto L1)

> Program Coutner(PC)는 현재 instruction의 주소를 가리키는 register이다. PC는 항상 4의 배수를 가리킨다.

#### Branch Addressing

|imm[12]|imm[10:5]|rs2|rs1|funct3|imm[4:1]|imm[11]|opcode|
|-|-|-|-|-|-|-|-|

SBformt으로 저장하는데 PC는 4씩 증가하기 때문에 imm[0]은 0임을 보장할 수 있기 때문에 imm[0]은 저장하지 않는 덕분에 immediate를 13bit로 저장할 수 있다.

주소를 가르키는 방법은 PC-relative addressing을 사용한다. PC-relative addressing은 PC에 immediate를 더한 주소로 branch한다.

#### Jump Addressing

|imm[20]|imm[10:1]|imm[11]|imm[19:12]|rd|opcode|
|-|-|-|-|-|-|

UJformat으로 저장한다. PC는 4씩 증가하기 때문에 imm[0]은 0임을 보장할 수 있기 때문에 imm[0]은 저장하지 않는 덕분에 immediate를 21bit로 저장할 수 있다. 

Branch와 달리 jump는 PC-relative addressing을 사용하지 않는다. 따라서 lui와 jalr instruction을 조합해서 사용한다.

### RISC-V Encoding Summary

어떠한 format이더라도 Immediate의 MSB는 Sign bit이다.
