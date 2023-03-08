# 데이터베이스개론 2주 차 2차시

## Data Model (Relational)

- Structure
  - DDL - Definition
  - 데이터 정의
- Operations
  - DML - Manipulation
  - 데이터 조작
- Constraints
  - DCL - Control
  - 데이터 제어

데이터를 간단하게 표현하고 query 언어도 매우 깔끔해서 잘 사용하고 있는 Data Model이 되었다. XML, JSON, NoSQLs등 다양한 경쟁자가 있지만 아직 RDBM에 비해 시장 규모가 작다.

## Relational Database

Relational Database는 중복되지 않은 Relation 들의 집합이다.

Relation은 relation의 이름과 각 col의 이름 및 타입을 표현하는 Schema, rows와 cols로 이루어진 테이블인 Instance로 이루어져 있다.

### Example

Schema: Students(sid:string, name:string, login:string, age:integer, gpa: real)

|FIELDS -> |sid|name|login|age|gpa|
|-|-|-|-|-|-|
|TUPLE -> |50000|Dave|dave@cs|10|3.3|
|TUPLE -> |53666|Jones|jones@cs|18|3.4|

각 속성들을 Field라고 하고 비어 있으면 NULL이 들어가 있다.

### Relational이라고 부를까?

N-ary relation의 개념을 가져왔고 튜플이나 각 속성들의 순서가 중요치 않기 때문에 Relational이라고 한다.

예를들어 Excel의 data model은 (i,j)와 같이 좌표로 데이터를 가져올 수 있지만 Relational은 이처럼 위치로 주소를 정하지 않고 이름과 값을 기준으로 데이터의 주소를 정한다.

## SQL

### Creating Relations - DDL

``` sql
create table Students
  (sid: CHAR(20),
  name: CHAR(20),
  login: CHAR(10),
  age: INTEGER,
  gpa: REAL);
```

위와 같이 Students relation(Conceptional Schema)을 만들 수 있다. 이외로도 View(External schema), Index(Physical schema)를 만들 수도 있다.

### Modifying Relations - DML

``` sql
insert into students values(53688,'Smith','smith@ee', 18, 3.2);
delete from students s where s.name = 'Smith';
update students s set s.gpa = s.gpa - 0.1 where s.gpa >= 3.3
select * from students s where s.gpa >= 3.3 and s.age < 25
```

각각 순서대로 Tuple을 삽입, 삭제, 갱신, 검색하는 Query다.

## Integrity Constraints(ICs) - 무결성 제약조건

DBMS가 Domain, primary / foreign key constraint 등을 대신 지키게 해준다.

User가 정의한 Schema를 기반으로 데이터를 저장하거나 관리할 때 DBMS가 확인하게 된다.

### Primary Keys and Entity Integrity

- Primary keys
  - 각 튜플의 key는 서로 중복되면 안 된다.
  - 자동으로 해당 키에 대하여 index를 만든다.

``` sql
create table Enrolled
  (
    sid char(20),
    cid char(20),
    grade char(2)
    primary key (sid,cid)
  )
```

위와 같이 table을 만들때 지정 가능하다.
