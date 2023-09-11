# 운영체제 3주 차

## IPC (Inter Process Communication)

정보 공유, 계산 속도, 모듈성, 편의성 등을 위해 프로세스 간에 데이터를 주고 받는 것으로 크게 두 가지 방법이 있다.

- Message Passing
  - 커널을 통해 메시지를 주고 받는 방법
  - send(), receive() system call
  - waiting하는 blocking 방식과 waiting하지 않는 non-blocking 방식이 있다.
- Shared Memory
  - 커널을 통하지 않고 메모리를 공유하는 방법
  - read, write system call

distributed system에서는 아래와 같은 방법이 있다.

- RPC (Remote Procedure Call)
  - stub와 RPC Runtime System을 통해 메시지를 주고 받는 방법
- RMI -> JVM에서 사용하는 RPC
- LRPC (Lightweight RPC)
  - 같은 컴퓨터에서 사용하는 RPC
- DSM
  - Distributed Shared Memory

distributed system은 간단히 설명하시고 넘어갔다.

## Process Scheduling

프로세서 사용률을 높이기 위한 멀티프로그래밍을 위해 프로세스를 스케쥴링한다. 이를 위해서는 time sharing, space sharing이 필요한데 오늘은 time sharing에 해당하는 스케쥴링에 대해 배웠다.

### Performance Indices

단순히 성능이라고 하면 모호하므로 성능을 측정하는 지표가 필요하다.

- Mean response time
  - 프로세스가 처음으로 요청을 한 시간부터 응답의 시작을 받는 시간까지의 평균
- Throughput
  - 단위 시간당 완료된 프로세스의 수
- Resource utilization
  - 단위 시간당 프로세서가 사용된 시간의 비율
- Turnaround time
  - 프로세스가 처음으로 요청을 한 시간부터 완료되는 시간까지의 평균
  - response time과는 다르게 완료되는 시간을 기준으로 한다.
- Waiting time
  - 프로세스가 ready queue에서 기다리는 시간
- Predictability
  - 프로세스가 얼마나 예측 가능한지
- Fairness
  - 프로세스가 얼마나 공평하게 스케쥴링 되는지

Mean response time은 interactive system에서 주로 사용되고 throughput, resource utilization은 batch system에서 주로 사용된다. 그리고 Mean response time과 resource utilization은 trade-off 관계이다.

### Scheduling Criteria

- process characteristics
  - CPU bound or I/O bound
    - I/O bound process부터 스케쥴링한다.
  - Batch(다른 일중) or interactive(기다리는 중)
    - interactive process부터 스케쥴링한다.
- Urgency
  - Hard real-time system
    - deadline이 존재하는 시스템
  - Soft real-time system
  - Non real-time system
- Process type and importance
- Service time
  - CPU burst time (짧은 시간 동안 CPU를 사용하는 시간)
- Process priority
  - 우선순위가 높은 프로세스부터 스케쥴링한다.

### Scheduling Levels

- Long-term scheduling
  - job scheduling
  - 메모리에 올라갈 프로세스를 선택한다.
  - 요즘에는 메모리가 충분하므로 잘 사용되지 않는다.
  - I/O bound와 CPU bound의 비율을 조절한다.
- Medium-term scheduling
- Short-term scheduling
  - CPU scheduling
  - CPU를 할당받을 프로세스를 선택한다.

### Scheduling Policies

- Preemptive
  - 프로세스가 CPU를 할당받은 후에도 다른 프로세스가 CPU를 빼앗을 수 있다.
  - 우선순위가 높은 프로세스가 CPU를 빼앗을 수 있다.
  - context switching이 발생한다.
- Non-preemptive
  - 프로세스가 CPU를 할당받은 후에는 다른 프로세스가 CPU를 빼앗을 수 없다.
  - 프로세스가 CPU를 반납할 때까지 기다려야 한다.
- Priority
  - static priority
    - 프로세스가 생성될 때 우선순위가 결정된다.
  - dynamic priority
    - 프로세스가 실행되는 동안 우선순위가 결정된다.

### Terminology

- CPU burst
  - CPU를 사용하는 시간
- I/O burst
  - I/O를 기다리는 시간

### Scheduling Schemes

- Arrival time
  - FCFS (First Come First Served)
    - 먼저 도착한 프로세스부터 스케쥴링한다.
    - non-preemptive
    - batch system에 적절
    - convoy effect
      - CPU burst time이 긴 프로세스가 먼저 도착하면 뒤에 있는 프로세스들이 기다려야 한다.
  - RR (Round-Robin)
    - FCFS와 유사하나 time quantum이라는 개념이 추가된다.
    - time quantum이 지나면 다른 프로세스에게 CPU를 넘겨준다.
    - preemptive
    - time quantum이 너무 크면 FCFS와 같아지고 너무 작으면 context switching이 자주 발생한다.
- Burst time
  - SPN (Shortest Process Next)
    - CPU burst time이 가장 짧은 프로세스부터 스케쥴링한다.
    - non-preemptive
    - waiting time을 최소화한다.
    - starvation이 발생할 수 있다.
      - aging 개념을 사용해서 해결할 수 있다.
    - burst time을 예측해야한다.
  - SRTN (Shortest Remaining Time Next)
    - SPN의 preemptive 버전
    - 현재 실행중인 프로세스의 남은 burst time과 ready queue에 있는 프로세스의 burst time을 비교해서 짧은 프로세스가 있으면 CPU를 빼앗는다.
  - HRRN (Highest Response Ratio Next)
    - Response ratio = (waiting time + burst time) / burst time
    - Response ratio가 가장 높은 프로세스부터 스케쥴링한다.
    - starvation을 방지할 수 있다.
    - 나머지는 SPN과 유사하다.
