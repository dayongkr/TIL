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

### Cache Example

8bit address, 1 word/block, 8 blocks를 가진 cache를 가정하자. 이때 block size는 1 word이므로 offset은 2bits, cache에 있는 block의 갯수는 8개이므로 index는 3bits, 나머지는 tag가 된다. 예를들어 0x58은 01011000이므로 tag는 010, index는 110, offset은 00이 된다.

> direct map의 한계로 여러 block이 같은 index를 가질 수 있다. 이에 따른 miss가 발생하는 경우가 생길 수 있다.

추가로 한 예시를 더 보자면 4KB cache, 1 word/block일 경우 4KB / 4B = 2^10 이므로 10 bits가 index가 되고 offset은 2bits, 나머지는 tag가 된다. 만약에 4 words/block 일 경우 index에 여러 block이 들어갈 수 있으므로 이들 중 하나를 선택해야 한다. 이때 사용하는 것이 block offset이다. 이렇게 하면 MUX도 필요하고 overhead가 늘어난다.

다만 근처에 있는 버퍼를 가져오는 것이기 때문에 Spatial Locality에 따라 성능이 좋아진다.

> Byte offset은 lh, lb일 떄 사용한다.

### Block Size Tradeoffs

Block의 크기가 커지면 cache line의 수가 줄어들고 이에 따라 cache conflict가 많이 발생하여 miss가 많이 발생한다. 크기가 작아지면 spatial locality가 떨어져 miss가 많이 발생한다. 따라서 적절한 크기를 선택해야 한다.

### Handling Write(Store) Operations

- Hit
  - cache는 항상 최신의 값을 가지고 있어야 한다.
  - memory는 최신 값을 가지고 있지 않아도 된다.
- Miss
  - memory에 최신 값을 저장한다. (No Write Allocate)
  - cache에도 최신 값을 저장한다. (Write Allocate)

#### Write-through

메모리도 최신 값을 가지고 있도록 하는 방법으로 write가 발생하면 cache와 memory에 모두 write를 한다. 이렇게 하면 memory 접근이 많아져 성능이 떨어진다. 이를 해결하기 위해 write buffer를 사용한다. 이는 mem stage에 추가로 unit을 만들어 구현을 하는데 일단 쓰여질 값을 저장해두고 다른 일을 하다가 memory에 write를 해야 할 때 한번에 write를 하는 방법이다.

> 보통 buffer가 꽉 차면 write를 한다.

#### Write-back

cache에만 write를 하고 memory에는 write를 하지 않는다. 이때 cache에는 dirty bit를 사용하여 memory이 업데이트 되었는지 확인한다. 만약에 block이 교체될 때 dirty bit가 1이면 memory에 write를 한다. 여기서도 memory에 write를 할 때 write buffer를 사용한다.

### Cache Write Summary

- Write-through, write allocate
  - hit: write to cache and memory
  - miss: fetch block from memory, write to cache and memory
- Write-through, no write allocate
  - hit: write to cache and memory
  - miss: write to memory
- Write-back, write allocate
  - hit: write to cache (set dirty bit)
  - miss: fetch block from memory, write to cache (set dirty bit)
  - evict: write to memory if dirty
- Write-back, no write allocate
  - hit: write to cache (set dirty bit)
  - miss: write to memory
  - evict: write to memory if dirty
