# 운영체제 1주 차

2012년 기준 위키피디아에 나와있는 운영체제의 정의는 하드웨어와 유저의 인터페이스로 나와있고 OS를 host, application을 guest로 묘사하고 있다.

현재에는 하드웨어, 자원 그리고 일반적인 서비스들을 제공하는 시스템 소프트웨어라고 나와 있다.

## 운영체제의 역할

- User Interface
  - System call interface
  - Command line interface, GUI 등
- Resource Manager
  - Process Manager
  - Memory Manager
  - File Manager
  - I/O Manager
- Process Manager
  - Proccess도 자원이지만 따로 분류
  - 더 나아가 Thread manager도 따로 분류
- Network Manager / Security & Protection

## 운영체제의 유형

- Number of concurrent users
  - Single-user
    - 한 유저가 시스템의 모든 자원을 사용
    - 개인 컴퓨터에 주로 사용
  - Multi-user
    - protection mechanism이 필요
    - 서버에 주로 사용
    - UNIX, Linux 등
- Number of concurrent tasks
  - Single-tasking
  - Multi-tasking
    - 동시성 제어 그리고 싱크 메커니즘 필요
- Job processing
  - Batch processing
  - Interactive processing
  - Real-time processing
  - Cloud computing

## 운영체제의 구조

- Kernel
  - OS의 핵심
  - booting 시에 메모리에 올라가는 부분
  - 자주 사용되는 함수들을 지원한다
- Utilities
  - 메모리에 올라가지 않고 필요할 때마다 불러와서 사용하는 부분

### Booting

Bootstrap program
