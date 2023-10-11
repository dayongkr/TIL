# 운영체제 7 ~ 8주 차

## Deadlock

Deadlock이 발생하려면 아래의 4가지 조건이 모두 성립해야 한다.

- Exclusive use of resources
  - 한 번에 한 프로세스만 사용할 수 있는 자원
- Non-preemptable resources
  - 자원을 강제로 빼앗을 수 없는 자원
- Hold and wait
  - 자원을 가지고 있으면서 다른 자원을 기다리는 상태
- Circular wait
  - 자원을 기다리는 프로세스가 원형으로 연결되어 있는 상태

### Deadlock resolution

Deadlock을 해결하는 방법은 아래와 같다.

- Deadlock prevention
  - 위 4가지 조건 중 하나를 제거한다.
  - 사실상 불가능하고 비효율적이다.
  - witness
    - 적절한 순서대로 자원을 요청하면 Deadlock을 방지할 수 있다.
- Deadlock avoidance
  - 프로세스가 자원을 요청할 때 safe state인지 확인한다.
  - safe state
    - Deadlock이 발생하지 않는 상태
  - unsafe state
    - Deadlock이 발생할 수 있는 상태
  - 여러 가정이 필요해서 실질적으로 사용하기 어렵다.
  - 다익스트라: 하나의 rsouce type만 존재하는 경우에만 사용 가능하다.
  - banker's algorithm: 여러 개의 resource type이 존재하는 경우에도 사용 가능하다.
  - 둘 다 적절한 순서대로 자원을 요청하면 Deadlock을 방지할 수 있다.
- Deadlock detection and recovery
  - Deadlock이 발생하면 recovery한다.
  - resource allocation graph으로 deadlock을 감지한다.
    - 요청보다 할당 가능한 자원이 더 많으면 unblocked process이다.
  - unblocked process에 해당하는 edge를 모두 지웠을 때에도 edge가 남아있으면 Deadlock이다.
  - deadlock 현재 발생하고 있는지만 확인한다.
  - recovery
    - process를 kill한다.
      - lowest priority process를 kill한다. -> 불필요한 프로세스까지 kill할 수 있다.
      - minimum cost recovery -> 알맞는 process를 찾는데 시간이 오래 걸린다.
    - resource를 preempt한다.
      - context saving을 주기적으로 해서 partial rollback을 할 수 있다.
