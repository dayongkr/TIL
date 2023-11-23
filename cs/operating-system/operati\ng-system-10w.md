# 운영체제개론 10주 차

## Discontiguous Memory Allocation

process image를 여러 개의 block으로 나누어서 메모리에 올리는 방법이다.

### Paging

fixed size의 page로 나누어 physical memory에 올리는 방법이다. logical address는 page number와 offset(displacement)으로 나누어진다. logical address를 사용하다보니 physical address로 바꾸는 과정이 필요한데 이를 address mapping이라고 하고 이를 위해 page table을 사용한다.

address mapping은 logical address의 page number로 page table을 참조하여 frame number를 얻고 이를 offset과 합쳐서 physical address를 얻는다.

### Segmentation

variable size의 segment로 나누어 physical memory에 올리는 방법이다. logical address는 segment number와 offset으로 나누어진다. 보통 segment는 code, data, stack등으로 나누어진다. 이 방법은 segment table을 사용하는데 base와 limit으로 이루어져 있다. base는 segment의 시작 주소이고 limit은 segment의 길이이다.

## Virtual Memory

프로그램을 여러 block으로 나누고 필요한 block만 메모리에 올리는 방법이다. 덕분에 메모리 공간을 효율적으로 사용할 수 있고 cpu utilization도 높일 수 있다. 그리고 프로그램을 memory로 load하는 과정이 빨라진다. 하지만 page fault가 발생할 수 있고 address mapping을 위한 overhead가 더 생긴다.

virtual memory의 구현 방법은 demand paging과 segmentation이 있다. 이 두 개를 살펴보기 전 block mapping에 대해 알아보자. block mapping은 virtual address를 block number와 offset으로 정의하고 block map table을 통해 physical address를 얻는다. 이 때 resident bit을 통해 해당 block이 메모리에 있는지 없는지를 확인할 수 있다. 없다면 page fault가 발생하고 page fault handler가 해당 block을 메모리에 올린다.

### Demand Paging

Discontiguous Memory Allocation에서의 paging과 비슷한데 필요한 page만 메모리에 올리는 방법이다. 이를 paper라고 하고 프로세스 전체를 메모리에 올리고 내리는 것을 swapper이라고 한다. paging은 logical partition하지 않고 예를들어 4KB씩 나누어서 메모리에 올린다.

Addressing mapping을 하는 방법은 3가지가 있다.

- Direct Mapping
  - In memory PMT를 사용하여 page number를 frame number로 바꾼다.
  - memory access가 두 번 발생해서 성능상 좋지 않다.
  - pmt size가 너무 크다.
- Associative Mapping
  - TLB(Translation Lookaside Buffer)를 사용하여 search하는 과정에서의 성능을 향상시킨다.
  - parallel search를 통해 빠르게 찾을 수 있다.
- Hybrid Mapping
  - Direct Mapping과 Associative Mapping을 혼합한 방법이다.
  - small TLB를 사용하여 Associative Mapping을 하고 TLB miss가 발생하면 Direct Mapping을 한다.
  - cache처럼 locality 성질을 활용하여 성능을 향상시킨다.

이 외로 page-table resigster, hashed page table, inverted page table, hierarchical paging등이 있다.

page-table register는 일부 register를 사용하여 page table을 저장하는 방법이고 hierarchical paging은 page number을 여러 개의 field로 나누어서 page table을 여러 개로 나누어 load 해야 하는 page table 수를 줄이는 방법이고 inverted page table은 page table을 frame number로 indexing하여 page table의 크기를 줄이는 방법인데 search overhead가 크다.
