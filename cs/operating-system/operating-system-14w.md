# 운영체제 14주 차

## File Protection

File Protection은 파일에 대한 접근의 종류를 제한하는 것이다. 보통 종류는 read, write, execute가 있다. password로 접근을 제한할 수 있지만 이는 비효율적이다. 따라서 보통 access matrix를 사용한다. access matrix는 domains와 objects간에 access를 허용하는지를 나타내는 행렬이다. 예제로는 domain끼리 switch할 수 있는 것, copy right가 있어 domain끼리 copy할 수 있는 것, owner right가 있어 domain의 권한을 변경할 수 있는 것, control right이 있어 모든 object의 권한을 변경할 수 있는 것이 있다.

### Access Matrix

이를 그대로 사용하면 행렬의 크기가 너무 커지므로 보통 3가지 방법을 사용한다.

- Global Table
  - 비어있지 않은 entry만 저장한다.
  - 그래도 table의 크기가 너무 커진다.
- Access list
  - 각 object마다 access list를 만든다.
  - 이를 Inode에 permanent하게 저장한다.
- Capability list
  - 각 domain마다 capability list를 만든다.
  - 이를 process control block에 저장한다.

## File System Implementation

### File System Structure

- Logical file system
  - 파일 시스템의 메타데이터 관리
  - directory structure, fcb, protection등을 관리한다.
- File organization module
  - logical block을 physical block으로 mapping
  - free space management
- Basic file system
  - PB를 읽고 쓰기 위해 device driver와 통신

### File System Layout

- Boot control block
  - 부트 가능한 파티션인지 확인
  - 맨 앞에 위치
- Volume control block(Superblock)
  - 파티션의 크기, free block의 수, free block의 위치, block size, FCB의 위치 등을 저장
  - Boot control block 다음에 위치
- Directory structure
  - Data block에 저장
  - 파일 이름, inode number등을 저장
- FCB
  - owner, permission, size, data block의 위치 등을 저장
  - Volume control block 다음에 위치

### Kernel Data Structure

- Open file table
  - open된 파일의 정보를 저장
  - 파일의 위치, 파일의 상태, 파일의 FCB의 위치 등을 저장
  - per-process, per-system
- Mount table
  - 마운트된 파티션의 정보를 저장
  - device number, mount point, superblock을 가지고 있는 buffer의 pointer, root inode의 pointer 등을 저장
- VFS
  - 파일 시스템의 종류에 상관없이 동일한 인터페이스를 제공
  - vnode를 제공하고 이를 나중에 inode로 변환한다.

### Directory Implementation

- Linear list
  - 한 디렉토리 안에 있는 파일들을 linear list로 저장한다.
- Hash table
  - 파일 이름을 hash function을 통해 hash value로 변환한다.
  - 이를 hash table에 저장한다.
  - 한 디렉토리에 많은 파일이 있을 때 유용하지만 overhead가 크다.
- directory caching을 하기 때문에 linear list가 더 효율적이다.

### File Allocation

- Contiguous allocation
  - 파일을 연속된 블록에 저장한다.
  - 파일의 크기가 커지면 external fragmentation이 발생한다.
  - 파일의 크기가 커지면 파일을 저장할 수 있는 공간이 없어진다.
  - extents라는 hybrid 방법을 사용한다.
- Linked allocation
  - FAT(File Allocation Table)에 다음 블록의 위치를 저장한다.
  - direct access가 불가능하다.
- Indexed allocation
  - inode에 파일의 블록의 위치를 저장한다.
  - direct access가 가능하다.
  - index block에 블럭의 위치를 저장한다.
  - index block의 크기 문제를 해결하기 위해 Linked scheme, Multilevel scheme, Combined scheme을 사용한다.
