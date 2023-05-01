# 데이터베이스 9주 차

Disk에 Logical Table을 어떻게 물리적으로 저장을 하는지 배우게 된다.

## Overview

일단 Disk에서 데이터를 읽고 쓰는 IO의 기본 단위는 Page로 4kb에 해당한다. 보통 page 또는 block으로 혼용에서 불린다.

Disk 안에는 이러한 Index, Data Files를 제외한 한 가지 파일이 더 있는데 이를 System Catalog이라고 한다. 해당 파일 안에는 dbms가 최적화하기 위해 필요한 데이터들을 포함하고 있다.

## Files of Records

어쨋든 하위 계층(between buffer manager and disk space manager)에서는 block interface로 block 단위로 사용하고 좀 더 상위 계층에서는 File of record interface로 record 단위로 사용한다. 이 record는 pages 안에 존재한다. 여기서 File(per table)은 records의 집한인 pages의 집합이다.

물리적으로 DBMS는 아래 3가지 동작을 지원해야 한다.

1. Insert/Delete/Update a record
2. Fetch a particular record (by record id)
3. Scan all records

### Unordered (Heap) Files

특정한 순서 없이 records를 저장하고 있다. 때문에 우리는 record를 찾고 쓰기 위해서는 아래 3가지 동작을 수행해야 한다.

1. keep track of the pages in the file
2. keep track of the records in each page
3. keep track of the free space in each page

이는 space manager가 수행한다.

이를 구현하는 방법은 여러가지가 있는데 첫 번째는 list로 구현하는 것인데. 해당 방법은 record를 삽입하기 위해 page를 찾는 과정에서 불필요한 disk IO가 많이 발생해 비효율적이다.

두 번째 방법은 directory를 사용하는 것인데, directory는 pages의 집합으로 이루어져 있다.

### Oracle: Tablespaces , Segments, Extents, Blocks

- Tablespace
  - 여러개의 segment로 구성되어 있다.
  - DBMS file의 논리적인 단위이다.
  - 여러개의 datafile로 구성될 수 있다.
- Segment
  - 여러개의 extent로 구성되어 있다.
  - Table, Index, Rollback, Temporary, LOB 등의 segment가 있다.
- Extent
  - 여러개의 block으로 구성되어 있다.
  - 한번에 할당되는 disk space의 단위이다.
- Block
  - 여러개의 record로 구성되어 있다.
  - 한번에 읽고 쓰는 disk space의 단위이다.

테이블을 생성하면 처음에는 하나의 extent에 적은 block을 배정 받다가 점점 많은 block을 할당 받는다.

## Page Formats

### Fixed-Length Records

Packed 방식과 Unpacked 방식이 있는데 먼저 Packed 방식은 Slot 사이에 Free Space가 없도록 계속 정렬을하는 방식인데 이렇게 되면 record id를 계속 바꿔야 하기 때문에 이를 참조하는 경우 불필요한 과정들이 생기게 된다. 따라서 이렇게 구현하지 않고 record를 삭제할 경우 빈 공간으로 남겨두는 unpacked 방식을 사용한다. 하지만 Unpacked는 이러한 Free space를 표시하기 위해 추가적인 공간이 필요하다. 참고로 Bitmap을 통해 표시한다.

### Variable-Length Records - Tuple Oriented, Slotted Page Structure-

page 안에 record가 저장되는 방식을 설명한다. data와 slot으로 구성되어 있는데 서로 반대편에서 시작한다. slot은 record의 위치와 크기를 저장한다.(<record offset, length>) 그리고 slot의 맨 앞에는 slot의 개수를 저장한다.
나머지는 free space이고 data와 slot array가 만나면 가득 찬 것이다.

### Oracle Formatted Block Dumps

실제 Dumps 파일을 보게되면 records가 몇개 있는지(nrow), 시작 offset(fsbo)과 end offset(fseo)등이 있고 각 record마다의 length(tl)와 lock(lb)이 걸려 있는지, col count(cc)등이 있다.

### Data Layout on Disk Page

#### Row-Store

일반적으로 OLTP 같은 경우에는 Row를 기반으로 검색을 하기 때문에 기본적으로 DBMS는 row를 기반으로 저장한다. 이러한 방식을 row-store라고 한다.

#### C-Sore

하지만 OLAP 같은 경우에는 Column 단위로 분석하는 경우가 많아 Column을 기반으로 저장하는 방식이 있다. 이러한 방식을 column-store라고 한다. Oracle 같은 경우에는 기본적으론 row-store을 사용하지만 in-memory에 column-store도 같이 사용한다고 한다.

