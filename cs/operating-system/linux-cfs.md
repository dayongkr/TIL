# 운영체제 - 리눅스 CFS

2.4 이전에는 priority based, RR 방식으로 스케줄링을 했다. 이러한 방식은 SMP에 비효율적이고 task의 수에 따른 scalability가 떨어진다는 문제가 있어 2.4~2.6.22에서는 O(1) 스케쥴링을 통해 processor affinity, load balancing을 통한 smp 지원을 했지만 큰 서버에 이상적인 스케쥴링이어서 interactive task에 대한 스케쥴링이 떨어졌다. 이러한 문제를 해결하기 위해 2.6.23에서 Completely Fair Scheduler(CFS)가 도입되었다.

Real-time range인 0-99에서는 FIFO, RR 방식으로 스케쥴링을 하고 Nice value range인 100-139에서는 CFS 방식으로 스케쥴링을 한다.

> 기본 nice value는 0이고 범위는 -20 ~ 19이다.

## Linux scheduling policy

Linux에서는 task가 얼마나 CPU를 사용하는지 숫자로 표현하는 time slice을 직접적으로 사용하지 않고 processor의 비율을 사용하여 할당한다. 해당 비율은 nice value를 사용한 weight를 통해 결정된다.

> weight = 1024 / (1.25 ^ nice)
> proportion = weight / total_weight \* T(target)
> T(target) = 24ms

위와 같은 공식만 기억하면 되고 특징은 아래와 같다.

- nice에 따른 weight이 25%로 된 이유는 평균적으로 10%의 차이가 나도록 하기 위해서이다.
- 최소한 time slice가 1ms는 되도록 한다.

## Linux scheduling Implementation

- time accounting
  - unix
    - clock tick마다 모든 task에 대해서 time slice을 1씩 감소시킨다.
  - linux cfs
    - vruntime을 사용한다.
      - vruntime = runtime \* weight / total_weight
- task selection
  - red-black tree를 사용하여 small vruntime을 가진 task를 선택한다.
