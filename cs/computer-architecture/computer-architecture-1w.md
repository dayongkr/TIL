# 컴퓨터구조개론 1주 차

## 개요

모든 수업은 녹화해서 i-Campus에 업로드된다.

### 수업 목표

컴퓨터 성능을 결정하는 것이 무엇이고 어떻게 소프트웨어를 작동시키는지 하드웨어 위주로 배우게 된다.

### 수업 과정

cpu 먼저 배운 후 중간 이후에는 파이프라인과 메모리 부분으로 넘어가게 되는데 cache 메모리 등을 배우게 된다.

## RISC-V CPU

현대 x86 기반 컴퓨터들은 복잡한 명령어 세트로 매우 복잡하다는 문제를 해결한 RISC CPU 중의 하나이다.

비슷한 목적으로 만들어진 CPU인 ARM은 비교적 복잡하고 유료라는 단점이 있다.

### 특징

- 불필요한 명령어 세트를 제거해 간단하다
- 많은 오프소스 구현체가 존재한다.
- 시뮬레이터가 존재해서 RISC-V 컴퓨터가 없어도 해당 시스템의 소프트웨어를 테스트할 수 있다.

## 컴퓨터들의 유형

- 개인용
- 서버용
- 슈퍼컴퓨터
  - 성능과 전성비 모두 Oak Ridge National Laboratory에서 만든 Frontier가 1위를 차지했다.
  - 삼성전자에서 만든 건 전성비에서 6위를 차지했는데 Frotier 보다 2배 좋지 못하다.
- 임베디드
  - 이동장치, 가전제품, usim등
  - 크기, 소비전력, 성능 등 상당한 제한들이 있다.
- 클라우드 컴퓨팅
  - 데이터를 저장, 복잡한 연산 요청, 가상머신 다양한 목적으로 수행한다.
  - 결국 효율적으로 강력한 컴퓨터를 사용하기 위해 사용하게 된다.

예전에는 개인용, 서버용이 매우 다른 구조(Architecture)로 되어 있었지만, 요즘은 똑같은 구조로 되어 있다.

## 컴퓨터 시스템 추상 및 계층 구조 (Abstarction)

- 하드웨어
  1. 트랜지스터
  2. 회로
  3. 마이크로아키텍쳐
  4. 프로세서아키텍쳐
- 소프트웨어
  1. 기계어
  2. 프로그래밍 언어
  3. 애플리케이션

컴퓨터 성능은 low-level의 하드웨어 구조에 따라 바뀐다. 다른 구조이더라도 소프트웨어와 하드웨어를 잇는 인터페이스가 같아서 실행 파일을 실행할 수 있다.

명령어 세트가 다르기 때문에 x86, arm 프로세서들은 서로 프로그램이 호환이 안 된다.

### Make the Common Case Fast

Common Case를 빠르게 만드는 것이 rare case를 최적화하는 것보다 더 좋다고 본다.

### Performance via Parallelism - 병렬의 성능

한 번에 하나만 운송할 수 있는 매우 빠른 차와 한 번에 모든 것을 운송하지만 비교적 느린 기차가 있다고 치자.

하나만 운송하는 일을 수행하면 차가 빠르겠지만 여러 개를 운송하는 일은 기차가 빠를 수도 있다.

### Performance via Pipelining

앞으로 파이프라인으로 cpu 성능을 향상하는 것을 배울 예정이니 간단하게 짚고 넘어간다.

두가지 경우로 설명하셨다.

1. 불을 끄러 한 사람이 혼자서 물을 들고 달려가서 끄는 경우
2. 불을 끄러 여러 사람이 물을 서로에게 전달해서 끄는 경우

첫 번째 경우 혼자서 하므로 왕복하는 동안 딜레이가 생기는데 2번째는 전달하고 돌아가서 다시 떠오면 되기 때문에 딜레이가 덜해서 당연히 빠르다.

### Performance via Prediction

물어봐서 일을 수행하게 되면 물어보는 과정이 생기는데 예측해서 일을 수행하면 이 과정이 없어져서 성능상 더 좋지만 만약에 예측이 틀리면 다시 한번 더 수행해야 하므로 성능상 더 안 좋아질 수도 있다.

### Hierarchy of Memories

작은 파일이라면 cpu 내부에 저장할 수 있어서 빠르지만, 큰 파일은 외부에 저장되어 느릴 수 있다.

자주 사용하는 데이터들을 cpu 내부에 저장하고 자주 사용하지 않는 데이터들은 외부에 저장시키면 평균적으로 성능이 향상되게 된다.

### Dependability via Redundancy(중복성, 이중화)

컴퓨터 시스템은 완벽하지 않다. 따라서 매우 극히 드문 일이지만 cpu가 잘못된 결과를 낼 수 있다.

중요한 일을 수행할 거면 여러 개의 copy system을 운용해야 하나의 시스템에서 다른 값을 내더라도 뭐가 맞는 값인지 유추할 수 있고 잘못되었는지 판단할 수 있다.

## 하드웨어 추상화

- ISA Instruction set architecture 명렁어 세트 구조
  - x86, arm, sparc 등
  - 하드웨어를 어떻게 추상화 할지를 정의
  - 하드웨어와 소프트웨어의 인터페이스
- ABI Application binary inteface
  - ISA의 추가 시스템 소프트웨어 인터페이스
  - 이번 수업에서는 다루진 않는다.

## CPU 내부

- Datapath
  - 구성품간의 데이터 이동 통로
- Control
  - 주여진 데이터를 어떻게 처리할지 관리
- Reigisters
  - 데이터 임시 저장소
- Cache memory
  - 실행되고 있는 프로그램의 주된 저장소

Registers -> Control -> Registers -> Cache -> Registers

좋은 개발자가 되려면 어떻게 CPU 구성품간의 작동 과정을 이해하는 게 중요하다.