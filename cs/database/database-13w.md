# 데이터베이스개론 13주 차

## Transaction

여러 쿼리가 담긴 transaction이 들어오면 DBMS는 이를 여러 단계로 나누어서 실행한다. 이 때 데이터를 불러오고 저장하는 것에 많은 시간을 쓰는 것이 아닌 ACID를 보장하는 것에 시간을 쓴다. 그만큼 중요하고 비용이 많이 드는 작업이다.

어쨋든 Transaction은 unreliable computers와 concurrent executions 문제를 해결하기 위한 좋은 추상화 방법이다. DBMS가 CC와 recovery를 잘 관리하기 때문에 사용자는 직접 개발할 필요 없이 transaction을 사용하면 된다.

> CC와 recovery를 위한 기본 단위로 transaction을 사용한다.

간단하게 이러한 것들이 작동하는 방법을 설명하자면 실행하는 동안 log를 남겨 놓고, 실패하면 log를 보고 이전 상태로 되돌리는 방식으로 복구를 하고 어떠한 transaction이 실행되면 해당 버퍼를 lock을 걸어서 다른 transaction이 접근하지 못하게 하여 consistency를 보장한다.

### Consistency vs Isolation

Consistency는 transaction이 실행되기 전과 실행된 후에도 DB의 상태가 일관성을 유지하는 것을 말한다. 즉 사전에 정의된 제약 조건을 만족하는 상태가 유지되어야 한다. Isolation은 transaction이 실행되는 동안 다른 transaction의 영향을 받지 않는 것을 말한다.

### ACID

ACID는 Atomicity, Consistency, Isolation, Durability의 약자이다. 이는 transaction이 안전하게 실행되기 위한 4가지 특성이다.

- Atomicity: transaction은 모두 실행되거나 모두 실행되지 않아야 한다.
  - all or nothing
- Consistency: transaction은 DB의 일관성을 유지해야 한다.
- Isolation: transaction은 다른 transaction의 영향을 받지 않아야 한다.
- Durability: transaction이 성공적으로 실행되면 그 결과는 영구적이어야 한다.
  - log를 통해 복구가 가능하다.

이러한 것들은 incomplete transaction에 의해 발생하는 문제를 해결하기 위한 것이다. incomplete transaction은 보통 사용자, 시스템 충돌, deadlock 등에 의해 kill되어 발생한다.

### Schedule

transaction은 interleaved execution으로 실행된다. 이 때 interleaved execution은 transaction이 실행되는 순서를 말한다. 이들의 결과는 순서대로 실행했을 때와 같아야 한다. 이를 serializable schedule이라고 한다.

- serial schedule: transaction이 순차적으로 실행되는 것
- serializable schedule: serial schedule과 같은 결과를 내는 schedule
- Equivalent schedule: transaction의 결과가 같은 schedule

#### Anomalies with interleaved execution

- Reading uncommitted data
  - dirty read
  - transaction이 commit되지 않은 데이터를 읽는 것
  - W-R conflict
- Non-repeatable reads
  - transaction이 같은 데이터를 두 번 읽었을 때 값이 다른 것
  - R-W conflict
- Overwriting uncommitted data
  - transaction이 commit되지 않은 데이터를 덮어쓰는 것
  - W-W conflict
  - dirty write

#### Lock Based Concurrency Control

위와 같은 Anomalies를 방지하기 위해 lock을 사용한다. Lock에는 2가지 경우가 있다.

- Shared lock
  - Multiple transaction들이 동시에 읽을 수 있다.
  - Read-only transaction
- Exclusive lock
  - 하나의 transaction만 읽고 쓸 수 있다.

오직 Read transaction만이 shared lock을 얻을 수 있다. Lock-based CC는 비관적으로 최대한 많은 lock을 걸어서 CC를 보장한다. 때문에 Write를 하면 commit이 되기 전까지는 lock을 걸어버린다.

lock을 거는 protocol을 Two-phase locking protocol(2PL)이라고 하는데 해당 프로토콜은 하나의 transaction이 lock을 release하기 시작하면 그 이후에는 lock을 acquire하지 못한다. 때문에 lock이 걸리는 부분과 release되는 부분으로 나뉘어 2 phase라고 불린다.

### Transaction Support in SQL

SQL에서는 record에 lock byte를 두어 record 단위로 lock을 관리한다. 하지만 이렇게 관리를 하면 새로운 record가 추가되면 이를 관리할 수가 없어 phantom problem이 발생한다.

표준 SQL에서는 Isolation level을 4단계로 나누어서 관리한다.

| Isolation level  | Dirty read | Dirty write | Non-repeatable read | Phantom read |
| ---------------- | ---------- | ----------- | ------------------- | ------------ |
| Read uncommitted | N          | Y           | Y                   | Y            |
| Read committed   | N          | N           | Y                   | Y            |
| Repeatable read  | N          | N           | N                   | Y            |
| Serializable     | N          | N           | N                   | N            |

이와 같이 관리하는데 Serializable은 모든 문제를 해결할 수 있지만 Lock을 너무 많이 걸어서 성능이 떨어진다.

Read Committed에서의 Read lock은 기간이 짧지만 Repeatable read에서의 Read lock은 기간이 길다. 각 Level의 차이점은 다음과 같다.

- Read uncommitted
  - W blocks W but not R
- Read committed
  - W blocks R
- Repeatable read
  - R blocks W
- Serializable
  - R blocks R

### CC Mechanisms in Oracle

Oracle에서는 single-version이 아닌 timestamp-based multi-version(MVCC)를 사용한다.

#### MVCC

MVCC는 오직 write rock만 하며 commitSCN에 따라 multi-version을 관리한다. 각 transaction 또는 SQL문은 각자의 timestamp를 가지고 있고 이를 사용해 version을 관리한다. 이와 같은 multi-version은 undo segment를 사용하여 rollback을 지원한다.

많은 DBMS에서 Oracle과 같이 MVCC를 사용하여 교수님이 설명하셨다.

#### Oracle Isoaltion Levels

Isolation level이 Read committed(Default), Serializable 두 가지만 지원한다.

Oracle은 같은 page를 buffer pool에 여러 버전으로 clone 해두고 이를 사용한다. 때문에 read lock이 없어도 repeatable read를 보장할 수 있고또한 record 별로 timestamp를 관리하기 때문에 해당 튜플 이후에 삽입 및 수정된 튜플은 필터링하여 phantom read를 방지할 수 있다. 때문에 위 2가지 isolation level만 지원해도 되는 것이다.
