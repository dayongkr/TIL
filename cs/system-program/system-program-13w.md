# 시스템프로그램 13주 차

## Locality

Locality는 프로그램이 메모리를 참조할 때 특정 부분을 자주 참조하는 것을 말한다. 이는 프로그램의 성능을 향상시키는데 도움을 준다. 이는 크게 2가지로 나뉜다.

- Temporal locality
  - 최근에 참조한 주소를 다시 참조할 확률이 높다.
  - 반복문에서 사용하는 변수
  - 더 빠른 storage에 cache를 사용해서 temporal locality를 높일 수 있다.
- Spatial locality
  - 최근에 참조한 주소와 인접한 주소를 다시 참조할 확률이 높다.
  - 배열
  - cache line의 크기를 키워서 spatial locality를 높일 수 있다.

### Locality example

- Data reference
  - 배열의 요소를 순차적으로 읽는다.
    - Spatial locality
    - stride-k reference pattern 이라고 하고 모든 요소를 순차적으로 읽는 것은 stride-1 reference pattern이라고 한다.
  - 반복문에서 특정 변수를 사용한다.
    - Temporal locality
- Instruction reference
  - 반복문에서 사용하는 instruction
    - Temporal locality
  - 순차적으로 실행되는 instruction
    - Spatial locality

이를 활용해서 성능향상을 시킬 수 있는데 대표적인 예제로 보통 배열은 row major order로 저장되어 있기 때문에 row major order로 순차적으로 읽는 것이 spatial locality를 활용한 것이다.

## Memory Hierarchy

위와 같은 locality 성질 덕분에 memory hierarchy를 사용할 수 있다. memory hierarchy는 memory를 여러 계층으로 나누어서 사용하는 것을 말한다. 이는 memory의 access time과 cost를 줄여서 성능을 향상시키는데 도움을 준다. 이를 통해 컴퓨터는 마치 엄청 큰 저장 장치를 매우 빠르게 사용하는 것처럼 보인다.

보통 lower한 저장장치는 upper한 memory보다 느리고 크다. 그래서 보통 lower한 저장 장치는 한 번에 많은 데이터를 저장한다. 어쨋든 자주 사용하는 데이터를 upper한 memory에 저장하는 과정을 caching이라고 한다.

### Cache

이러한 Cache의 컨셉은 cpu에서 데이터가 필요하면 계층을 따라 내려가면서 데이터를 찾는 것이다. 이 때 데이터가 존재하면 hit, 존재하지 않으면 miss라고 한다.

### Types of cache misses

- Compulsory miss
  - 처음에 데이터가 존재하지 않아서 발생하는 miss
- Conflict miss
  - cache의 크기는 충분하나 저장할 수 있는 공간이 한정되어 있어서 발생하는 miss
- Capacity miss
  - cache의 크기가 작아서 발생하는 miss

### Generic cache organization

2^m 주소를 가진 메모리가 있다고 가정하면 Cache는 S개의 set 안에 E개의 line 안에 B개의 block으로 구성된다. 이 때 S는 2^s, E는 2^e, B는 2^b이다. 즉 cache size는 S \* E \* B가 된다.

그렇게 나눠진 cache를 찾아가기 위해 tag, index, offset을 사용한다. tag는 line의 주소를 나타내고, index는 set의 주소를 나타내고, offset은 block의 주소를 나타낸다. 따라서 index는 s bit, offset은 b bit이고 나머지 bit는 tag이다.

### Direct mapped cache

Direct mapped cache는 line의 개수가 1개인 cache이다. tag와 set index를 사용해서 cache를 찾는다

### Set associative cache

Set associative cache는 line의 개수가 여러 개인 cache이다. 이때 line의 개수가 C/B개라면 fully associative cache라고 한다. fully associative cache는 index bits가 필요없다. set associative cache는 line이 여러개라서 replacement policy가 필요하다.

### Issues with writes

write hit이 발생하면 cache에만 수정하는 write back과 cache와 memory에 모두 수정하는 write through가 있다. 그리고 write miss 같은 경우에는 cache에도 쓰고 memory에도 쓰는 write allocate와 memory에만 쓰는 no write allocate가 있다.

write back + write allocate를 사용하면 cache와 memory에 쓰는 횟수를 줄일 수 있지만 cache와 memory의 데이터가 다르기 때문에 consistency 문제가 발생할 수 있다.

### Cache performance metrics

- Miss rate
  - miss가 발생한 비율
- Hit rate
  - hit이 발생한 비율
  - 1 - miss rate
- Miss penalty
  - miss가 발생했을 때 추가적으로 걸리는 시간
- Hit time
  - hit이 발생했을 때 걸리는 시간
- Average memory access time
  - (hit time + miss rate \* miss penalty)
