# 컴퓨터구조개론 12주 차

이번주 차 부터 cache를 배우게 된다.

## Memory

### Memory Technology

- SRAM
  - Static RAM
  - 0.5ns ~ 2.5ns (16KB ~ 64KB)
  - in CPU memory
- DRAM
  - Dynamic RAM
  - 50ns ~ 70ns (GBs)
  - 1 ns는 1GHz로 표현할 수 있다.
  - 따라서 50ns 기준 4GHZ의 CPU는 200 Cycle동안 기다려야 한다.
- Flash
  - 5 - 50us (TBs)
- Magnetic Disk
  - 5 - 20ms (10+ TBs)

### Memory Hierarchy

Processor - Cache - Main Memory - Disk로 대충 나누어지는데 이때 block 단위로 copy를 한다. 데이터베이스개론 때 배운 hit ratio 개념도 나왔다.

### Principle of Locality

- Temporal Locality
  - 최근에 접근한 데이터는 다시 접근할 확률이 높다.
  - related to time
  - instruction loop, index variable
- Spatial Locality
  - 최근에 접근한 데이터와 인접한 데이터에 접근할 확률이 높다.
  - related to space
  - e.g. array, sequential instruction access

### Typical Cache Hierarchy

Core pipeline - L1 I-cache, L1 D-cache - L2 cache - L3 cache - Main Memory 인데 Die 사진을 보면 Core마다 L1 cache, L2 cache가 있고 Core 밖에 L3 cache가 있다. 즉 L3 cache는 shared cache이다.

### Cache Memory

Cache Memory에서 data가 있는지 어떻게 알까?

#### Direct Mapped Cache

주소에 의해 위치가 정해지는데 이때 주소의 일부를 cache의 index로 사용한다. Block address % # Blocks in cache = cache index 이다. 즉 Block address의 lower order bits만 사용하여 index를 만든다. 예를 들어 00001이 block의 주소이고 cache의 크기가 8이면 00001 % 8 = 001이 cache index가 된다. 이때 index는 겹치는 것이 있을텐데 어떻게 구분할까?

#### Tags and Valid Bits

이때 사용하는 것이 tag로 이는 block의 high order bits를 저장한다. 또한 처음에는 cache에 garbage value가 있을 수 있으므로 valid bit를 사용하여 이를 구분한다. 이때 valid bit가 0이면 cache에 garbage value가 있고 1이면 cache에 valid한 값이 있다는 것을 의미한다.

종합한 cache의 format은 다음과 같다.

| Tag  | Index                                                    | Offset                                                            |
| ---- | -------------------------------------------------------- | ----------------------------------------------------------------- |
| rest | block size으로 크기 결정 (e.g. 8 words => 2^5 => 5 bits) | cache에 있는 block의 갯수로 결정 (e.g. 8 blocks => 2^3 => 3 bits) |
