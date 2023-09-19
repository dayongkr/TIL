# 운영체제 4주 차

## Schedule Schemes

- Priority Scheduling
  - Priority가 높은 프로세스를 먼저 실행한다.
  - priority의 범위나 높은 부분이 어디인지는 OS마다 다르다.
- MLQ(Multi-Level Queue)
  - 여러 개의 queue를 두고 queue마다 priority를 다르게 한다.
  - 고정된 priority를 가지고 있다.
- MFQ(Multi-Level Feedback Queue)
  - MLQ와 비슷하지만 priority가 고정되어 있지 않다.
  - sleep 상태에서 꺠어나면 기존 queue로 가고 preemption이 발생하면 priority가 낮은 queue로 간다.
  - 따라서 cpu burst time이 적은 IO bound process를 선호하는 경향이 있다.
  - Starvation과 overhead가 발생하는데 이를 해결하기 위해 아래의 방법을 사용한다.
    - 각 프로세스의 time quantum을 다르게 한다.
    - 오래 기다리면 priority를 높인다.
    - wake up하면 priority를 높인다.

## Case Studies

### Unix

- Priority Scheduling
- Kernel priority, user priority
  - 0 ~ 59: kernel priority
    - kernel process (interruptible, uninterruptible로 나뉜다.)
  - 60 ~ 127: user priority
    - user process
- MFQ와 유사하다.
- Priority adjustment
  - Decay computation
    - CPUCount = CPUCount / 2
  - Priority adjustment
    - Priority = CPUCount / 2 + BasePriority + niceValue
    - niceValue는 user가 설정할 수 있다.
  - 실행되면 CPUCount가 증가하는데 이를 통해 Priority를 조절한다.
  - FSS(Fair Share Scheduler)
    - Process 일부를 group으로 묶어서 group time과 자기의 time을 더해서 priority를 계산한다.

### Windows

- Priority Scheduling (Preeemptive)
- 32 priority levels
  - 1 ~ 15: Real-time
  - 16 ~ 32: Variable
- priority class
  - REALTIME_PRIORITY_CLASS (real-time)
  - HIGH_PRIORITY_CLASS (variable)
  - ABOVE_NORMAL_PRIORITY_CLASS (variable)
  - NORMAL_PRIORITY_CLASS (variable)
  - BELOW_NORMAL_PRIORITY_CLASS (variable)
  - IDLE_PRIORITY_CLASS (variable)
- relative priority
  - TIME_CRITICAL
  - HIGHEST
  - ABOVE_NORMAL
  - NORMAL
  - BELOW_NORMAL
  - LOWEST
  - IDLE
- 위 두가지로 값들이 결정된다.
- sleep 상태에서 깨어나면 priority가 높아진다
  - IO 종류에 따라 priority가 다르게 설정된다.
  - Keyboard, Mouse는 크게 증가하고 Disk는 비교적 적게 증가한다.
- preemption이 발생하면 priority가 낮아진다.
- In windows 7
  - UMS -> application이 각자의 thread를 가지고 있고 schedule할 수 있다.

### Linux

- 2.4 이상에서는 O(1), O(n) scheduling을 사용한다.
  - 이를 통해 SMP(Symmetric Multi-Processing)을 지원한다.
    - SMP: 여러 개의 CPU를 사용하는 것
  - task의 수가 많아지면 scheduling하기가 어렵던 것을 해결한다.
- 다양한 scheduler를 사용하는데 우리는 주로 CFS(Completely Fair Scheduler)를 다룬다
- O(logN) scheduling이다.
- Real-time range: 0 ~ 99
- Normal range: 100 ~ 139
  - 이때 CFS를 사용한다.
- realtime task는 static priority를 가지고 있고 normal task는 dynamic priority를 가지고 있다.
- CFS는 Red-Black Tree를 사용한다.

### Multicore Scheduling

- Processor Affinity
  - 프로세스가 어떤 core에서 실행될지 결정한다.
  - Soft affinity
    - 같은 core에서 실행되는 것을 선호하지만 다른 core에서 실행될 수 있다.
  - Hard affinity
    - 같은 core에서 실행되어야 한다.
- Load balancing
  - 일을 잘 분배해서 균등하게 처리하는 것
  - push migration
    - 일을 많이 하는 core에서 일을 적게 하는 core로 일을 넘긴다.
  - pull migration
    - 일을 적게 하는 core에서 일을 많이 하는 core로 일을 넘긴다.
  - 보통 둘다 사용한다.
