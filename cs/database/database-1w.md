# 데이터베이스개론 1주 차

데이터베이스는 서로 연관된 큰 데이터들의 집합이고 개체(Entities)와 관계(Relationships)로 이루어져 있다.

DBMS는 데이터베이스를 관리하고 저장하기 위해 설계된 소프트웨어 패키지이다.

> e.g. IBM DB2, Oracle, MS SQL Server 등...

## File System의 특징 및 단점

1. 쿼리를 직접 구현을 해야한다.
2. 동시 제어(Concurrency control)와 충돌 복구(crash recovery)를 직접 구현해야 한다.
3. 보안 및 접근 제어를 효과적으로 관리하기 힘들다.

## DBMS

### DBMS을 사용해야 하는 이유

- Data indepedence
- Efficent data access
  - DBMS에는 쿼리에 최적화된 알고리즘이 탑재되어 데이터 접근 면에서 효율적이다.
- Data integrity(무결성) and security
- Uniform data administration
- Concurrent access and crash recovery
- Reduced application development time
  - 최종적으로 애플리케이션 개발자들은 데이터베이스 관련해서 구현할 필요가 없다 보니 개발 시간을 상당히 많이 줄일 수 있고 오류를 디버깅하는 시간도 당연히 줄어들 것이다.

### 데이터베이스를 왜 배울까

computation에서 정보로 paradime이 변하면서 매우 중요한 분야가 되었다.

### Data Models

- Data model: 데이터를 설명하기 위해 high-level 개념의 모음
  - 자세한 low-level 한 내용은 숨긴다.
  - relational model을 가장 많이 사용되며 2차원의 테이블로 데이터를 표현한다.
    - 모든 relation은 schema를 가지고 있다.
  - Schema: 특정한 data의 집합을 설명하는 것

#### Relational Data Model

- Schema
  - Relation name
  - Attribute (or field, column) and its type
  - e.g. Students(sid: string, name: string, login:string, age: integer, gpa: real)
- Relation instance
  - A set of records(or tuples, rows)
  - 실제 데이터들

#### Levels of Abstraction

- Physical Schema
  - dba가 주로 운용
  - 물리적으로 어떻게 저장되고 있는지
- Conceptual(logical) Schema
  - user/app이 운용
  - 논리 구조를 정의 (2차원 테이블 구성)
- External Schema(View)
  - user/app이 운용
  - 데이터를 유저들이 어떻게 볼지 설명

논리적으로 위 3가지 Schema가 존재하며 어떠한 이유로 Schema는 변동될 수 있다.

- SQL의 Data Definition Language(DDL)로 설명
  - External > Create view...
  - Logical > Create table...
  - Physical > Create index...; Create table ... partitioning

#### Data Independence

데이터베이스를 설치한 후 중간에 Schema를 변경하게 되는 일이 생길 텐데 각 Schema에서 변동사항이 있어도 서로에게 영향을 미치지 않는 것을 의미한다.

- Physical DI
  - Conceptual Schema의 변동사항 없이 Physical Schema를 변경한다.
- Logical DI
  - External Schema의 변동사항 없이 Conceptual Schema를 변경한다.

### Transactions

인생은 Transaction으로 가득 차 있다.

> 카톡을 사용하든 은행 앱을 사용하든 모두 Transactions를 통해 작동되기 때문에...

- Transaction의 4가지 특징 및 조건: ACID
  - Atomicity - 원자성
  - Consistency- 연속성
  - Isolation - 격리성
  - Durability - 영구성

위 특징들을 지켜줘야 하는데 이를 DBMS가 지키게 도와준다.

#### Scheduling Concurrent Transactions

DBMS는 Transactions를 동시에 왔다 갔다 하면서 처리하게 되지만 결국엔 결과는 Transactions를 Serial 하게 실행한 결과와 동일하게 해준다.

이는 Locking 기반으로 구현되어 있는데 다른 Transaction에서 이미 변경하고 있으면 해당 부분에 Lock을 걸어 충돌되는 일을 회피하게 된다.

#### Ensuring Atomicity

Transaction을 수행하다가 중간에 시스템이 shut down이 될 수 있으므로 DBMS는 전부를 수행하거나 아니면 안 하거나 둘 중의 하나로만 수행하므로 Atomicity를 보장해준다.

이는 log로 구현하는데 Transaction을 수행하면서 생기는 history을 모두 log에 저장하다가 마지막에 commit을 해주는 식이다.

### DBMS 구조

- Query Evaluation Engine
  - 입력받은 SQL을 최적화하고 파싱 등을 하는 엔진이다.
- Files and Access Methods
  - File 전체에 접근할지 인덱스를 사용할지 등을 결정하는 부분
- Buffer Manager
  - RAM에 있는 Disk에서 가져와야 하는지를 결정하는 부분
- Disk Space Manager
  - 새로운 데이터를 생성할 때 공간을 결정하는 부분

이 사이에 Transaction, Lock, Recovery Manager도 있어서 위 구조들이 ACID를 지킬 수 있게 도와준다.

앞으로 이 구조들에 대해 자세히 배울 예정이다.

## 요약

- DBMS는 큰 datasets을 유지하고 전달해준다.
- 추상화의 Levels이 data independence를 유지해준다.
- DBMS는 layered한 구조를 가진다.
- RDBMS는 Declarative interfaces와 Transaction이 주된 아이디어이다.
  - 무엇을 원하는지 적는 거지 어떻게 할지를 적는게 아니고 ACID를 지켜주는 Transaction이 중요하다.
