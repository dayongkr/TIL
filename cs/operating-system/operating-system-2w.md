# 운영체제 2주 차

오늘은 가상화와 프로세스 관리에 대해 배웠다.

## 가상화

가상화 중 hardware virtualization과 os virtualization을 배웠다.

### Hardware Virtualization

host machine을 virtual machine으로 나누어서 사용하는 것이다. 이때 host machine은 hypervisor라는 소프트웨어를 통해 virtual machine을 관리한다.

만약에 guest machine에서 system call을 하게 되면 hypervisor를 통해서 host machine의 system call을 호출하게 된다.

### OS Virtualization

여러개의 user-space instance(container)를 만들어서 사용하는 것이다. OS의 일반적인 시스템 콜 인터페이스를 사용하기 때문에 overhead가 적은데 안정성이 떨어진다.

### 가상화 종류

- Para-virtualization
  - guest OS를 수정해서 사용하는 것
- Full-virtualization
  - guest OS를 수정하지 않고 사용하는 것
  - exception이 발생하면 hypervisor가 처리한다.
- Hybrid-virtualization
  - guest OS의 일부를 수정해서 사용하는 것

### VMM(Hypervisor) 종류

- Type 1
  - bare-metal
  - host machine에 hypervisor가 설치되어 있고 그 위에 guest machine이 설치된다.
  - ex) Xen, KVM
- Type 2
  - hosted
  - host OS 위에 hypervisor가 설치되고 그 위에 guest machine이 설치된다.
  - ex) VMware, VirtualBox
- Type 3
  - hybrid

## 프로세스 관리

- Job
  - 실행 가능한 프로그램
  - 실행 전에 제출되는 개체
- Process
  - 실행 중인 프로그램
  - 실행을 위해 kernel에 등록된 개체
  - program code, global data, temporary data, heap등을 가지고 있다.

시스템은 resource, process, kernel로 구성되어 있다.

### Resource 개념

커널의 제어 아래 프로스세가 할당받고 해제되는 수동적인 개체를 말한다. HW는 cpu, memory, disk, I/O device 등이 있다. SW는 file, signal등이 있다.

### Process 개념

- PCB
  - 커널에 등록된 프로세스의 정보를 담고 있는 자료구조
  - 커널 공간에 존재
  - 프로세스의 상태, 프로세스 번호, 스케쥴링 정보, 메모리 관리, IO 상태, Context save area 등을 가지고 있다
  - PCB access speed가 시스템 전반 성능에 영향을 미친다.
  - OS 별로 PCB의 구조와 명칭이 다르다.
- Process state
  - Active (메모리에 할당됨)
    - Running (CPU를 사용하고 있다)
    - Ready
    - Blocked, asleep (I/O를 기다리고 있다)
  - Suspended (메모리에 할당되지 않음)
    - Suspended ready (메모리에 할당되지 않았지만 메모리에 올라갈 준비가 되어있다)
    - Suspended blocked
  - Created state
    - system call에 의해 생성된 상태
    - fork() system call
  - Ready state
    - CPU를 할당받기 위해 대기하는 상태
  - Running state
    - CPU를 할당받아서 실행되는 상태
    - Preemtion
      - CPU를 할당받은 프로세스가 CPU를 반납하기 전에 강제로 CPU를 빼앗기는 것
    - Block/sleep
      - I/O를 기다리는 상태
      - 스스로 CPU를 반납한다.
      - Wakeup
        - Interrupt signal에 의해 block/sleep 상태에서 ready 상태로 바뀌는 것
    - Suspended
      - 메모리에 할당되지 않은 상태
      - swap out (suspend)
        - 메모리에 할당되어 있던 프로세스가 메모리에서 제거되는 것
      - swap in (resume)
        - 메모리에 할당되지 않았던 프로세스가 메모리에 할당되는 것
    - Terminated
      - 프로세스가 종료되는 상태
      - exit() system call
      - PCB의 일부 정보는 남아있는다.

### scheduler

- scheduling queue
  - priority queue로 구현
  - ready queue, io queue등 별도로 관리
- 종류
  - long-term scheduler
    - job scheduling
  - medium-term scheduler
    - swap scheduling
  - short-term scheduler
    - CPU scheduling

### Interrupt

- unexpected event
- 종류
  - I/O interrupt
  - Clock interrupt
  - Console interrupt
  - etc
- 핸들링 방법
  - 인터럽트 프로세서로 전달
  - pcb에 context save
  - interrupt handler 실행
    - 근원지, 이유, 처리 방법 등을 확인
  - interrupt service 실행
  - scheduling해서 다음 프로세스 얻기
  - context restore

### Context Switching

- context
  - process와 관련된 정보들의 집합
    - user-level context
      - text, data, stack, heap
    - system-level context
      - pcb
    - register context
- context saving
  - 현재 프로세스의 상태를 저장
- context restore
  - 다음 프로세스의 상태를 복원
- context switching
  - context saving + context restore
