# 운영체제개론 13주 차

## File System

- HDD
  - Platter -> Surface -> Track -> Sector
  - Cylinder: 같은 위치의 Track을 모아놓은 것
  - Spindle: Platter를 돌리는 축
  - Gap: Sector를 구분하는 구멍
  - Poistioner: Arm의 축
  - Head: Sector를 읽고 쓰는 장치
  - Arm: Head를 이동시키는 장치
  - Access Time = Seek Time + Rotational Latency + Transfer Time
  - Seek Time: Head를 target sector를 퐇마하는 cylinder로 이동시키는 시간
  - Rotational Latency: Head가 target sector에 도달하는 시간
  - Transfer Time: Sector를 읽고 쓰는 시간
  - Capacity: sector의 크기 \* sector의 개수 \* track의 개수 \* surface의 개수 \* platter의 개수
  - In-place writing: overwrite가 가능한 경우
  - Direct access: 임의의 위치로 이동할 수 있는 경우
  - Address: Cylinder Number | Surface Number | Sector Number
- SSD
  - Flash memory
  - FTL: Flash Translation Layer (SSD의 controller)
  - In-place writing이 불가능하다.
  - Page단위로 읽고 쓴다.
  - Wear out: 더 이상 쓸 수 없는 상태
  - Address: Block Number | Page Number

### File

- File: 관련된 정보를 모은 것을 이름을 부여한 것
- FCB(File Control Block): 파일의 정보를 저장하는 곳
  - Name, Identifier, Type, Size, Protection, Time, Date, Location, Owner, ...
  - Unix, Linux에서는 inode라고 한다.
- File operation: System call을 통해 수행한다.
  - Create
  - Read
  - Write
  - Seek(Reposition)
  - Delete: 모두 지우기
  - Truncate: file size만 초기화하고 Directory entry는 남겨둔다.
  - Open
    - Open file table에 FCB를 저장한다.
      - Open file table: Per-process table, System-wide table(global)
      - unix에서는 descriptor table은 per-process table이고 file table과 inode table은 system-wide table이다.
    - File descriptor(pointer)를 반환한다.
- File types
  - Ordinary file(Regular file)
  - Directory file
  - Device file
  - Symbolic link file
  - Named pipe file
  - Magic number: 실행 파일을 구분하는 방법
- File structure
  - 실행 파일, Directory file은 보통 구조를 제한한다.
  - ELF(Executable and Linkable Format)
    - ELF header: ELF 파일의 정보를 저장한다.
    - Segment header table: 실행 시간에 사용되는 segment의 정보를 저장한다.
    - Section header table: section의 갯수와 section의 정보를 저장한다.

### Directory Structure

- Flat (Single-level) directory
  - 파일을 모두 같은 directory에 저장한다.
  - 파일 이름이 중복될 수 있다.
  - 보통 단일 사용자 시스템에서 사용한다.
- Two-level directory
  - 사용자마다 directory를 만든다.
  - 파일 이름이 중복될 수 있다.
  - MFD(Master File Directory): 사용자의 directory를 저장하는 directory
  - UFD(User File Directory): 사용자의 파일을 저장하는 directory
- Hierarchical directory
  - tree 구조로 directory를 만든다.
  - Home directory: 사용자의 root directory
  - Current directory: 현재 작업 중인 directory
  - Absolute path: root directory부터 시작하는 경로
  - Relative path: 현재 directory부터 시작하는 경로
- Acyclic graph directory
  - Link를 사용하여 directory를 만든다.
  - Hard link: inode를 공유한다.
  - Soft link: symbolic link, inode를 공유하지 않는다.
  - 다양한 path를 사용할 수 있다.
- General graph directory
  - cycle이 존재하는 Acyclic graph directory

### Mounting

- Mounting: 다른 파일 시스템을 현재 파일 시스템에 연결하는 것
- Mount point: 연결되는 지점
- ~/dev/dsk1에 있는 파일을 ~/usr에 연결하고 싶다면 ~/usr에 mount point를 만들고 ~/dev/dsk1을 연결한다.
- Mac, Windows에서는 자동으로 mount한다.
- Unix, Linux에서는 mount 명령어를 사용한다.

### Consistency Semantics

- 데이터의 수정이 발생하면 다른 유저들에게 언제 보여지는지를 결정하는 것
- Unix semantics: 데이터의 수정이 발생하면 다른 유저들에게 바로 보여진다.
  - Lock이 read, write 단위로 존재한다.
- Session semantics: 데이터의 수정이 발생하면 session이 끝나고 읽기를 시도하는 유저들에게 보여진다.
  - Lock이 session 단위로 즉 open ~ close 단위로 존재한다.
  - AFS(Andrew File System)에서 사용한다.
- Immutable semantics: 수정이 발생하면 새로운 파일을 만들고 수정된 파일을 가리킨다.
