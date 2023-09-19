# 운영체제 3주 차 복습

## IPC

- Message Passing
  - Network protocol 사용
  - 각자 memmory space를 가지고 있다.
- Shared Memory
  - Network protocol 사용하지 않음
  - 하나의 memory space를 공유한다.
- RPC
  - client stub에 함수를 정의해두고 해당 함수가 호출되면 RPC Runtime을 통해 server stub에 함수를 호출한다.
  - system call link와 유사하다.
- DSM
  - Distributed Shared Memory
  - 공유하는 물리적 memory가 없다.
  - 각자의 memory space를 가지고 있지만 공유하는 logical memory가 있다.
