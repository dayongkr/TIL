# 운영체제 9주 차

## Memory Management

저장공간은 아래 4가지로 나눌 수 있다.

- register
  - CPU 내부에 존재한다.
  - 가장 빠르다.
  - word 단위로 접근한다.
    - 최근에는 64-bit word를 사용한다.
- cache
  - cpu 내부에 존재한다.
  - L1, L2, L3 cache가 존재한다.
- main memory
  - RAM이라고도 한다.
  - auxiliary storage에 block 단위로 저장된다.
    - 4KB가 일반적이다.
- auxiliary storage
  - SSD, HDD 등이 있다.
  - byte 단위로 접근한다.

regs에 접근하는 시간은 0~1이지만 RAM에는 50~200이 걸려서 중간에 cache를 두었다. cache는 보통 4~50이 걸린다.

추가로 주소를 binding하는 방법은 아래와 같다.

- Compile-time binding
  - absolute code
    - 주소를 컴파일 시점에 binding한다.
    - 주소가 바뀌면 다시 컴파일해야 한다.
- Load-time binding
  - relocatable code
    - 주소를 로드 시점에 binding한다.
    - 주소가 바뀌면 다시 로드해야 한다.
  - 할당된 주소 기준으로 코드를 수정한다.
- Run-time binding
  - 주소를 실행 시점에 binding한다.
  - MMU(memory management unit)를 사용하여 주소를 매핑한다.
  - limit register로 계산된 주소가 범위를 벗어나는지 확인한다.
- Dynamic linking
  - system libraries와 같이 공통으로 사용되는 library를 binding한다.
  - disk와 main memory의 공간을 아낄 수 있다.
  - 보통 stub을 두고 call이 되면 stub이 library를 찾아서 binding한다.
    - 다음부터는 바로 실행한다.

Overlay structure는 메모리가 부족할 때 사용하는데 어떠한 공간을 공유해서 사용하는데 이 때 swap device를 사용하여 swapping을 한다. 이 때 time quantum이 swap time보다 커야 CPU utilization이 높아지고 I/O를 기다리고 있는 process는 swap하면 안된다. 참고로 swap device는 빠른 access time을 위해 contiguous allocation을 사용한다.

## Contiguous Memory Allocation

Memory allocation에는 아래 3가지 방법이 있다.

- Contiguous memory allocation
  - 프로세스를 연속적으로 할당한다.
- Discontiguous memory allocation
  - 프로세스를 불연속적으로 할당한다.
- Virtual memory
  - 일부만 메모리에 올려둔다.

Uniprogramming systems에서의 메모리 할당을 먼저 살펴보면 contiguous memory allocation은 아래 2가지 문제가 있다.

- Program size > memory size
  - overlay structure을 사용한다.
- Kernel protection
  - boundary register을 사용해서 접근을 제한한다.

이 중 contiguous memory allocation은 메모리의 연결된 한 부분을 차지하는 것인데 이를 위해 partition을 나눈다. partition은 아래 2가지 방법으로 나눌 수 있다.

- Fixed partition multiprogramming (FPM)
  - partition의 크기가 고정되어 있다.
  - Internal fragmentation, External fragmentation이 발생한다.
    - Internal fragmentation
      - partition의 크기가 process의 크기보다 크다.
      - partition의 남은 공간이 낭비된다.
    - External fragmentation
      - 남은 partition의 크기가 process의 크기보다 작아서 사용할 수 없다.
  - Boudnary address를 사용해서 파티션의 경계를 나타낸다.
  - FPM도 relocation 문제가 발생하기 때문에 위에서 살펴본 방법을 사용한다.
- Variable partition multiprogramming (VPM)
  - partition의 크기가 가변적이다.
  - External fragmentation이 발생한다.
  - 배치 기법은 아래 4가지가 있다.
    - First-fit
      - 가장 먼저 맞는 partition에 할당한다.
      - overhead가 적다.
    - Best-fit
      - 가장 작은 partition에 할당한다.
      - small size partition이 많이 생산되어서 external fragmentation이 많이 발생한다.
    - Worst-fit
      - 가장 큰 partition에 할당한다.
      - small size partition은 막을 수 있지만 internal fragmentation이 많이 발생한다.
    - Next-fit
      - First-fit과 비슷하지만 이전에 할당한 곳부터 찾는다.
  - Coalescing holses: 인접한 빈 공간들을 합친다.
  - Compaction: 프로세스를 한쪽으로 몰아서 빈 공간을 한쪽으로 몰아낸다.
    - External fragmentation을 해결할 수 있다.
    - overhead가 크다.
