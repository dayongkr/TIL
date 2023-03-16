# 컴퓨터구조개론 3주 차

앞으로 3주 동안 Assembly code(Instruction)를 배우게 된다.

## Instruction Set

- Arithmetic operations (add, sub, ...)
- Logic operations (and, or, xor, ...)
- Multiplication / Division
  - Arithmetic operations보다 좀 더 복잡하다.
- Load from memory / Store to memory(load, store, ...)
- Jump / branch
  - if, for문 등에서 사용
  
위 5가지 Instructions를 수업에서 다룬다.

- Exception handling
  - cpu design(x86, arm)에 따라 특정한 방법이 있다.
  - 수업에서는 따로 다루지 않는다.

### RISC-V simulators

- [Spike](https://github.com/riscv-software-src/riscv-isa-sim): CLI 기반 simulator
- [RARS Simulator](https://github.com/TheThirdOne/rars): GUI 기반 simulator

### Arithmetic Operations

단순 연산과 대입을 수행하는 C 코드:

``` c
f = (g+h) - (i+j);
```

Corresponding RISC-V assembly code:

``` risc
add t0, g, h // t0에 g와 h를 더하여 저장
add t1, i, j
sub f, t0, t1 // f에 t0과 t1을 빼서 저장
```

### Reigisters

RISC-V(RV32I) ISA는 32 regs 을 가지며 각 32bits 크기를 가지고 있다. 32 regs 는 register file이라고 불리고 각 regs 는 from x0 to x31에서 이름(숫자)을 가지게 된다. 따라서 `add x8, x2, x5`와 같이 사용이 가능하다.

> 책은 RV64I 버전을 기반으로 적혀 있기 때문에 다른 부분이 있을 수 있다.

#### RISC-V Regs Usage

|Register Number|Name|Usage|
|-|-|-|
|x0|zero|Constant 0 (hardwired)|
|x1|ra|Return address|
|x2|sp|Stack pointer|
|x3|gp|Global pointer|
|x4|tp|Thread pointer|
|x5-x7, x28-x31|t0 - t6|Temporaries|
|x8|s0 / fp|Frame pointer|
|x9, x18-x27|s1 - s11|Saved registers|
|x10-x11|a0 - a1|Function arguments / results|
|x12-x17|a2 - a7|Function arguments|

각 숫자마다 용도가 보통 정해져 있는데 이를 지켜야 다른 software와 소통하기 편할 것이다.

### Memory

모든 데이터가 regs에 들어갈 수 없으니 보통 memory를 주 저장장치로 사용한다.

#### Using Memory Values

Arithmetic operations을 수행할 때 데이터가 memory에 저장되어 있으면 Load -> Compute -> Store하는 과정이 필요하다.(memory -> regs -> memory) 따라서 성능상으로 좋지 않기 때문에 compiler는 memory access를 최소화해야 한다.

``` c
z = x + y
```

Corresponding RISC-V assembly code:

``` risc
// memory에서 load
load x2, @x
load x5, @y

// compute
add x8, x2, x5

// memory로 store
store x8, @z
```

앞서 설명한 memory access는 위와 같이 작동하게 된다.

#### The Number of Registers is Finite

Regs가 정해진 양이 있다보니깐 쓰고 나서는 memory에 저장하고 필요하면 다시 load한다.

### Constant

Immediate Operands를 사용하면 Instruction에 Constant data를 포함 시킬 수 있다.

``` risc
add i x22, x23, 4
```

addi operand와 a negative integer value를 사용하면 되므로 불필요하게 subtract immediate instruction은 존재하지 않는다.

``` risc
addi x1, x0, 100
li x1 100
```

RISC-V regs에서 x0, zero는 constant 0을 의미하고 x0에 overwritte를 하면 안된다. Constant Zero를 사용해서 regs 간 이동 및 copy가 가능해지고 constant value를 regs로 저장할 수 있다. 또는 li instruction을 사용해서 immediate value를 load 할 수 있다.

> li는 pseudo-instuction이다.

### Multiply

만약에 32 bit x 32 bit multiply 연산을 수행하면 64 bit의 결과가 나올 수 있다. 또한 multiply은 2개의 regs가 필요하다.

> 기본적으로 RV32I 기준 ISA는 mul/div instruction은 포함되지 않았기 때문에 RV32IM 버전을 사용해야한다.

``` risc
mul x3, x1, x2
mulh x3, x1, x2 // all signed
mulhu ... // all unsigned
mulhsu ... // signed or unsigned
```

addition과 달리 signed, unsigned에 따라 다른 instruction을 가지고 있다. mul instruction은 lower 32bits를 load하지만 나머지 instruction은 upper 32bits를 load한다.

### Division

``` risc
div x3, x1, x2
rem x3, x1, x2
```

각각 나누기와 나머지를 구한 instruction이고 이또한 Unsigned version (divu, remu)이 있다.

### Logical (Bitwise, Shift)

|Operation|C|Java|RISC-V|
|-|-|-|-|
|Bitwise AND|&|&|and, andi|
|Bitwise OR|\||\||or, ori|
|Bitwise XOR|^|^|xor, xori|
|Bitwise NOT|~|~|xor, xori|
|Shift left|<<|<<|sll slli|
|Shift right|>>|>>>|srl srli srai|

- sra: Shift Right Arithmetic Shift, srl: Shift Left Logical Shift
- slli, srli의 상수부분은 0 ~ 31(32 bit기준)까지 지원한다.
- sll, srl, sra의 rs2 부분의 5 bits(0~31) 아래에 있는 양만큼 shift하게 된다.

``` risc
xori x10, x11, -1
not x10, x11
```

xori instruction을 사용해서 NOT 연산자를 구현했는데 따로 pseudo instruction(not)도 존재한다.
