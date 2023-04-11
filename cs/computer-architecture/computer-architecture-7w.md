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
