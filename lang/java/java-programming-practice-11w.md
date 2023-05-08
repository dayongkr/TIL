# 자바프로그래밍실습 11주 차

## Multithreading

Thread란 instructions의 가장 작은 단위로 OS scheduler에 의해 독립적으로 관리된다. thread와 process의 구현은 OS에서 다르다 하지만 대부분의 경우는 thread는 process의 일부로 구현된다.

### Life Cycle of a Thread

- New: thread가 생성되었지만 아직 start()가 호출되지 않은 상태
- Runnable: start가 호출되어 run()을 호출할 수 있는 상태
- Running: thread가 실행중인 상태
- Waiting: thread가 다른 thread가 특정 작업을 마칠 때까지 기다리는 상태
- Dead: thread가 실행을 마친 상태

### Thread Priorities

모든 Java thread는 priority를 가지고 있는데 이는 thread를 schedule 할 때 결정하는 요소이다. thread priorities의 범위는 1~10이며 숫자가 높을수록 우선순위가 높다. static하게 MIN_PRIORITY, NORM_PRIORITY, MAX_PRIORITY를 가지고 있다.

> 하지만 순서를 보장하지 않는다.

### Creating a Thread

- Runnable interface를 구현하는 방법
  - run() method를 구현한다.
  - instantiate a Thread object
  - start() method를 호출한다.
- Thread class를 상속하는 방법
  - run() method를 override한다.
  - start() method를 호출한다.
  - 좀더 flexible하다.

### Thread Static Method

- run
  - thread가 실행할 코드를 정의한다.
- sleep
  - thread를 일정 시간동안 sleep시킨다.
  - millisecond 단위로 정의한다.
- holdsLock
  - 현재 thread가 특정 object의 lock을 가지고 있는지 확인한다.

### BlockingQueue

이번에 주차 과제를 하면서 BlockingQueue를 사용하게 되었는데 이를 사용하면 thread간의 communication을 쉽게 할 수 있다. 만약에 buffer가 비어있으면 이를 take 하려는 thread를 block시키고 buffer가 꽉 차있으면 put 하려는 thread를 block시킨다. 덕분에 thread간 communication을 쉽게 할 수 있다.
