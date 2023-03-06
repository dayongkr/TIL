# 데이터베이스개론 2주 차

매우 간단한 SQL를 소개하고 있어서 일단 알고 있는 내용은 정리하지 않았다.

## 기타 명령어

``` sql
set lines 200;
```

한줄에 몇 글자 나타낼 것인지 알려주는 명령어

``` sql
set autotrace on; // autotrace 활성화
set autotrace off;// autotrace 비활성화
```

내부에서는 어떻게 작동하고 있는지 알려주는 autotrace를 끄고 키는 명령어이다.

## DDL

- 조건은 WHERE
- SQL애서는 대입이 필요 없으므로 = 가 등호를 뜻한다.

## Levels of Abstraction in a DBMS

- Conceptional Schema
  - Tables
    - desc emp; 결과물이 Conceptional Schema
- Pysical Schema
  - Index
    - create index emp_deptno on emp(deptno);
- External Schema or VIEW
  - create or repalce view dept_sal as select deptno, avg(sal) avg_sal from emp group by dpetno;
  - 데이터는 없지만 사용자는 마치 데이터가 있는 것처럼 쿼리를 사용해서 데이터를 얻을 수 있다.

## Logical data independence

Conceptional schema를 바꿔도 External schema는 영향을 받지 않는다. 되게 중요한 개념이다.

```sql
alter table emp rename to emp2;
select * from dept_sal; // 변경 사항이 없다.
```

## Transition

### ACID

- Atomicity
  - All or Nothing
- Concurrency Control
  - 다른 곳에서 사용하고 있는 부분은 Commit 전에는 Lock이 걸리기 때문에 수정 작업들을 못하게 된다.

이를 DBMS에서 알아서 처리해주므로 구현할 필요가 없어서 너무나 중요하고 좋은 기능이다.
