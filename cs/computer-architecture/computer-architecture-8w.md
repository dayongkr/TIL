# 컴퓨터구조개론 8주 차

## pipelining

세탁기를 생각해보자. 세탁기는 wash, spin, dry 과정을 거친다. 하나의 세탁기로 3 가지 옷을 빨려고하면 세탁기를 3번 돌려야한다.

하지만 wash, spin, dry를 3개의 기계가 각각 담당한다면 하나의 옷을 spin 하는 동안 다른 옷은 wash를 할 수 있고 이에 따라 더 빠르게 세탁을 할 수 있다. 이것이 pipelining의 개념이다.

pipelining에서 하나의 step을 stage라고 부른다. 위의 예시에서 wash, spin, dry가 stage가 된다.

### Clock Period in pipeline

각 stage는 다른 clock period를 가질 수 있는데 모든 stages는 가장 긴 stage의 clock period를 따른다. 예를 들어 wash, dry는 10s spin은 20s 라고 하면 clock period는 20s가 된다. 따라서 wash가 10s만에 끝나도 10s 이후에 다음 stage로 넘어가게 된다.

> 가변적으로 clock period를 가지면 다른 작업을 할 때 제약을 받을 수 있기 때문에 가장 긴 period로 맞추는 것이 좋다. 또한 가변적으로 줄이더라도 성능상의 이점은 없다.

이러한 부분 때문에 single cycle보다 하나의 작업을 끝내는데 더 오래 걸릴 수 있다. 하지만 여러 작업을 동시에 수행할 수 있기 때문에 overall performance는 더 좋아진다.

### Pipleline Speedup

만약에 모든 stages가 같은 clock period를 가진다면 pipelining은 non-pipelining / N of stages 시간을 가질 수 있지만 이런 경우는 거의 드물다.

### RISCV-V ISA designed for pipelining

한 사이클에 decode와 fetch하기 쉽도록 32-bits instructions을 가진다. 이에 반해 x86은 1~17 byte instructions을 가진다.

주소를 load하고 store할 때 주소를 계산 하는 건 3 번째 stage에서 메모리에 접근하는 건 4 번째 stage에서 할 수 있게 디자인 되어 있다.

매우 적고 정규화된 instruction formats 덕분에 decode와 regs를 읽는 것이 한 step에 가능하다.

#### RISC-V Pipeline Stages

5가지의 stages를 가진다. 실제로 이렇게 작동하는 것은 아니지만 수업에서는 간단하게 이렇게 나누어서 설명한다.

1. IF: Instruction fetch from memory
   1. PC와 ADD하는 부분
2. ID: Instruction decode & register read
   1. Instruction을 decode해서 regs를 read하고 imm을 gen하는 부분
3. EX: Execute operation or calculate address
   1. ALU와 address에 add 계산을 하는 부분
4. MEM: Access memory operand
   1. data memory에서 데이터를 접근 하는 부분
5. WB: Write result back to register
   1. 결과를 regs에 다시 write 하는 부분

만약에 ALU가 많은 period를 가지면 ALU 자체도 pipelining을 할 수 있다. 이를 통해 balanced한 pipeline을 설계할 수 있다.

#### Pipeline Stage

combinational logic도 Flip-Flop을 중간에 넣어서 pipelining을 할 수 있다. 그리고 어디서 나누는지에 따라 Flip-Flop의 갯수가 달라져서 cost가 달라질 수 있다.

#### Simplified Representation of RISC-V Pipeline

add는 MEM Stage를 사용하지 않아도 되지만 pipelining에서는 일단 해당 과정을 거치고 넘어가야한다. 따라서 single cycle보다 단일 작업에서는 느릴 수 있다.

그림에서 네모칸에 오른쪽 반칸만 색칠된 부분은 regs file에 read 부분을 사용해서 오른쪽 반칸만 색칠했고 왼쪽만 색칠된 부분은 regs file에서 write 부분을 사용해서 왼쪽만 색칠된 것이다. 즉 왼쪽은 write, 오른쪽은 read라고 생각하면 된다. 별로 중요한 부분은 아니다.

#### Pipeline Hazards

pipeline에서는 여러가지 hazards가 발생할 수 있다.

- Data Hazards
  - data value가 아직 준비되어 있지 않는데 다음 instruction에서 해당 data를 사용해서 연산을 수행할 수 있다.
  - 이를 방지하기 위해 준비될 때까지 기다리는 방법과 연결하는 datapath를 추가해 forwarding을 사용하는 방법이 있다.
  - forwarding 방법은 데이터를 집어 넣어 주기 때문에 regs read가 필요없다.
- Structural Hazards
  - 하나의 stage를 여러 instructions이 사용하려고 할 경우이다.
  - 최대한 많은 resource를 통해 해결한다.
- Control hazards
  - data Hazards와 비슷하지만 이는 PC 변경과 관련이 있다.
  - ID stage는 작은 period를 가지니 여기다가 추가 hardware resource를 넣어서 해결한다. 해당 hardware은 branch address를 계산한다.

이를 다음 주에 더 배운다.
