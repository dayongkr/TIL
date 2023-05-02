# 컴퓨터구조개론 10주 차

## Pipeline Hazards

### Data Hazards in ALU Instructions

Reg write를 하면 다음 clock에 쓰여지기 때문에 이 전에 다른 instruction에서 old value를 읽어오면 문제가 생긴다.

이는 additional data path를 만들어서 해결할 수 있는데 만약에 read regs id와 write regs id가 같으면 bypass를 해서 해결한다. 이러한 bypass circuit이 regs file에 embedded 되어 있다고 가정하고 설명한다.

지금까지는 추상적으로 설명했지만 실제로는 이렇게 설계되어 있다. 일단 먼저 pipeline에 alu result를 저장하고 이를 다음 사이클에서 사용한다. 하지만 이러한 데이터가 original path에 전달되므로 여기에 mux를 추가해서 이 중에 선택을 할 수 있게 한다. mux의 조건은 pipeline을 통해 전달된 rs1 또는 rs2가 rd와 같은지를 확인한다.

#### Register Forwarding Condition

- EX Hazard
  - MEM에서 rd와 같은 rs1, rs2를 사용하는 경우
  - EX/MEM pipeline에서 forward한다.
- MEM Hazard
  - WB에서 rd와 같은 rs1, rs2를 사용하는 경우
  - MEM/WB pipeline에서 forward한다.

이러한 condition check은 forwarding unit에서 담당한다. 여기서 forward가 필요한지 detect 하는데 실제로 regsiter write가 발생하고 rd가 zero가 아닌 경우에만 위의 codition check를 통해 forward를 한다. 이는 control signal을 통해 수행한다.

만약에 hazard가 동시에 발생한다면 가장 최근에 것을 선택한다. 따라서 EX와 MEM Hazard가 동시에 발생한다면 EX Hazard를 선택한다.
