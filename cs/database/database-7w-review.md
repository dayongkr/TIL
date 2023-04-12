# 데이터베이스 7주 차 Review

DB Design을 다루게 된다.

## Ch 2. The Entity-Relationship Model

분리된 테이블이 아니라 통합된 테이블을 사용하면 데이터의 중복이 발생할 수 있기 때문에 데이터베이스를 설계할 때는 테이블을 분리하는 것이 중요하다.

이를 위해 Entity-Relationship Model을 사용하여 데이터베이스를 설계하고 이를 DBMS에 적용한다.

### Overview of Database Design

- Conceptual design
  - ER Diagram: Entity, Relationship, Attribute
  - UML: Class Diagram
- Logical design
  - RDB Schema
- Physical
  - index, block size, partitioning, disk allocation, ...

위와 같은 과정을 거쳐서 design을 한다.

#### Entities

Entity는 다른 객체들과 구별 가능한 실제 세계의 객체이다. 또한 유사한 Entities 끼리의 집합을 Entity Set이라고 한다.

각 Entity(사각형)는 attribute(타원형)를 가지는데 Entity를 구별할 수 있는 attribute를 key(밑줄)라고 한다. 또한 각 attribute는 domain을 가진다.

#### Relationships

마름모로 표시되는 것이 Relationship이다. Relationship은 Entity Set들 사이의 관계를 나타낸다. Relationship은 attribute를 가질 수 있다. 유사한 Relationship들의 집합을 Relationship Set이라고 한다.

이 관계는 보통 두 개의 Entities를 연결하는데 자기 자신을 가르키는 경우도 있다.

화살표 방향은 관계의 방향을 나타낸다. 관계의 방향이 없는 경우는 두 Entity가 서로 독립적인 관계를 가지는 경우이다. 이러한 관계는 1:1, 1:M, N:M, N:1 관계가 있다.

#### Participation Constraints

Participation Constraints는 Entity Set이 Relationship Set에 참여하는 정도를 나타낸다. Participation Constraints는 다음과 같은 종류가 있다. total participation, partial participation으로 나눌 수 있다. Total은 반드시 참여해야 하고 partial은 참여하지 않아도 되는 관계를 의미한다.

### Class Hierarchy

Class Hierarchy는 상속 관계를 나타낸다. 상속 관계는 부모 클래스와 자식 클래스가 있고 부모 클래스는 자식 클래스의 상위 개념이다. 부모 클래스는 자식 클래스의 속성을 모두 가지고 있고 자식 클래스는 부모 클래스의 속성을 추가로 가질 수 있다.

일반적인 Class 개념과 동일하다.

## Ch3.5 Logical DB Design

ER Diagram을 RDB Schema로 변환하는 과정을 Logical DB Design이라고 한다.

### Entity Set to Relation

일반적인 attribute는 그냥 field를 만들어주면 되는데 집합 attribute는 큰 문자열으로 정의하고 각 요소를 세미콜론와 같은 구분자로 구분하여 저장한 후 필요할 때 파싱하여 사용하면된다.

### Key Constraints

total participation의 경우 key 또는 NOT NULL로 정의하면 된다.

### Translating Class Hierarchies

각각의 테이블을 구현하던지 공통된 부분과 차이점을 나누어서 테이블을 구현하던지 한 테이블로 통합해서 구현하던지 한다.

## Ch 19. Schema Refinement and Normal Forms

Redundancy을 제거 하기 위해 Schema Refinement을 한다. Redundancy 때문에 아래 3 가지 상황으로 인해 일관성이 깨질 수 있다.

- Update anomaly
- Insertiton anomaly
- Deletion anomaly

이를 위해 Decompostion을 한다. 하지만 Decomposition으로 인해 다음과 같은 문제가 발생할 수 있다.

- Performance
- Information loss
- Dependency loss

중요한 부분이지만 자세히는 안 집고 넘어가셨다.

### Functional Dependencies - 함수적 종속성

X -> Y 라고 할 때 X가 주어지면 Y가 결정되는 관계를 함수적 종속성이라고 한다. 이는 일종의 Integrity Constraint이다. Primary Key는 함수적 종속성을 만족한다.

## Ch 25.2 Multi-dimensional Data Model

어떠한 판매에 대해서 어떤 상품, 위치, 시간에 대한 정보를 저장하고 싶을 때 사용한다. 판매를 measure이라고 하고 상품, 위치, 시간을 Dimension이라고 한다. 또한 이러한 Table을 Fact Table이라고 한다.

### Dimension Hierarchies

각 Dimension 내에서도 계층을 가진다. 예를들어 시간은 year - quarter - week - date와 같이 계층을 가질 수 있다.

### Star Schema

각 Dimension은 Fact Table의 Foreign Key로 연결되고 각 Dimension은 각각의 Table로 구현된다. 이러한 구조를 Star Schema라고 한다.
