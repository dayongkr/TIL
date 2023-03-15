# 데이터베이스 3주 차 REVIEW

## Q & A

- view도 update(insert/delete/update)가 가능은 하다고 나오는데 정확히 가능하다는 것이 어떤 것을 의미하고, 특정한 경우에는 아예 update가 불가능하다고 나오는데 그러한 경우가 어떤 경우인지 구체적으로 궁금합니다!
  - join, aggregation이 들어간 view는 updates가 불가능
- 세션 2개가 존재하는데 한쪽에서 update하고 commit을 안 했을 때 다른 세션에서는 어떻게 보여줘야할까?
  - 다른 세션에서 update하고 commit 하지 않으면 update 하기 전 값을 보여주게 된다. (multi versioning을 지원)
- set constraint에서 deffered 를 사용하게 되는 상황?
  - 정확한 상황이 없지만 만약에 query 순서 때문에 constraint에 제약받을 경우를 위해 옵션 존재
- unique key도 index를 만드는 이유?
  - index를 만들어야 unique 함을 체크하기 더 효율적이다.
- relational model 이전에는 어떤 방식으로 데이터를 관리/사용?
  - 계층, 그래프 모델을 사용해서 표현
  - query language가 없을 때는 program language를 이용해서 직접 접근
- 오라클이 비교적 쇠퇴한 이유는?
  - 여전히 중요한 분야에서는 시장 지배적

## ch4. relational algebra

### Relational Database Language: Genealogy

SQL 자체로는 relational calculus 기반이고 SQL implementation은 relational algebra 기반이다.

- Relational Algebra
  - 절차적
- Relational Calculus
  - 선언적

따라서 무엇을 원하는지 적는 SQL에서는 Relation Calculus 기반으로 되어 있는 것이다.

### Algebra

- Operands: relation or variables
- Operators: relation으로 처리할 절차를 표현하는 symbol
- Axioms
  - Commutativeness R x S = S x R
  - Associativeness (R x S) x T = R x (S x T)
  - Distributiveness R x (S U T) = (R x S) U (R x T)

linear algebra는 항상 relation으로 나오기 때문에 closeness 하다고 볼 수 있다.

### Relational Algebra

- Selection (б)
  - selects a subset of rows
  - e.g. б rating > 8(S2)
  - 중복에 대한 이슈는 없다. (어차피 set)
- Projection (π)
  - delete unwanted columns
  - e.g. π age(S2)
  - 중복된 것들은 제거해준다.
- Cross-product(X)
  - 두 relation 결합
- Set-difference(–)
  - R1 - R2: R1에 있지만 R2에 없는 것
- Union(U)
  - Tuples in either R1 and R2
