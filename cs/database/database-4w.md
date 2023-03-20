# 데이터베이스개론 4주 차

## Relational Algebra

### Cross-Product or Cartesian Product

R1 X S1은 R1과 S1 relation의 Cross-Product 연산을 의미한다. Cross-Product는 두 개의 Relation을 합친 Relation을 만드는데 합치는 방법은 각 relation의 tuple 한 개씩 서로 더 하는 방식이다.

겹치는 field를 따로 처리하지 않고 둘 다 추가해서 relation을 만들다 보니 renaming operater(ρ) 를 사용해서 field의 이름을 바꿔서 사용해야 한다.

### SQL vs Relation Algebra

SELECT는 Projection, FROM은 Cross-Product, WHERE는 Selection이라고 보면 된다.

### Joins

Cross-Product 해서 나온 relation에서 조건을 추가하고 싶을 때 보통 사용한다.

#### Condition Join or Theta-join

R ⋈ condition S라고 표현하며 이는 σ condition (RxS)와 같다.

예를들어 S1 ⋈ S1.sid < R1.sid R1은 S1과 R1을 Cross-product 수행하고 나온 relation 중에 S1.sid가 R1.sid 보다 작은 조건을 만족하는 tuple을 보여달라는 의미이다.

#### Equi-Join

R ⋈ field S라고 표현하며 오직 equalities를 확인하는 Join이다. 따라서 S1 ⋈ sid R1은 S1과 R1을 Cross-product 수행하고 나온 Relation의 tuple 중 S1.sid = R1.sid 조건을 만족하는 tuple을 보여달라는 의미이다.

#### Natural Join

S1 ⋈ R1이라고 표현하며 all common fields를 기반으로 Equi-join을 수행한 것과 같은 결과가 나온다.

### Set vs Bag Semantics

Relational Algebra는 Set이지만 SQL은 Multi-set(or bag) semantics를 기본으로 사용한다.

### Division

(R X S) / S = R에서 /가 division이다. 예를 들어 x, y와 같은 2개의 field를 가진 A relation과 y field를 가진 B relation을 division 연산(A/B)을 수행하면 B의 모든 field의 value를 만족하는 y를 제외한 모든 field를 포함한 A의 tuple을 반환한다.

> 되게 말로 표현하면 장황해서 이해하기 어려울 수 있으니 ch 4. relational algebra 교안의 Examples of Division A/B 부분의 사진을 참고하면 이해가 빠를 수 있다.

어쨋든 join과 같은 기본 연산자를 사용해서 표현할 수 있기 때문에 꼭 필요한 operator가 아니다. 예를 들어 πx(A) - all disqualified tuples로 A/B를 나타낼 수 있다. disqualified tuples는 πx((πx(A) x B) - A)로 구할 수 있다.

### Algebra Example

나와 있는 schema을 직접 다 옮기기 어렵기 때문에 정리는 넘겼다. 따라서 p.29에 가서 직접 연습해보자.

join을 수행하기 전 π을 사용해서 불필요한 field를 제거한다면 더 효율적으로 join을 수행할 수 있다.

> ⌵는 OR logic을 말하고 ^는 and logic을 말한다.

## 실습

- union
  - 두 개이상의 SQL 쿼리문을 합치는 연산자로 중복은 제거한다.
  - 다만 union all은 중복을 허용한다.
- select * from emp, dept;
  - Cross product를 수행하는 쿼리문이다.
  - 여기서 Where 문을 사용하면 Join을 수행할 수 있다.
- select * from emp natural join dept;
  - 와 같이 명시적으로 natural join을 수행할 수 있다.
- select * from R divide by S
  - R/S 연산을 수행하는 쿼리문
