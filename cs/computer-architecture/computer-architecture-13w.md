# 컴퓨터구조개론 13주 차

## Measuring Cache Performance

CPU time은 프로그램이 실행되는 cycles와 memory stall cycles로 구성된다. memory stall cycles는 memory access \* miss rate \* miss penalty로 볼 수 있다.

### Cache Performance Example

- I-cache miss rate: 2%
- D-cache miss rate: 4%
- Miss penalty: 100 cycles
- Base CPI(모두 hit일 때): 2
- load & stores : 36%

위와 같이 조건이 주워지면

- Miss cycles per instructions
  - I-cache: 2% \* 100 = 2 cycles
  - D-cache: 0.36 \* 4% \* 100 = 1.44 cycles

따라서 Acutual CPI는 2 + 2 + 1.44 = 5.44 cycles이다.

### Average Memory Access Time

줄여서 AMAT은 Hit time + Miss rate \* Miss penalty로 구할 수 있다. 예를들어서 2ns clock, hit time = 1cycle, miss penalty = 20 cycles, I-cache miss rate = 6%이면 AMAT = 2ns \* 100% + 40ns \*6% = 4.4ns이다.

## Improving cache performance

이전에는 slot이 하나만 있는 direct-map을 봤는데 이제는 slot이 여러개인 cache를 배운다.

### Associative cache

![예제](./imgs/2023-05-24-18-00-58.png)

> ref. 컴퓨터구조개론 조형민 교수님 강의자료

- Set associative cache
  - e.g. 2-way set associative cache
  - 2-way set associative cache는 2개의 slot이 있고 각 slot은 2개의 block을 가진다.
  - set마다 comparator가 있어야 한다.
  - 반드시 power-of-2가 아니여도 된다.
  - block number는 set index에 의해 결정된다.
    - block number % set number
- Fully associative cache
  - 어디든 들어갈 수 있다.
  - 동시에 모든 장소를 검색하기 위해 개체마다 comparator가 있어야 한다.
  - cache index가 필요 없다.

### Replacement policy for set associative cache

여기서도 LRU replacement policy가 나왔지만 set의 수가 많아지면 LRU를 구현하기 어렵다. 따라서 Pseudo-LRU를 사용한다.

Pseudo-LRU는 2개의 개체마다 1개의 LRU bit가 존재하는데 이때 개체는 block이 될 수 있고 lru bit일 수 있다. 이는 tree-like structure이다.

lru bit은 replace 할 buffer를 가르키는데 가지고 있는 개체들 중 접근이 가장 오래된 개체를 가르킨다.
