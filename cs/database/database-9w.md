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

모든 record가 같은 크기를 가지고 있을 경우를 가정하고 설명한 것인데 그럴 일이 없으므로 패스

### Variable-Length Records - Tuple Oriented, Slotted Page Structure-

page 안에 record가 저장되는 방식을 설명한다. data와 slot으로 구성되어 있는데 서로 반대편에서 시작한다. slot은 record의 위치와 크기를 저장한다.(<record offset, length>) 그리고 slot의 맨 앞에는 slot의 개수를 저장한다.
나머지는 free space이고 data와 slot array가 만나면 가득 찬 것이다.
