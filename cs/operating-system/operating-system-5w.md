# 운영체제 5주 차

## process syncronization

멀티프그래밍 시스템에는 여러 프로세스가 동시에 실행되기 때문에 공유 자원에 대한 접근을 제어해야한다. 그렇지 않으면 data inconsistency를 일으킬 수 있다.

- asynchronous: 서로에 대한 상태를 알 수 없다.

### Race condition

접근 하는 특정한 순서에 따라 결과가 달라지는 상황을 말한다. 예를 들어 두 개의 프로세스에서 instruction이 실행되는 순서에 따라 결과가 달라지는 경우가 있다. 또는 context switch로 인해 결과가 달라지는 경우도 있다.

### Critical section problem

critical section은 공유 자원을 접근하는 코드 영역을 말한다. 보통 공유를 crtical이라고 표현하는 것 같다.

두 개 이상의 프로세스들이 동시에 critical section에 접근하는 것을 방지하는 것을 mutual execuison 즉 상호 배제라고 한다.

- Mutual exclusion primitive
  - enter critical section
    - enterCS(): critical section에 진입한다. -> CS에 누가 들어갔는지 알 수 있어야한다.
  - exit critical section
    - exitCS(): critical section에서 나온다. -> CS에서 나갔다는 것을 알려야한다.
  - requirements
    - mutual exclusion
    - progress
      - CS에 들어가려는 프로세스가 없으면 CS에 들어갈 수 있어야한다.
    - bounded waiting
      - 결국에는 한정적인 시도 후에 CS에 들어갈 수 있어야한다.

### Two process mutual exclusion

- ME primitives version-1
  - turn 변수를 사용한다.
  - progress requirement를 만족하지 못한다.
- ME primitives version-2
  - flag 변수를 사용한다.
  - 반복문 밑에서 interrupt가 발생하면 mutual exclusion을 만족하지 못한다.
- ME primitives version-3
  - flag 변수를 바꾸는 부분을 whlie문 위로 올린다.
  - progress requirement를 만족하지 못한다.
- Dekker's algorithm
  - flag 변수를 사용한다.
  - turn 변수를 사용한다.
  - version3에서 turn을 확인하는 부분을 추가한다.
- Peterson's algorithm
  - flag 변수를 사용한다.
  - turn 변수를 사용한다.

### N process mutual exclusion

- Dikstra's algorithm
  - IDLE, WANT_IN, IN_CS라는 3가지 상태를 사용한다.

### Hardware Instructions

- 기계어로 구현된다.
- TS
  - 값을 가져오고 값을 true로 바꾼다.
  - sharded variable인 lock을 사용한다.
  - bounded waiting을 만족하지 못한다.
  - waiting 배열을 사용하면 bounded waiting을 만족할 수 있다.
- swap
  - 값을 바꾼다.
  - bounded waiting을 만족하지 못한다.

### Semaphore

상호 배제는 busy waiting을 하기 때문에 비효율적이다. 이를 해결하기 위해 즉시 들어갈 수 없으면 block하는 방법인 semaphore를 사용한다.

Dijkstra에 의해 제안된 개념으로 P, V로 접근할 수 있는 encapsulated variable이다.

- P
  - S가 0보다 크면 S를 1 감소시키고 CS에 들어간다.
  - S가 0이면 sleep queue에 들어간다.
- V
  - CS에서 나온다.
  - CS에서 나온 프로세스가 없으면 S를 1 증가시킨다.
- Binary semaphore
  - 0 또는 1의 값을 가진다.
  - 1이면 CS에 들어갈 수 있고 0이면 CS에 들어갈 수 없다.
  - mutex라고도 한다.
- Counting semaphore
  - 0 이상의 값을 가진다.
  - producer-consumer problem을 해결할 수 있다.
- producer-consumer problem
  - 한정적인 buffer에 여러 producer가 데이터를 넣고 여러 consumer가 데이터를 빼는 문제
  - single buffer
    - 이미 사용되고 있으면 producer는 block된다.
  - multiple buffer
    - producer가 buffer를 사용할 수 있을 때까지 기다리지 않고 다른 buffer를 사용한다.
    - 보통 원형 큐로 구현한다.
    - 코드는 ppt 참조
