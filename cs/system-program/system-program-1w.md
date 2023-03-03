# 시스템 프로그램 1주 차

코드들이 시스템에 어떻게 저장, 작동하는지 하드웨어, OS 적으론 어떻게 작동하는지 Tour 느낌으로 진행된다.

## Source File

Text file는 ASCII 코드로 이루어져 있고 이는 binary 형태로 시스템에 저장된다.

- Text file
  - ASCII 코드로 이루어짐
- Binary file
  - 이진으로 이루어짐

### Translation

만든 소스 파일을 실행파일로 변환해주는 과정이다.

``` zsh
gcc -o hello hello.c // 리눅스에서 컴파일하는 명령어
```

- Pre-porcessor
  - directives(#include와 같은 부분)을 처리해서 순수 C언어 프로그램으로 바꿔줌
  - output -> hello.i(Text file)
- Compiler
  - Assembly code로 변환
  - output -> hello.s(Text file)
- Assembler
  - Binary file로 변환
  - output -> hello.o
- Linker
  - 최종 실행파일
  - output -> hello

### Running (HW)

- Bus and word
  - 8bytes(64bits)
- Controller vs Adapter
  - Controller: 시스템의 메인보드에 내장 되어 있는 칩셋
  - Adapter: 메인보드 슬롯에 장착하는 형태

## Caches

CPU는 1 clock 단위로 돌아가는데 Mem에 다녀오면 약 200 clock 단위이므로 상당한 성능상 손해를 보게 된다.

이를 해결하기 위해 나온 게 Cache Memory가 되겠다. CPU chip 안에 있는 Memory로 상당히 빠른 Memory이다.

많이들 사용하는 인텔 i7 CPU는 3단계(L1,L2,L3)로 Cache memory를 구성하는데 속도 차이가 있다.

- L1
  - Core 안에 Register와 바로 연결됨
- L2
  - Core 안에 L1 Cache와 연결된다.
- L3(unifed)
  - 모든 Core에 의해 공유된다.

### Storage 계층

- Register
- L1 Cache
- L2 cache
- L3 Cache
- Main mem
- Local secondary storage (HDD,SSD)
- Remote secondary storage (Cloud)

위로 올라갈수록 속도는 빨라지고 가격은 비싸지고 용량은 줄어든다.

## OS 운영체제

하드웨어와 Application 사이에서 interface 역할을 하고 주로 Process, Virtual memory, Files를 다룬다.

- 기능
  - User interface
    - I/O
  - Resource management
    - HW(Processor, Mem, I/O Device) / SW(Files, Msg)의 자원들을 관리
  - Process management
    - Process: 실행 중인 Program(App)
  - Networking / Security

### Process

Cpu는 한 개이기 때문에 Context switching을 통해 여러 Process를 번갈아 처리할 수 있다.

Context switching은 데이터를 임시 저장을 함으로써 다시 차례가 오면 다시 연산할 수 있게 도와주는 과정이다.

### Virtual memory

Physic memory보다 더 필요하더라도 Program이 돌아갈 수 있도록 무제한 용량이 있는 것과 같은 환상을 주는 Virtual memory를 사용하게 된다. 

각 Process가 혼자만 Memory를 사용하고 있다고 환상을 갖게 해주기도 한다.

### File

사용자는 사용하고자 하는 데이터들을 그룹화해서 이 이름으로 저장하라는 식의 동작이 이루어지게 도와주는 Abstraction이다.

## Network

다른 Host와 연결되어 통신하는 것이다.

## Concurrency and Parallelism

- Concurrency
  - 여러 개의 Processes를 하나의 CPU 및 Core를 사용하여 동시에 실행되는 것처럼 보이게 한다.
  - 번갈아가면서 실행되도록 한다.
- Parallelism
  - HW적으로 여러 CPU 및 Core를 사용하여 여러 개의 Processes를 동시에 실행되게 해준다.

### Hyperthreading

Regs를 여러 개로 둠으로써 외부 저장소로 저장할 필요가 없어지고 이에 Context switching이 매우 빠르게 작동되어서 마치 동시에 실행되는 것처럼 작동하는 것이다.

### SIMD parallelism

Single Instruction Multiple Data architecture이다.

Regs의 크기를 매우 크게 해서 데이터를 여러 개를 넣을 수 있게 하고 이를 통해 한 명령에 여러 데이터를 처리할 수 있게 하는 개념이다.

벡터, 신호, 그래픽 연산을 할 때 자주 사용된다.
