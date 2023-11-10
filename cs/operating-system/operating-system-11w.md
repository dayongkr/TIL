# 운영체제 11주차

## Issues in Demand Paging

### Page Sharing

page를 process 간 공유를 하면 memory를 절약할 수 있다. 따라서 Pure code인 Procedure page와 Read-only data page등은 공유해서 사용하는데 procedure page sharing 상황에서 jump instruction등을 할 때 서로 다른 pmt entry index를 가지면 문제가 발생한다. 이를 해결하기 위해 같은 pmt entry index를 가지도록 한다.

### Page Fault Handling

instruction 수행과정에 page fault가 발생하면 instruction을 처음부터 다시 수행해야 한다. 때문에 중간에 바뀐 register등을 다시 원래대로 복구해야 한다. 이러한 page fault가 발생하면 system 성능에 악영향을 미치기 때문에 page fault가 발생하는 비율을 줄여야 사용하는데 의미가 있다!

### Copy-on-Write

fork()를 할 때 parent process의 page를 복사하지 않고 같이 사용하되 COW 마크를 통해 write가 발생하면 복사하는 식으로 구현하면 memory를 절약할 수 있다.

## Segmentation & Hybrid Paging/Segmentation

### Segmentation

서로 다른 크기의 size를 가진 segment로 logical하게 분리하여 sharing과 protection이 쉬운 대신 address mapping overhead가 좀 크다.

PMT와 다르게 segment length와 protection bits(Read/Write/Execute/Accesible)를 가진다. 따라서 mapping alogrithm에도 overflow exception과 protection exception을 추가해야 한다.

### Hybrid Paging/Segmentation

먼저 segment를 나누고 segment마다 page로 나눈다. 따라서 segment별로 PMT가 존재한다. 이를 통해 각 장점을 가져올 수 있지만 SMT, PMT 모두를 가지고 있어야 하므로 overhead가 크다. 참고로 주소 체계는 (s, p ,d) 이다.

## Virtual Memory Management

관리하기 위한 전략 6가지가 있다.

- Allocation Strategy: How / How much
- Fetch Strategy: When
- Placement Strategy: Where
- Replacement Strategy: Who
- Cleaning Strategy: When
- Load Control Strategy: How many

주로 Allocation Strategy와 Replacement Strategy를 다룬다. 추가로 어휘를 다루면 Page reference string은 process가 memory에 접근하는 순서를 나타내는 string이다.

### Hardware / Software Components

- Hardware
  - Address Translation device: TLB, MMU
  - Bit vectors
    - Reference bit: page가 사용되었는지
      - 주기적으로 0으로 초기화 즉 최신의 reference를 반영한다.
    - Update bit: page가 변경되었는지
      - write back policy를 위해 사용된다.
- Software
  - Allocation Strategy
    - Fixed allocation: process마다 고정된 갯수의 frame을 할당한다.
    - Variable allocation: process마다 다른 갯수의 frame을 할당한다.
    - 너무 많으면 thrashing이 발생하고 너무 적으면 memory utilization이 낮아진다.
  - Fetch Strategy
    - Demand fetch: page fault가 발생할 때 page를 가져온다.
    - Anticipatory fetch: page fault가 발생하기 전에 미리 가져온다.
      - Prediction overhead가 발생한다.
  - Placement Strategt: page system에서는 필요없다.
  - Replacement Strategy
    - Fixed allocation based
      - MIN(OPT, B) algorithm: 가장 먼 미래에 사용될 page를 victim으로 선택한다.
        - OPT: optimal replacement algorithm
        - B: Belady's anomaly
        - Page reference string이 주어진다는 가정하에 사용할 수 있기 때문에 실제로는 사용할 수 없다.
      - Random algorithm: random하게 victim을 선택한다.
    - Variable allocation based
      - 크기를 바꿀 수 있기 때문에 replace가 필요 없을 수 있다.
      - VMIN, WS, PFF
  - Cleaning Strategy
    - Demand cleaning: page가 victim이 되면 disk에 write한다.
    - Precleaning: page가 victim이 되기 전에 disk에 write한다.
      - Prediction overhead가 발생한다.
  - Load Control Strategy
    - allocation strategy와 같이 사용한다.

### Locality

- Temporal locality: 최근에 사용된 page는 다시 사용될 확률이 높다.
- Spatial locality: 최근에 사용된 page와 인접한 page는 사용될 확률이 높다.
