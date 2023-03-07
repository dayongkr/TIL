# 컴퓨터구조대론 2주 차

컴퓨터 시스템의 간단한 개념을 다루게 된다.

## Semiconductor

### Old Computer Systems

많은 트랜지스터들을 하나의 칩에 넣기 어려워서 기능마다 칩들을 분리했다. 많은 칩이 있다 보니 칩 간의 의존성 때문에 불안한 시스템이다. CPU에는 하나의 코어가 존재했다.

### SOC

파이프라인으로는 한계가 있다 보니 요즘에는 멀티코어 구조를 갖게 되었다.

### Integrated Circuits 생산

실리콘을 자르고 작은 패턴을 만들고 여러 테스트를 거쳐 포장하여 칩들을 생산하게 된다.

> Yield: 작동하는 Die들의 Percentage

Die의 크기가 커질수록 Die의 가격이 비싸지게 된다.

- 낭비되는 Wafer의 부분이 많아지기 때문에
- 작동 안하는 부분이 포함될 가능성이 더 높기 때문에

#### Chiplet

하나의 칩에 여러 대를 내장시켜서 위의 경쟁적 문제를 해결하는 추세이다.

Old Computer System으로 회귀한 꼴인 것처럼 보이지만 서로를 연결하는 와이어가 효율적이고 작아져서 대부분의 문제를 해결했다.

같은 일은 하나의 다이에서 최대한 연산한다고 해서 Die끼리의 통신을 최소화해서 지연 문제를 해결했다.

## Performance

- Response time
  - 응답속도
- Throughput
  - 특정시간에 가능한 처리량

### What Affects Performance of a Computer?

- 애플리케이션
  - 연산의 양
- 프로그래밍 언어, 컴파일러, ISA
  - 연산을 실행하는 명령어의 양
- Processor and memory system
  - 각 명령어를 실행되는 속도
- I/O
  - I/O 동작을 수행하는데 걸리는 속도
