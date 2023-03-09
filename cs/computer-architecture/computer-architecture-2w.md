# 컴퓨터구조개론 2주 차

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

### CPU

> CPU TIME = CPU Clock Cycles x Clock Cycle Time = CPU Clock Cycles / Clock Rate

- Clock period: 1 -> 0 으로 변하는 주기
- Clock frequency (rate): 1초에 몇 번 주기가 반복되는지
  - e.g. 4.0 GHz

Clock cycle의 수를 줄이면 성능 향상을 기대할 수 있다.

- 1 cycle
  - Clock period가 좀 더 길어서 1 cycle에 연산할 수 있는 경우
  - 저장할 필요가 없으므로 Resource가 비교적 덜 필요하다
- 2 cycles
  - pipline을 사용할 수 있다.

#### Instruction Count and CPI (Without Pipelining)

> Clock Cycles = IC x CPI
> CPU Time = IC x CPI x Clock cycle Time = (IC * CPI) Clock Rate

- Instruction Count (IC)
  - 프로그램에 의해 실행된 명령어의 개수
- Cycles Per instruction (CPI)
  - Processor의 설계로 결정
  - 명령어의 종류에 따라 달라질 수 있음, 따라서 Average CPI를 사용한다.

### SPEC CPU Benchmark

다양한 방법으로 측정하지만 보통 Time, Throughput을 위주로 측정한다.

#### Aggregating Performance Ratios

Geometric mean은 각 프로그램에서 측정해서 나온 SPECratio i 개를 모두 곱한 후 루트 i를 씌운다. 이를 사용하면 반대 상황에서도 ratio가 유지돼서 사용하게 된다.

> SPECratio: reference machine과의 elapsed time을 비교한 비율

### The Power Wall

Power ~= Capacitive load * Voltage^2 * Frequency

- Power
  - 전력소비가 증가할수록 열이 발생하고 실패로 이어진다.
- Capacitive load
  - transistor를 작게 만들거나 적게 만들면 되지만 작게 만드는 데는 한계가 있고 적게 만들면 성능 저하로 이어진다.
- Voltage
  - 1V보다 낮추는 데는 한계가 있다.
- Frequency
  - 당연히 frequency를 낮추면 성능 저하로 이어진다.

이러한 한계로 점점 하드웨어 성능 향상이 어려워지고 있고 따라서 소프트웨어적으로 성능 향상이 중요해지고 있다.
