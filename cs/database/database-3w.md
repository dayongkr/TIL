# 데이터베이스개론 3주 차

## Integrity Constraints(ICs) - 무결성 제약조건

### Primary Keys and Entity Integrity

``` sql
create table Students (sid char(20), name char(20), primary key (sid));
```

Key는 field의 집합으로 분리된 튜플끼리 같은 값을 가질 수 없으며 field의 합으로 만든 것은 Super Key라고 한다.

이 Key 중 하나를 선택하여 선언하는데 이를 Primary Key라고 하며 나머지는 Candidate Key라고 한다. 그리고 Index가 Primary Key 기준으로 자동으로 만들어지게 된다.

### Foreign Keys & Referential Integrity

``` sql
create table Enrolled (sid char(20), cid char(20), grade char(2), primary key (sid,cid), foreign key (sid) references Students);
```

Foreign Key는 다른 Relation 튜플을 refer 하기 위해 사용하는 field의 집합이다. 따라서 다른 relation의 primary key와 일치해야만 한다.

Foreign key constraints를 다 지킨다면 referential integrity를 지킬 수 있고 dangling reference를 방지할 수 있다.

> dangling reference: 허상 참조

보통 FK는 다른 Relation의 PK를 참조하지만, 같은 Relation의 PK도 참조할 수 있다.

### Enforcing Referential Integrity

PK를 가지고 있는 parent table에서 삽입/삭제가 일어나면 Referential Integrity를 enforcing 하기 위해 4가지 방법으로 처리하게 된다.

- CASCADE: 참조하고 있는 tuples를 지운다.
- NO ACTION: 참조하고 있으면 삭제를 안 한다.
- SET NULL: FK 값을 NULL로 바꿈
  - PK는 NULL이 허용되지 않지만 FK는 가능
- SET DEFAULT: default PK로 바꿈 (oracle에서는 없음)

``` sql
create table Enrolled (... 생략, foreign key (sid) references Students on delete cascade on update set default)
```

위와 같이 테이블을 만들 때 정의한다.

### IC and Transactions

``` sql
Begin_TX
Select ..
Insert into EMP ..
Insert into DEPT ..
...
END_TX
```

예를 들어 Transaction 과정에서 Insert 문이 실행된다면 보통 Immediate 하게 Integrity Constraint를 체크하지만 `set constraint Foo deferred` 명령어를 치면 해당 constraint는 Deferred mode로 commit time에 체크하게 된다.

## Relational Query Languages: SQL

Structured Query Language의 줄임말

사용자는 무엇을 원하는지만 queries로 적으면 되고 optimizer가 똑같은 값이 나오는 여러 가지 경우 중 최선의 선택을 해준다.

### Join

``` sql
select S.name, E.cid from Students S, Enrolled E where S.sid = E.sid and E.grade="A";
```

Table 들을 결합해서 원하는 결과를 얻어내는 것이다. 위 query는 Enrolled의 table에서 grade가 A인 학생의 sid를 가져오고 그 sid와 일치하는 학생의 이름을 Students table에서 가져오는 일을 한다.

### Views

``` sql
create view HighScoreStudents(sid, gpa) as select S.sid, S.gpa from Students S WHERE S.gpa > 3.5
```

View는 relation이지만 정의만 저장되고 튜플은 저장되지 않는다. 따라서 virtual relation과 같다. RDBMS는 해당 뷰로 query가 들어오면 해당 relation에는 튜플이 없기 때문에 query를 수정하여 튜플이 있는 Base relation에서 튜플을 가져와 보여준다.

View를 활용한다면 Base Relation에서 보여주고 싶은 부분만 보여줄 수 있어 보안 측면에서 좋다. 또한 Join을 할 때 매번 Query를 작성하지 않고 View를 만들어서 더 효율적으로 사용할 수 있다.

만약에 View를 insert/delete/update 한다면 Base relation이 바뀌는데 만약에 여러 Base Relation을 사용하는 View는 위와 같은 updates이 불가능할 수도 있다.

### Destroying and Altering Relations

``` sql
drop table Students [RESTRICT | CASCADE]
alter table Students add column firstYear: integer
```

- Destroy
  - drop을 사용하면 schema와 instance 모두를 삭제
  - oracle에서 truncate를 사용하면 instance만 삭제
- Alter
  - alter을 사용하면 새로운 칼럼을 추가/삭제가 가능

## 실습

``` sql
set linesize 120
set pagesize 80
```

위와 같은 설정을 매번 하기 귀찮으면 admin folder에 있는 glogin file에 추가하면 된다.

``` sql
rollback;
```

commit을 하기 전 rollback을 치면 지금까지 했던 작업을 undo 할 수 있다.

``` sql
set autot on;
```

Auto trace를 키면 Execution Plan 부분이 있는데 해당 부분이 How라고 생각하면 된다.

### SELECT

``` sql
select ename, empno from emp order by ename;
```

order by {field name} 기준으로 정렬하는 query

``` sql
select * from emp where hiredate = to_date('23-01-1982','dd-mm-yyyy');
select * from emp where to_char(hiredate,'yyyy') = 1981;
select * from emp where to_char(hiredate,'mm') = 04;
select * from emp where hiredate > to_date('81/09/01','yy/mm/dd');


alter session set nls_date_format='dd-Mon-yyyy hh:mi:sspm';
alter session set nls_date_format='dd/Mon/yyyy'; 
```

Date type이라고 따로 data type이 있으므로 to_date, to_char 내장 함수로 date를 다뤄야 한다. 또한 아래와 같이 date의 포맷을 바꿀 수 있으니 참고하자.

### INSERT

``` sql
desc DEPT;
Insert ...
```

desc를 통해 Relation의 정의 내용들을 본 다음에 insert 문을 작성하면 편하다.

### CREATE TABLE

``` sql
create table hello (a int, b char(1),
  constraint hello_pk primary key(a),
  constraint hello_uk unique(b));

select index_name from user_indexes where table_name = 'HELLO'; -- 인덱스 확인
```

위와 같이 primary key 또는 field에 unique 설정을 하면 index가 자동으로 추가된다.

``` sql
create table ... , foreign key(d) references parent(a), ... );
```

위와 같이 foreign key를 설정할 수 있다. 다만 FK를 지정 후 parent table에서 해당 key를 삭제하면 참조 무결성 위반으로 삭제가 안되므로 먼저 참조한 튜플을 삭제해야한다. 다만 on delete cascade를 제약 조건에 추가하면 DBMS에서 자동으로 연관된 FK들을 삭제해준다.

### CREATE VIEW

``` sql
create view join_view
as select ename, dname 
from emp, dept where emp.deptno = dept.deptno;
```

Join을 수행한 view를 미리 만들어서 매번 Select 할 때마다 join 하는 과정을 없앨 수 있다.

생성할 때 `WITH CHECK OPTION` 을 추가하면 뷰에는 업데이트되지 않는 query를 막아주게 된다. 또한 위와 같은 Join View 같은 경우에는 업데이트를 허용하지 않는다.

``` sql
create materialized view ...
```

materialized view로 생성하면 base relation으로 가지 않고 별도로 실체화된 relation으로 간다는 차이가 있고 update가 되지 않는다.

avg, sum 등과 같은 연산이 들어가 있는 select 문이 반복된다면 이 view를 사용해서 최적화하자.
