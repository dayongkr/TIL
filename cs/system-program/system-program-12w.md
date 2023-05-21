# 시스템 프로그램 12주 차

## Program Profiling

저번주 차에 이어 Program Profiling에 대해 알아보았다.

### Profilig Example

bigram 의 빈도수를 세는 프로그램을 Profiling 한다고 했다. 해당 Program은 아래와 같은 작동을 수행한다.

- 단어를 lower case로 바꾼다.
- Hashing하여 s buckets에 저장한다.
- hash bucket을 순회하면서 bigram을 찾는다.
- 모든 요소들을 frequency를 기준으로 정렬한다.

따라서 해당 프로그램은 Sort, List, Lower, Strlen, Hash, Rest으로 나눌 수 있다. 그렇게 나눈 항목들을 각각의 시간을 측정하고 가장 오래 걸리는 항목을 찾아서 최적화를 진행한다.

1. Sort가 가장 오래 걸려서 Quick sort로 바꾼다.
2. buckets의 갯수를 늘려 특정 bucket에 많은 요소가 들어가지 않도록 한다.
3. Hash Function을 바꾼다.
4. Code motion을 통해 불필요한 연산을 줄인다.

이렇게 해서 3.5분이 걸리던 프로그램을 1초 이내로 줄일 수 있었다.

### Amdahl's Law

프로그램을 최적화할 때 어떤 부분을 최적화할지 결정하는 것이 중요하다. Amdahl's Law는 이를 도와주는 법칙이다.

- T: 최적화 전 프로그램의 시간
- p: 최적화한 프로그램의 비율
- k: 몇 배 빨라졌는지
- T' = T(1-p) + p \* T/k

결국 특정한 부분을 상당히 최적화해도 전체 프로그램의 속도는 크게 빨라지지 않는다는 것이다. 따라서 최적화할 부분을 잘 골라야 한다.

## The Memory Hierarchy

특정한 set의 instructions 또는 data 요소들을 계속 사용하는 locality가 존재하기 때문에 이를 이용하여 memory의 hierarchy를 구성하여 자주 사용하는 요소들은 low level의 memory에 저장하고 자주 사용하지 않는 요소들은 high level의 memory에 저장하여 전체적인 속도를 높이는 방법이다.

### SRAM and DRAM

- SRAM
  - bit 당 6개의 트랜지스터로 구성되어 있어 비싸고 빠르다.
  - 자가 refresh하기 때문에 직접적인 refresh가 필요하지 않다.
  - 하지만 전력을 많이 소모한다.
- DRAM
  - w개의 DRAM cells로 구성되어 있는 d개의 super cells로 구성되어 있다.
  - supercell은 row, column으로 사각형 배열에 조직되어 있다.
  - MC (Memory Controller)
    - super cell단위로 읽고 쓰기를 수행한다.
    - 이때 row, column을 주소로 사용한다.
    - 먼저 row를 선택하고 column을 선택한다.
  - 보통 여러개의 DRAM의 같은 주소에 데이터를 저장하고 이를 한 번에 읽어오는 방식을 사용한다.

### Non-Volatile Memory

- ROM
  - Read Only Memory
  - PROM
    - Programmable ROM
  - EPROM
    - Erasable PROM(ultraviolet light)
  - EEPROM
    - Electrically EPROM
- flash memories
  - 읽기 쓰기 속도가 비대칭적이다.
  - 지울 수 있는 횟수가 제한적이다.

#### HDD

HDD는 두 surface를 양면으로 가지고 있는 platters와 회전축인 Spindle, 데이터를 읽어오는 head, 이와 연결된 arm 그리고 이를 움직이는 actuator 그리고 다른 장치들과 연결되는 SCSI connector로 구성되어 있다.

surfaces는 원형 ring 형태의 track으로 구성되어 있고 track은 gap으로 분리된 sectors로 이루워져있다. 같은 track에 있는 sectors를 cylinder라고 한다.

Disk의 용량은 track안의 bits의 수 그리고 track의 수에 비례한다. 원형의 surface 특성상 중심에서 멀리갈수록 지름이 길어지는데도 예전에는 gap의 크기를 키워 sectors의 수를 동일시켰지만 요즘은 recording zone이라고 특정 트랙들을 그룹화하고 각각의 recording zone마다 sectors의 수를 다르게 하여 효율을 높인다.

Disk의 평균 시간은 head가 target sector로 이동하는 seek time, target sector가 head에게 도달하는 rotational latency, head가 sector를 읽어오는 transfer time으로 구성된다. avg rotation time은 1/2 \* 1/rotation speed per second \* 1000ms이다. avg transfer 1 / RPM \* 1 / avg sector per track \* 1000ms이다.

> logical로는 block으로 나누어져 있고 physical로는 sectors로 나누어져 있다.

#### SSD

SSD는 flash memory chips와 FTL(Flash Translation Layer)로 구성되어 있다. FTL은 disk controller와 같은 역할을 한다.

SSD는 Flash memory 안에 여러 block들이 존재하고 각 block은 여러 page로 구성되어 있다. page는 IO 단위이지만 지울때 에는 block 단위로 지워야 한다.

#### Disk formatting

gaps에 sector의 위치를 저장하는 sector를 채우고 defect한 sector를 찾아서 사용하지 않도록하고 특정한 zone을 spare로 두어 잘못된 상황에 사용되게 한다. 이러한 과정 때문에 실제 최대 용량보다는 적은 용량을 사용하게 된다.

### Bus

Bus는 여러 IO Device를 연결하는 통로이다. 1 ~ (M-1)을 먼저 Memory 주소로 잡고 나머지를 Disk의 주소로 잡아 데이터가 올바르게 전송되도록 한다. 이를 Memory Mapped IO라고 한다. 또한 Disk에서 Memory로 CPU를 거치지 않고 바로 전송하는 Direct Memory Access를 사용할 수도 있다. 해당 수행을하고 interrupt를 걸어 CPU에게 알려준다.

이러한 IO Bus는 PCI와 같이 CPU에 의존하지 않고 독립적이게 설계되었다.
