# 운영체제 6주 차

## Mutual Exclusion

### Semaphore

Semaphore는 busy waiting을 하지 않고 mutual exclusion을 구현할 수 있는 방법이라고 저번 시간에 배웠고 이번 시간에는 semaphore로 reader-writer problem을 해결하는 방법을 배웠다.

- Semaphore 특징
  - no busy waiting
  - no scheduling for wake up
    - 기다리고 있는 아무 프로세스나 꺠우기 때문에 scheduling이 필요 없다.

#### Reader-Writer Problem

Reader는 공유 자원을 읽기만 하고 writer는 공유 자원을 수정할 수 있기 때문에 writer가 공유 자원을 사용하고 있을 때에는 reader, writer 모두 접근할 수 없어야 한다.

이러한 문제는 semaphore를 이용하여 해결할 수 있다. reader 부분에서는 nreader를 사용해서 reader가 접근할 때마다 nreader를 1씩 증가시키고 writer 부분에서는 nwriter를 사용해서 writer가 접근할 때마다 nwriter를 1씩 증가시킨다. nreader가 0 이면 write lock 거는 식으로 구현하면 된다.

#### Dining Philosopher Problem

Dining Philosopher Problem은 5명의 철학자가 원형 테이블에 앉아서 식사를 하는데, 각자의 앞에는 포크가 하나씩 놓여져 있다. 철학자는 식사를 하기 위해서는 포크를 두 개 모두 들어야 한다. 이러한 상황에서 각자의 앞에 있는 포크를 들기 위해서는 다른 철학자가 들고 있는 포크를 내려놓아야 한다. 이러한 상황에서 모든 철학자가 식사를 할 수 있도록 포크를 들고 놓는 순서를 정하는 문제이다.

이러한 문제도 semaphore를 이용하여 해결할 수 있다.

### Spinlock

Spinlock은 busy waiting을 하면서 mutual exclusion을 구현할 수 있는 방법이다. 이 방법은 semaphore와 달리 busy waiting을 하기 때문에 CPU를 많이 사용하게 되고, context switching이 일어나지 않기 때문에 성능이 좋다. 따라서 multiprocessor에서 사용하기 좋다.

- P(S)
  - S가 0보다 크면 S를 1 감소시키고, 아니면 busy waiting
- V(S)
  - S를 1 증가시킨다.

### Eventcount / Sequencer

ticket lock이라고도 불리는 eventcount는 은행 대기열에서 사용하는 방법으로 FIFO 방식으로 동작한다.

- Sequecer
  - 마지막 번호를 저장하는 변수
  - ticket(S): 마지막 번호를 1 증가시키고 그 값을 반환
- Eventcount
  - 현재 처리할 번호를 저장하는 변수
  - read(E): 현재 처리할 번호를 반환
  - advance(E): E에 해당하는 process를 wake up하고 E를 1 증가시킨다.
  - await(E, v): 만약에 v가 E보다 작으면 waiting queue에 넣는다.

보통 ticket을 통해 번호를 받고 해당 번호를 사용해서 await을 호출한다. 그리고 advance를 통해 다음 번호를 처리하고 있는 process를 깨운다. 이를 통해 Mutual Exclusion을 구현할 수 있다.

- Producer-Consumer Problem
  - Producer용 sequence, eventcount 그리고 Consumer용 sequence, eventcount를 만들고 각 상대방의 eventcount와 await를 사용해서 full과 empty를 구현해서 Producer와 Consumer가 동시에 접근하지 못하도록 한다.
- busy waiting을 하지 않는다
- no starvation
  - FIFO 방식으로 동작하기 때문에 starvation이 발생하지 않는다.

## Case Studies

- Solaris
  - Adaptive mutex
    - 다른 CPU에서 사용되고 있으면 spinlock을 사용하고, 아니면 semaphore를 사용한다.
    - uniprocessor에서는 무조건 semaphore를 사용한다.
  - 보통 short code일 땐 adaptive mutex를 사용하고, long code일 땐 semaphore를 사용한다.
  - reader-writer locks
    - reader-writer problem을 해결하기 위해 사용한다.
  - turnstiles
    - block된 threads들을 포함하기 위한 queue 자료구조
- Windows XP
  - Interrupt masking
    - uniprocessor에서 사용
  - Spinlock
    - multiprocessor에서 사용
  - kernel 밖에서는 dispatcher object를 사용
    - signaled / non-signaled
      - signaled: ready
      - non-signaled: waiting
- Linux
  - 지금까지 배운 것들을 모두 사용한다.
  - SMP
    - spinlock (for short code)
    - semaphore (for long code)
  - UP
    - enable/disable preemption
  - Pthreads
    - 쓰레드 표준으로 Mutex, Condition variable, Reader-writer lock을 제공한다.

## Deadlock

Deadlock은 깨어날 가능성이 0인 waiting 상태를 말하는 것으로 starvation과는 다르다. 먼저 resource의 종류를 나누어서 생각해보자.

### Classifying Resources

- Preemptable or Non-preemptable
  - Preemptable: preempted 되어도 큰 문제가 없는 resource
  - Non-preemptable: preempted 되면 큰 문제가 생기는 resource (rollback이나 restart가 필요)
- Total or Partial
  - Total: resource를 전체를 할당해야 하는 resource
  - Partial: resource를 일부만 할당해도 되는 resource
- Exclusive or Shared
  - Exclusive: 한 번에 하나의 process만 사용할 수 있는 resource
  - Shared: 여러 개의 process가 동시에 사용할 수 있는 resource
- SR (Serially Reusable) or CR (Concurrently Reusable)
  - SR: 영구적으로 시스템에 존재하는 resource
  - CR: process에 할당되면 시스템에 사라지는 resource

우리는 이중 Non-preemptable, Exclusive, SR인 resource에 대해서만 생각하면 된다.

### Example Deadlock

- Resource
  - R1, R2
- Process
  - P1, P2

가 있을 때 P1이 R1을 할당받고 P2가 R2를 할당받고 P1이 R2를 요청하고 P2가 R1을 요청하면 deadlock이 발생한다.
