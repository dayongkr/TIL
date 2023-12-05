# 운영체제 15주 차

## Free Space Management

- Bit vector(bitmap)
  - 각 블록에 대해 1비트를 할당
  - linux ext에서 사용
  - 블록의 개수가 많아지면 비트 벡터의 크기가 커짐
- Linked list
  - 각 블록에 대해 다음 블록의 주소를 저장
  - 빈 공간을 찾기 위해 순회하는 시간이 오래 걸림
- Grouping
  - linked list와 비슷하지만 grouping은 한 block에 여러 개의 빈 공간을 저장
  - UFS에서 사용
- Counting
  - free block의 첫 주소와 연속된 free block의 개수를 저장

## Unix File System

- boot block
  - 부트 가능한 파티션인지 확인
  - 맨 앞에 위치
- superblock
  - 파티션의 크기, free block의 수, free block의 위치, block size, FCB의 위치 등을 저장
  - boot block 다음에 위치
- inode list
  - inode를 저장
  - superblock 다음에 위치
  - inode
    - indexed allocation을 사용하기 때문에 디스크의 주소들을 inode에 저장한다.
    - access list
    - file owner, type, access time, size, # of links
  - disk address (pointer당 4byte)
    - direct block -> 10개 나머지는 1개씩
    - single indirect block
    - double indirect block
    - triple indirect block

## Linux File System

### ext2

- UFS와 달리 block group 개념이 추가
- 맨 앞은 boot block이고 그 이후는 group들로 구성
- inode list와 data block의 거리가 멀다는 문제를 해결ㅎ기 위해 block group을 사용
- 또한 같은 파일의 block들이 흩어져 있을 수 있기 때문에 block group을 사용
- 기존에 FFS도 Cylinder group을 사용했었다.
- 각 group의 구성
  - superblock
    - kernel은 맨 앞 superblock을 사용
      - 나머지 그룹의 superblock은 backup용
    - fs의 정보
  - group descriptor
    - 그룹의 정보
  - data block bitmap / inode bitmap
    - block의 사용 여부
  - inode table
    - file의 inode를 저장
  - data block
  - 12개의 direct block과 single indirect block, double indirect block, triple indirect block을 사용

### ext3

- ext2의 journaling 버전
- commit과 checkpoint를 사용
- commit하면 journal area에 저장하고 checkpoint하면 journal area의 내용을 file system에 저장
  - 5초마다 commit, 5분마다 checkpoint
- 만약 commit 전 fail이 발생하면 journal area의 내용을 무시
- 만약 commit 후 fail이 발생하면 journal area의 내용을 file system에 저장

### ext4

- 16TB 이상의 파일을 지원
- Extent mapping
  - 파일의 block들을 연속된 block들로 저장
- multiblock allocation
  - 한 번에 여러 개의 block을 할당
- delayed allocation
  - 파일의 block을 할당하지 않고 write를 먼저 한다.
