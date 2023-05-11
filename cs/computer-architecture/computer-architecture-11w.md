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

### More Realistic Branch Prediction

지금까지는 Static branch prediction 방법을 다뤘다. 즉 typical branch behavior을 기반으로 예측을 수행했다. 예를 들어 loop과 if 문이 있으면 backward branch는 taken으로 예측하고 forward branch는 not taken으로 예측한다. 왜냐하면 backward branch는 보통 loop에서 사용되는데 loop 같은 경우에는 대부분 taken으로 수행되기 때문이다. 반대로 forward branch는 보통 if 문에서 사용되는데 if 문 같은 경우에는 어차피 한번만 수행되기 때문에 not taken으로 예측한다.

이러한 방법 말고 Dynamic branch prediction 방법도 있다. 즉 branch history를 기반으로 예측을 수행한다. branch history는 branch instruction이 수행될 때마다 branch history table(Branch Prediction Buffer)을 업데이트 한다. branch history table은 branch instruction의 address를 index로 하고 해당 branch instruction의 behavior를 저장한다. 이때 branch instruction의 result만 저장하는 것이 아니라 다른 instruction도 저장한다. 이렇게 되면 instruction memory / 32 만큼의 공간이 필요하다.

1-bit로 위 branch result를 저장하면 0이면 not taken, 1이면 taken으로 저장한다. 이렇게 되면 double loop 같은 경우에는 all incorrect prediction이 발생한다. 이러한 문제를 해결하기 위해서 2-bit branch prediction을 사용한다. 2-bit predictor은 앞 비트는 not taken, taken을 의미하고 뒤 비트는 strongly와 weekly를 의미하고 00부터 taken이 일어날 때 +1 하고 not taken이 일어나면 -1을 한다.

또한 Branch Prediction Buffer도 한 index을 여러 instructions이 함께 사용함으로써 메모리 공간을 줄이기도 한다. 다만 이렇게되면 공유하는 다른 instruction의 branch 결과의 영향으로 다른 instruction의 branch prediction이 실패할 수 있다.

## 마무리

지금까진 taken branch를 예측하는 방법에 대해서 다뤘다. 이 외에 target address를 예측하는 방법이 필요한데 이는 다루지 않는다.

> Branch Prediction buffer와 같이 Branch Target Buffer도 존재한다.