## Record Formats

Fixed Length일 경우 Base address와 각 field의 크기를 안다면 서로 더해서 해당 field의 address로 갈 수 있다.

하지만 Variable Length일 경우에는 각 field의 크기를 알 수 없기 때문에 field의 끝을 알리는 Special Symbols를 통해 field의 끝을 알 수 있다. 하지만 이 같은 경우엔 원하는 값까지 scan을 해야하는 cost가 발생하기 때문에 record의 앞에 각 field의 offset을 제공해 바로 찾아갈 수 있게 하는 방법도 사용한다.

### Row Layout in Oracle

기본적으로 Row head와 column data로 구성되어 있다.

- Row Head
  - Row Head에는 Row flag, Lock byte, Column count등이 있다.
- Column Data
  - 맨 앞에는 column length가 있다.(1, 3byte)
  - 긴 field을 경우 앞에 0xFE를 붙여서 표시한다.
  - 0xFF는 null을 의미한다.

### System Catalogs

- 각 Relation 별
  - 이름, 파일 구조, 파일 이름
  - 속성 이름 및 타입
  - 인덱스 이름
  - 무결성 제약조건
- 각 index 별
  - 자료구조와 key fields
- 각 view 별
  - 이름과 정의
- 통계, 사용자 정보, buffer pool 정보 등

위와 같이 oracle system을 위한 정보들이 담겨있다.

## File Access Methods

### Full Table Scan

테이블의 모든 record를 읽는 방법이다. Index가 없는 경우에는 이 방법을 사용한다. disk I/O를 얼마나 필요한지를 계산하는 cost model이라는 것이 있다.

#### Cost Model

필요한 데이터들은 이미 메모리에 있을 수 있기 때문에 이를 염두하고 계산을 해야 한다. Oracle은 미리 정의한 db_file_multiblock_read_count 테이블을 사용하는데 cost는 블록의 갯수 / Adjusted Multiblock Read Count + 1 이다. 당연히 실제 cost와 다를 수 있다.

### Index Range Scan

Index가 있을 경우 index를 통해 record를 읽는 방법이다. 덕분에 table 전체를 스캔할 필요가 없어 physical reads가 상당히 줄어든다.

## Disk Space Management

disk의 공간을 관리하는 DBMS의 가장 낮은 계층이다. 보통 더 높은 계층에서의 호출로 인해 page를 할당/해제를 하고 읽고/쓰는 동작을 수행한다. a sequence of pages을 위한 요청은 disk에 sequentially 하게 할당되어야 한다.

Files and Access Mehtods 아래의 low level은 shared components이고 그 위 layer들은 사용자마다 다른 components이다.

## Buffer Management

### OLAP vs OLTP

```SQL
SELECT SUM(b) FROM TEST;
```

OLAP(On-Line Analytical Processing)은 분석계 데이터 및 데이터를 처리하는 방법을 의미한다.

```SQL
SELECT B FROM Test WHERE A = 500000;
```

OLTP(On-Line Transaction Processing)은 운영계 데이터 및 데이터를 처리하는 방법을 의미한다.

즉 OLAP은 비지니스 활동에 대한 평가 및 분석이고 OLTP는 비지니스 활동을 지원하는 것을 의미한다. 따라서 OLAP은 보통 데이터 전체를 대상으로 분석을 하고 OLTP는 특정 데이터를 대상으로 처리를 한다. 따라서 OLTP는 index를 사용하는 것이 대부분이다.

어쨋든 둘다 Buffer manager를 통해 buffer에 page가 있는지 확인하고 없으면 disk에서 읽어와서 buffer에 올리고 있으면 buffer에서 읽어오는 동작을 수행한다.

### Buffer Management in a DBMS

data가 DBMS를 위한 RAM(Buffer Pool)에 있어야 작동을 한다. 때문에 없을 경우 disk에서 가져오는데 Buffer Pool이 가득 차 있을 경우 어떤 page를 disk로 내릴지 결정해야 한다. 이를 위해 DBMS는 replacement policy를 사용한다. 하지만 temporal locality와 access skew가 access pattern에 존재해 small buffer cache로도 충분히 효율적으로 동작할 수 있다.

> access skew: 다른 page에 비해 특정 page에 대한 access가 많은 경우, temporal locality: 최근에 접근한 page를 다시 접근할 확률이 높은 경우

#### When a Page is Requested

