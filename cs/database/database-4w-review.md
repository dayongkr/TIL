# 데이터베이스개론 4주 차 Review

## Q&A

- 만약에 Cross product를 수행하면 되게 큰 테이블이 생성되어서 메모리 용량 문제가 발생하지 않을까?
  - 쿼리문을 작성할 때는 이런 걱정을 할 필요는 없지만 간단히 설명하자면 넘치게 되면 disk에 저장하게 된다.
- A/B를 수행할 때 만약에 B가 빈 테이블이라면 어떻게 될까?
  - 답은 A로 나온다.

## SQL

### Overview

- DML
  - what만 다루면 된다.
- DDL (Definition)
  - how를 다루는 부분
  - Logical: table/view/ ICs
  - Physical: index/partitions
- DCL (Control)
  - Trigger, Advanced ICs, Transaction Management, Security

Data mining, Recursive Queries, Machine Learning 등과 같은 부분도 Query로 표현할 수 있도록 많이 발전했다.

### SQL and Data Independence

- High-level language
- 값 기반 관계
- content-based 주소 시스템
- physical schema가 어떻게 되어있는지 상관하지 않는다

Data independence를 위해 위와 같이 RDBMS는 설계되었다.

### Basic SQL Query

``` sql
select [distinct] target-list from relation-list [as ailas] where qualification
```

> distinct (optional): 중복 제거

qualification(only true)을 통과한 relation-list의 tuple의 target-list field의 내용들만 보여주는 query이다.

select query의 특징으로는 아래와 같다.

- distinct를 사용하는 데에도 많은 연산이 필요하므로 기본적(multi-set)으로는 중복을 허용해준다.
- Relation 뒤에 as와 별명을 붙여주면 해당 query에서 relation의 별칭을 정해줄 수 있다.
- relation-list를 cross-product 연산을 수행한다.
- 연산 과정에서 불필요한 field를 날림으로써 optimization을 수행한다.

#### Expressions and Strings

``` sql
select S.age, age1=S.age-5, 2*S.age as age2 from Sailors S where S.sname LIKE 'B_%B'
```

arithmetic expressions과 string pattern을 query안에 구현을 할 수 있다. 위 query는 2개의 필드를 정의하는데 값은 expression 그대로 들어가게 된다. 뒤에 where에 있는 string pattern은 B로 시작하고 끝나고 최소 3개의 문자를 포함하는 sname을 구하는 부분이다.

REGEXP_LIKE 함수를 사용해서 정규식(Regular Expression)도 사용이 가능하다.

### Union, Intersect, Except

- UNION, UNION ALL (합집합)
  - UNION은 set semantic이기 때문에 중복을 허용하고 싶으면 UNION ALL을 사용하면 된다.
  - OR Logic operand를 사용한 query과 똑같은 역할을 하는 query을 만들 수 있지만 UNION을 사용하면 query 2개를 처리해야 하므로 수행시간이 다를 수 있다. 다만 RDBMS에서 알아서 Optimization을 수행해서 같을 수도 있다.
- INTERSECT (교집합)
  - 얘는 AND와 비슷한 결과를 반환한다.

사용하는 방법은 두 query 사이에 해당 operand를 넣어주면 된다.

### Nested Queries(or Subqueries)

IN, ANY, ALL, EXISTS를 사용해서도 위와 같은 연산을 수행할 수 있다.

``` sql
select S.sname from Sailors S where S.sid in (select R.sid from Reserves R where R.bid = 103)
```

- IN
  - 포함하고 있는지
  - 값과 비교
- EXISTS
  - 존재하는지(IN과 유사)
  - tuple과 비교
