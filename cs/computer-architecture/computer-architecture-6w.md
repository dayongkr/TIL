# 컴퓨터구조개론 6주 차

## The Processor

Architecture 중 micro-architecture은 cpu의 internal을 의미한다. 외부적으로는 같은 interface을 가지고 있지만 내부적으로는 다른 구조를 가지고 있을 수 있다.

Micro-architecture의 예는 아래와 같다.

- Single-cycle
  - 한 사이클에 한 명령어를 처리한다.
- Pipelined
  - 실행이 여러 단계의 사이클로 나누어져 있다.

우리가 앞으로 다룰 예제는 RISC-V ISA의 몇가지만 지원한다. (add, sub, and, or, lw, sw, beq)

### What Happens in CPU

- Default
  - Fetch
    - Instruction을 메모리에서 가져온다.
    - RISC-V에서는 instruction이 4byte로 고정이라서 간단하게 구현이 가능
  - Decode
    - Opcode를 사용해서 instruction의 type을 파악한다.
- Arithmetic/Logic instructions: add, sub, and, or
  - Add 4 to PC
    - 아래 연산과 독립적으로 동시에 수행된다.
  - register에서 two operand values(rs1, rs2)를 가져온다.
  - 연산을 수행
  - 결과를 regs file(rd)에 저장
- Memory access
  - Add 4 to PC
  - lw
    - regs file에서 1 word를 읽어온다.
    - base address에 offset을 더한다
    - 메모리에서 1 word를 읽어온다. (Address: base address + offset)
    - regs file에 저장
  - sw
    - regs file(rs1)에서 1 word를 읽어온다.
    - base address에 offset을 더한다
    - regs file(rs2)에서 1 word를 읽어온다.
    - 메모리에 저장 (Address: base address + offset)
- Control transfer: beq
  - 2 words를 regs에서 읽어옴(rs1, rs2)
  - 비교 연산 수행(빼기 연산을 통해서)
  - if \*rs1 == \*rs2
    - PC = PC + imm
  - else
    - PC = PC + 4
  - PC는 beq 명령어가 수행되는 주소이다.

Single-cycle CPU는 (PC, Instruction memory)와 (Regsiters, ALU, Data memory)는 서로 독립적으로 구성되어 있어서 동시에 수행될 수 있다.

### Data Memory?

수업에서 Instruction memory와 Data memory를 분리해서 사용하지만 사실 같은 main memory 안에 존재한다. 다만 processor 입장에서는 분리된 cache memory를 사용하기 때문에 분리해서 memory를 사용하는 것처럼 보이는 것이다.

### Logic Design Basics

- Combinational Logic
  - 출력은 현재 입력일 뿐이다.
  - 매우 적은 delay를 가진다
- Sequential Elements (Flip - Flops)
  - data를 저장하고 0에서 1로 바뀌는 clock signal에 의해 업데이트된다.
  - clock 한 주기에 input이 바뀌면 output은 마지막 input으로 업데이트된다.
  - 이러한 기본적인 design말고 write라는 signal을 추가해서 input이 바뀌는 것을 막을 수 있다.
    - 1이 들어오기 전까지는 input을 update하지 않다가 1이 들어오면 update하는 방식이다.
- Wires
  - 0과 1이 wires를 통해 이동한다.
  - 한 wire에 1 bit가 이동한다.
- Counters
  - 2bit으로 구성되어 있으며 clock signal에 의해 0에서 3까지 순차적으로 바뀐다.

### Instruction Fetch

- PC
  - Program Counter
  - 현재 instruction의 주소를 가지고 있다.
- Instruction Memory
  - 다음에 동작 방식을 배우고 지금은 combinational logic으로 가정한다
  - PC로 부터 Address를 받으면 instruction을 return한다.

PC에서 Instruction Memory에 접근해서 instruction을 가져오는 동시에 Add 4를 하는 combinational logic을 동시에 수행해서 PC에 저장한다.

### R-Format (add, sub, and...)

R-Format는 2 regs operands를 읽고 arithmetic/logic operation을 수행한 후 regs에 저장한다.

Register File에서 현재 명령어로 부터 regsiter ID를 읽고 regs에 상응하는 현재 값을 가져온다. 이러한 Read는 combinational logic처럼 행해진다. 하지만 Write는 clock signal에 의해 동작해서 sequential logic으로 구현된다.

더 자세히 Read를 보자면 일단 32개의 regs와 연결된 MUX를 통해 원하는 regs를 선택해서 값을 얻을 수 있다.

write도 자세히 보자면 write regs는 먼저 32 bits의 one-hot-encoding을 하고 n-to-2^n Decoder을 통해 0을 제외한 31개의 regs 중 하나를 선택하고 RegWrite signal이 1이면 write를 수행하고 0이면 write를 수행하지 않는다.

#### one hot encoding

32개의 regs 중 하나를 선택하기 위해서는 32개의 MUX를 사용해야 한다. 하지만 32개의 MUX를 사용하면 32개의 wire가 필요하고 이는 매우 비효율적이다. 그래서 32개의 regs 중 하나만 1이고 나머지는 0인 32 bits의 값을 만들어서 32개의 MUX를 1개의 MUX로 대체한다. 이를 one-hot-encoding이라고 한다.