Buffer pool information table을 통해 page가 buffer pool에 있는지 확인한다. 해당 테이블에는 frame number, page id, pin_cnt, dirty가 있는데 pin_cnt는 pin이 걸린 횟수를 의미한다. 따라서 pin_cnt가 0 이어야지 candidate for replacement가 될 수 있다. dirty는 page가 수정되어 disk에 쓰여야 하는지를 의미한다. dirty가 활성화 되어 있으면 replace 될 때 undo log가 disk에 쓰였는지 확인하고 안 되어 있으면 disk에 쓴다.

page가 buffer pool에 없을 경우 disk에서 읽어와서 buffer pool에 올린다. 다 쓰고 나면 unpin을 해야 한다.

#### Buffer Replacement Policy

buffer pool에 있을 경우를 Hit, 없을 경우를 Miss라고 한다. Hit ratio는 N of hits / N of Page requests이다. 하나의 miss가 발생하면 한 번 또는 두 번의 Physical IO가 발생하므로 Hit ratio 1% 차이도 크다고 볼 수 있다. 때문에 buffer pool에서 replacement policy를 잘 정해서 자주 사용되는 page( Hot Page)를 buffer pool에 유지하고 Cold Page를 대체하는 것이 중요하다.

Replacement Policy에는 Random, FIFO, LRU, MRU, LFU, Clock 등이 있다. LRU는 Least Recently Used로 가장 마지막에 unpinned 된 것을 track해 이를 대체한다. MRU는 Most Recently Used로 가장 최근에 unpinned 된 것을 track해 이를 대체한다. LFU는 Least Frequently Used로 가장 적게 사용된 것을 track해 이를 대체한다.

우리가 주로 배울 내용은 LRU로 Queue로 구현을 할 수 있고 가장 흔한 policy이다.

#### LRU is NOT Scan-Resistant

만약에 sequential 하게 데이터를 가져온다면 끊임없이 replacement가 발생하는 경우가 생긴다. 따라서 모든 데이터를 scan하는 OLAP에서는 LRU가 적합하지 않을 수가 있다.

#### Clock Algorithm

cycle에 frame을 배정하고 각 frame에 reference bit을 저장한다. pin count가 0이 되면 reference bit가 켜진다. 이렇게 켜진 것은 자기 차례가 오면 꺼지고 이렇게 꺼진 것을 찾았을 때 replacement를 수행한다. 따라서 다 썼다고 바로 replacement가 되는 것이 아니라 한 번의 기회를 더 준다.

#### Belady's Min Algorithm

미래에 relation의 상태를 알 수 있다면 어떻게 replacement algorithm을 optimizing 할 수 있을지에 대한 내용으로 가장 오래 필요 없을 것을 대체하는 것이 좋다고 나와 있다.

### IO

#### CPU IO Overlapping

miss가 나면 disk IO가 발생하고 이 동안 CPU는 다른 작업을 수행할 수 있다. 이럴 때 멀티 쓰레딩을 통해 CPU IO Overlapping을 할 수 있다.

#### IO Crisis in OLTP

hdd를 사용할 때에는 IOPS가 매우 낮아서 여러 hdd를 사용해야 했다. 그래서 상당한 비용이 발생했다. 또한 balanced system을 구축하기 위해서는 CPU가 빨라지는 속도에 맞춰서 disk의 속도도 빨라져야 했다. 하지만 이러한 무어의 법칙에 disk의 성장 속도가 따라가지 못했다. 때문에 결국 HDD를 추가 구매해야 했다.

하지만 SSD가 나오고 이러한 문제가 해결되었다. SSD는 IOPS가 높아서 여러 개의 SSD를 사용할 필요가 없어졌다. 덕분에 비용 문제가 많이 해결되었다.

이러한 과정에서 HDD를 제조하는 회사가 부를 축적했다가 main memory를 제조하는 회사가 부를 축적했고 ssd 등장으로 Flash memory를 제조하는 회사가 부를 축적했다. 이러한 것들을 보면 시대의 흐름에 따라 부를 축적하는 회사가 바뀌는 것을 볼 수 있다.

### 5 min rule

어떤 데이터를 어떠한 저장 장치에 저장해야 효율적인 가를 정의한 규칙으로 최대 5분마다 사용하는 데이터는 memory에 저장하고 5분 이상 사용하지 않는 데이터는 disk에 저장한다.

요즘에는 10초 법칙도 나와서 10초마다 사용하는 데이터는 ssd에 저장하고 10초 이상 사용하지 않는 데이터는 disk에 저장한다.
