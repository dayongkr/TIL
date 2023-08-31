# 운영체제 1주 차

2012년 기준 위키피디아에 나와있는 운영체제의 정의는 하드웨어와 유저의 인터페이스로 나와있고 OS를 host, application을 guest로 묘사하고 있다.

현재에는 하드웨어, 자원 그리고 일반적인 서비스들을 제공하는 시스템 소프트웨어라고 나와 있다.

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

Bootstrap program가 boot program을 디스크에서 부터 가져오고 boot program은 kernel을 메모리에 올린다. (즉 2 단게에 걸쳐 부팅이 된다.)

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

### Process management

- Process scheduling
  - CPU에 어떤 process를 할당할 것인가
- Processor assignment
  - 어떤 CPU에 할당할 것인가
- PCB
  - Process Control Block 프로세스를 관리하는 자료구조

### Memory management

- multi-user, multi-tasking일 때
  - 메모리 할당/해제
  - 빈 공간 관리
  - 메모리 보호

### File management

- 유저 입장에서는 계층 구조를 가진 파일 시스템을 제공
- 백업은 별도의 프로그램으로 OS의 역할이 아니다.
- File이란 논리적인 단위

### I/O management

- 프로세스가 OS로 System call을하면 OS는 I/O request를 I/O device로 날리고 I/O device는 Interrupt를 발생시키면 이를 다시 프로세스로 넘겨준다.
- Buffer pool
  - I/O device와 바로 연결되어 있지 않고 buffer pool을 통해 연결되어 있다.
  - 단 키보드등과 같이 주고 받는 데이터가 적은 경우에는 바로 연결되어 있다.

## Dual Mode

- User mode
  - 응용 프로그램이 실행되는 모드
- Kernel mode
  - OS가 실행되는 모드
- 1-bit에 의해 구분
- trap 또는 interrup가 발생하면 모드가 바뀐다.
- Interrupt
  - 예상치 못한 외부 이벤트
  - 하드웨어와 소프트웨어 둘다 발생한다
- Trap
  - 소프트웨어에 의해 발생하는 interrupt
  - Exception
    - 실행 프로그램의 오류
  - System call
    - 프로그램이 OS의 서비스를 받기 위해 발생하는 interrupt
    - 프로그램 및 프로세스와 OS의 인터페이스
    - trap instruction에 의해 발생
  - Privileged instruction
    - 오류가 발생하면 안되는 중요한 명령어
    - kernel mode에서만 실행될 수 있다.
    - I/O, timer, interrupt 관리, user mode로 변환
