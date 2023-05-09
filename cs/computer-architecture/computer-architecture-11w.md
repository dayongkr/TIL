# 컴퓨터구조개론 11주 차

## Branch Hazards

branch 같은 경우에는 EX에서 계산하고 비교를 수행하기 때문에 next PC를 알 수 없다. 따라서 branch가 수행되는 동안에는 다음 명령어를 수행할 수 없다. 이를 branch hazard라고 한다.

### Rearranging pipeline stage

ALU에서 수행하던 비교 연산을 ID에서 수행하도록 하면 bubble을 줄일 수 있다. 이렇게 되면 ID의 수행시간이 길어져 clock period가 길어질 수 있다고 생각할 수 있지만 그렇게 길진 않아서 clock period가 길어지지 않는다.

하지만 만약에 비교할 register가 위에서 변경되는 경우에는 EX:MEM에서 ID로 bypass 할 수 없어서 bubble이 생길 수 있다. 이렇게되면 결국 bubble의 갯수는 같아진다. 만약에 stage가 더 많아져서 fetch에서 execute까지의 길이가 길어지면 bubble의 갯수가 더 많아질 수 있다.

> 해당 구간을 Branch penalty라고 한다.

따라서 미리 branch instruction 다음 instruction을 예상하고 만약에 실제로 branch instruction에서 비교 연산 결과 값이 다르면 예상한 instruction을 버리고 기존처럼 branch instruction을 수행한다.

### Branch prediction

Branch Prediction을 수행하기 위해서는 branch의 비교 결과와 offset을 예측하는 것이 필요하다. 수업에서는 offset을 예측하는 것은 생략하고 비교 결과만 예측하는 것을 다룬다. 그 중 제일 간단한 방법은 always taken, always not taken이다. always not taken 하면 다음 instruction을 그대로 수행하면 되기 때문에 offset을 예측할 필요가 없다. 따라서 수업에서는 해당 부분 먼저 다룬다.

만약에 예측에 성공하면 그대로 이어가면 되지만 만약에 잘못되면 IF:ID pipleline을 flush 하여 잘못 수행되던 instruction이 아무런 영향을 미치지 않도록 한다. IF:ID regs에는 instruction binary가 저장되어 있는데 이를 0x00000013으로 바꾸면 addi x0, x0, 0으로 nop instruction으로 바꿀 수 있다. 그리고 나서 pc에 pc +imm을 해주면 correct pc로 이동하게 된다.
