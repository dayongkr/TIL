# 데이터베이스개론 14주 차

crash Recovery(Recovery Manager)에 대해서 배운다.

## Basic

### Failures and Recovery

- Atomicity
  - Transaction은 모두 수행되거나 모두 수행되지 않아야 한다.
- Consistency
  - Transaction은 DB의 consistency를 유지해야 한다.
  - Transaction은 DB의 integrity constraints를 만족해야 한다.
- Isolation
  - Transaction은 다른 Transaction에 영향을 주지 않아야 한다.
- Durability
  - Transaction이 commit되면 그 결과는 영구적이어야 한다.

매번 보는 ACID에서 우리는 특히 Atomicity와 Durability에 집중하고 이를 지키기 위해 어떠한 방법을 사용하는지 배운다.

### Failure Classification

- Transaction Failure
  - Rollback or killed by deadlock -> undo
- System Failure
  - OS, DBMS, HW, Network -> redo, undo
  - 여기를 주로 다룬다.
- Media Failure
  - disk head crash, disk surface damage -> archive recovery

### Disk Writes

일단 시작에 앞서 아래 3가지 가정을하고 시작한다.

- Page: update가 발생하는 최소 단위
- In-place update: update가 발생하면 그 자리에서 update가 발생한다.
  - Out-of-place update: update가 발생하면 새로운 page를 할당하고 그곳에 update를 한다.
- Atomic propagation: single page write가 발생하면 그것은 atomic하게 발생한다.
  - multi-page write는 shadow page를 사용하여 해당 page에 저장을하다가 commit이 되면 그때 실제 page에 저장한다.

### Transaction Force & Steal

- Force
  - commit이 되면 모든 page를 disk에 쓴다.
  - 반응이 느리다.
  - 구현이 쉽다.
- No-force
  - commit이 되면 log만 disk에 쓴다.
  - redo log를 사용한다. (recovery를 위해)
  - 반응이 빠르다.
- Steal
  - commit 되지 않은 page를 disk에 쓴다.
  - 이전 값은 undo log에 저장한다. (rollback을 위해)
  - buffer management의 policy이다.
- No-steal
  - commit 되지 않은 page를 disk에 쓰지 않는다.

### SQLite

SQLite는 recovery를 위해 Rollbakc, WAL journal file을 저장하는데 이는 수정사항이 생기면 생기고 commit하면 삭제한다. 이들은 또한 Force, steal을 사용하여 구현되어있다. 그리고 single user이기 때문에 concurrency control이 필요하지 않고 lock은 file level에서만 사용하여 record level을 사용하는 Oracle과 다르다.

## Log

각 page가 수정될 때 마다 상응하는 log가 log buffer에 생성되는데 이때 LSN(Log Sequence Number)을 통해 log를 관리한다. LSN은 log가 생성된 순서를 나타내는 숫자이다. 이 LSN은 page에 저장되는데 이를 pageLSN이라고 한다. log based recovery는 아래 2 가지 특징을 가진다.

- Force log at commit
  - commit이 되면 log를 disk에 쓴다.
- Write-ahead logging
  - page를 disk에 쓰기 전에 log를 disk에 쓴다.

### Basic idea

매 update하기 전에 log를 log buffer에 생성을 하고 버퍼가 다 차거나 특정한 상황에 이를 file에 저장한다. 보통 log에는 최소한의 정보만을 저장한다. (ex. page id, offset, old value, new value) 이러한 정보를 담는 방법은 3가지가 있다.

- Physical logging
  - page id, offset, old value, new value(지금까지 배운 방법)
- Logical logging
  - e.g. insert, A table, r
  - 행위, 어디에, 무엇을
- Physiological logging
  - 위 두 방법을 혼합한 방법

어쨋든 database는 이러한 log와 disk에 있는 page를 혼합해서 결과를 낸다. 왜냐하면 disk에 있는 page에는 uncommited update가 있을 수 있기 때문이다. 만약에 log가 없다면 redo log을 통한 durability를 보장할 수 없고 undo log를 통한 atomicity를 보장할 수 없다.

### Two Logging Protocols

- Write-Ahead Logging
  - WAL
  - disk에 page를 쓰기전 log buffer에 있던 undo log를 disk에 쓴다.
  - undo를 위해서 필요하다.
  - uncommitted page를 disk에 내릴 때 사용되는 방법이다.
- Log Force at Commit
  - LFC
  - transaction은 commit log record가 disk에 저장이 된후에 commit이 된다.
  - redo를 위해서 필요하다.
  - commit 할 때 log만 disk에 쓰고 page는 disk에 쓰지 않는다.

이러한 과정에서는 disk에 저장이되어야 하는데 memory hierarchy 특성상 memory에 저장될 수 있다. 따라서 fsync를 사용하여 disk에 저장되도록 할 수 있다.

### Checkpoint

no-force policy에 의해 unflushed된 transaction이 많을텐데 그래도 redo log 덕분에 failure이 발생해도 복구가 가능하지만 이러한 방법은 recovery time을 증가시킨다. 따라서 checkpoint를 사용하여 recovery time을 줄일 수 있다. 이렇게 checkpoint를 사용하고 이를 log를 남기는데 이에대한 LSN은 master record와 같은 안전한 곳에 저장한다.

추후에 마지막 checkpoint 이후에 발생한 것들을 분석하고 crash가 발생한 시점 이후에 발생한 것들을 redo하고 다시 뒤로 돌아가면서 undo를 하는식으로 recovery를 진행한다.
