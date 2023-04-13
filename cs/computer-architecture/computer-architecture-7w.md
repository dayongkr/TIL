# 컴퓨터구조개론 7주 차

## Load/Store Instruction

하나의 ALU는 R-type의 Arithmetic/Logic과 Load/Store address 계산에 사용된다.

ALUOp이 R-type인지 확인하고 ALUSrc로 Imm를 ALU에 보낼지 Reg의 값을 보낼지 결정한다. MemtoReg가 1이면 Data Memory에서 읽은 값을 Reg에 저장하고 아니면 ALU의 결과를 Reg에 저장한다.

Read Data를 할 때 Data를 Little Endian으로 읽는다.

## Branch Instruction

만약에 rs1과 rs2가 같다면 Branch를 한다. Branch는 PC에 Imm를 더한 값을 저장한다.

ALU는 rs1과 rs2를 빼서 0이면 둘이 같다는 사실을 통해서 같다고 판단한다.

따라서 기존에는 +4를 더하는 부분 있었다면 Imm를 현재 PC에 더하는 부분을 추가하고 0이면 Imm을 더한 것을 사용하는 MUX를 통해 브랜치를 하게 된다.

0인 것을 확인하는 방법은 Branch & ALU Result(Zero?)를 통해 확인한다.

## Control Signals

Opcode를 기반으로 Control Signals를 결정한다. 이는 combinational logic으로 구현된다.

RegWrite가 0이라면 어차피 Data Memory에서 Write Data가 와도 무시되기 때문에 MemtoReg는 의미가 없다.

7개의 inputs을 받는 Bigger AND gate를 통해 각 Control Signal을 결정한다. input에 있는 동그라미는 세모가 생략된 것이고 invert를 하는 부분이다.

물고기 꼬리 같이 생긴 부분은 Bigger OR Gate이다.

## AUIPC Instruction

Upper Immediate(imm[31:12] + 0(lower 12 bits))를 PC에 더한 값을 Reg에 저장한다.

기존의 BEQ, JAL은 각각 13bit, 21bit 범위로 Jump를 할 수 있지만 이와 같은 AUIPC, LUI와 JALR을 사용하여 32bit 범위로 Jump를 할 수 있다.

```asm
lui x5, 0x12345 // x5 = 0x12345000
jalr x1, 0x678(x5) // jump to 0x12345678
```

```asm
auipc x5, 0x12345 // x5 = PC + 0x12345000
jalr x1, 0x678(x5) // jump to PC + 0x12345678
```

lui는 absolute address를 사용하고 auipc는 pc relative address를 사용한다.

## Combinational Logic Propagation Delay

각 gate는 delay가 있다. 따라서 output이 바뀌는데 걸리는 시간이 있다. 이를 combinational logic propagation delay라고 한다.

따라서 1 Clock의 주기를 모든 Instruction의 Propagation Delay를 포함할 수 있도록 가변적으로 주기를 변경한다. 따라서 Single Cycle CPU는 이러한 불필요한 제한 때문에 성능이 떨어진다.

### Performance Issues

Critical Path는 가장 긴 Propagation Delay를 가지는 Path이다. load instruction의 경우 ALU의 Propagation Delay가 가장 긴 것이므로 Critical Path가 된다.

이를 해결하기 위해 pipelining을 사용한다.
