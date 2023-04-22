# 데이터베이스개론 8주 차

앞으로 데이터가 어떻게 저장되는지 알아본다.

## Storing Data: Disks and Files - Heap File Structure

### Overview

Disk에 정보를 저장하게된다. 따라서 이를 통해 읽고 쓸 경우 성능에 영향을 줄 수 있기 때문에 조심해서 게획해야한다.

SSD와 HDD에 대한 차이도 설명하셨는데 전자와 기계식 Asymmetric, Symmetric등에 대한 내용이였다.

#### Typical Server and Storage Performance Metrics

보통의 max throughput은 DRAM이 100GB/s, SSD가 2GB/s, HDD가 130MB/s이다. Storage Capacity에 해당하는 금액은 보통 1000\$당 DRAM이 0.25TB, NVME SSD가 9TB, HDD가 50TB이다.

#### Storage Performance Metrics

IOPS는 IO Per Second의 약자로 1초에 몇 번의 IO를 할 수 있는지를 나타내는 지표이다.

#### Bandwidth Crisis in AI/ML era

데이터를 읽는 것을 반복하는 연산을 수행하기 때문에 DRAM이나 SSD의 대역폭이 중요하다. 그래서 비교적 가격이 싼 Optane과 같은 PM 장치를 사용하거나 데이터를 압축하고 알고리즘을 더 최적화하는 방법등을 사용해서 이를 해결한다.

### Memory Hierarchy

- CPU Registers
- CPU Cache
- Main Memory (Primary Storage)
- Magnetic Disk (Secondary Stroage)
- Tape

위로 올라갈수록 속도가 빨라지고 용량은 작아지고 가격이 비싸지는 특징이 있다. 데이터베이스는 disk에 저장되고 RAM에는 현재 사용되는 데이터가 저장된다.

#### Disks

Disk는 sequential한 tape와 달리 random access가 가능하다. data가 disk block 또는 pages unit에 저장되고 되찾는 시간은 어디에 위치에 있는지에 따라 다르다. 따라서 최적화하기 위해서는 data의 placement가 중요하다.

#### Anatomy of a Disk

disk arm에 disk head가 붙어 있고 disk platter의 track 위에 있게 된다. 이러한 세트가 층을 이루고 이러한 층이 여러 개가 쌓여서 disk가 된다. 한 세트당 한 번의 IO가 가능하다. 따라서 low IOPS를 가지고 있다. 데이터는 track 안에 sector에 저장된다. 저장을 요청하자마자 disk에 permanent하게 저장되는 것이 아니라 dram에 저장되고 추후에 disk에 저장된다.

#### Accessing a Disk Page

- Seek Time: disk arm이 원하는 track으로 이동하는 시간
  - 1~20ms
- Rotational delay: disk가 원하는 sector(block)로 돌아가는 시간
  - 0~10ms
- Transfer Time: disk head가 data를 읽어오는 시간
  - 1ms per 4KB page

위 3가지 시간이 합쳐져서 disk access time이 된다.

#### Arranging Pages on Disk

Blocks는 disk에 sequentially하게 저장되어야 한다. 즉 next block은 이전 block의 주소와 연속적이어야 한다. 여기서 next block이란 따라오는 같은 트랙 혹은 실린더에 있는 block 이거나 인접한 실린더에 있는 blocks를 의미한다.

file system은 continuous하지 않게 block address를 저장할 수 있다. 이러한 경우를 fragmentation이라고 한다. 따라서 이를 해결하기 위해서는 연속적으로 저장시키는 defragmentation이 필요하다.

#### Some Techniques to Hide IO Bottlenecks

- Prefetching: 순차적인 스캔하는 동안 several pages를 미리 읽어서 cache에 저장한다.
- Caching: disk에 있는 data를 cache에 저장한다.
- IO overlapping: IO를 수행하는 동안 CPU가 다른 작업을 수행한다.
- Multi-threading: 여러 개의 thread를 사용해서 IO를 수행한다.
- Avoiding IO: disk에 접근하지 않고 memory에서 처리한다.

#### Why Not Store Everything in Memory?

- Memory is expensive
- Main memory is volatile
  - data should be saved between runs
  - 복구를 위해 log를 작성하기 위해서는 disk write는 inevitable하다.
- Big memory는 Power consumption이 많이 든다.

하지만 간혹 특정 systems(MM-DBMS)는 전체 데이터베이스를 메모리에 저장한다.

#### Implications for DBMS Design

- Disk Space Management (Spatial control)
  - WHERE
  - Secondary storage 위에 중 어디에 저장을 할지
- Buffer Management (Temporal control)
  - WHEN
  - 언제 데이터를 물리적으로 읽고 쓸지
- Query Optimization and Execution (Access pattern control)
  - HOW
  - disk에 있는 data를 어떻게 읽어올지

### RAID

SLED(Single Large Expensive Disk)는 하나의 disk에 모든 데이터를 저장하는 것이다. 이러한 경우에는 disk failure가 발생하면 모든 데이터가 손실된다. 따라서 성능과 신뢰도 향상을 위해 여러 개의 disk를 사용하는 RAID(Redundant Array of Independent Disks)를 사용한다.

- Main techniques
  - Striping
    - 데이터를 여러 개의 disk에 분산시킨다.
    - 이를 통해 더 크고 높은 bandwidth, IOPS를 얻을 수 있다.
    - RAID 0
  - Mirroring
    - 데이터를 여러 개의 disk에 복사한다.
    - 더 높은 신뢰성을 얻을 수 있다.
    - RAID 1
