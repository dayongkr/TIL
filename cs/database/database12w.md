# 데이터베이스개론 12주 차

## Opertor Evaluator

selection, projection, join등 relaton algebra의 연산자들을 SQL에서는 상황에 맞는 알고리즘을 선택하여 구현한다. 이를 담당하는 것이 operator evaluator이다.

### Query Evaluation

relational operators를 작동시키는 알고리즘은 아래 간단한 아이디어에서 확장된다.

- Indexing
- Iteration
  - scan all tuples
- Partitionaing
  - Sorting 과 Hasing을 사용하여 큰 데이터를 작은 데이터로 나눈다.

#### Accessing Paths

Accessing paths는 relation에서 tuple을 가져오는 방법을 말한다. 만약에 tree index에 matching tuple이 있다면, index를 사용하여 tuple을 가져올 수 있다. 만약에 index가 없다면, relation을 scan하여 tuple을 가져온다.

### Selection

Selection은 relation에서 특정 조건을 만족하는 tuple을 가져오는 연산이다. Selection은 아래와 같은 방법으로 구현할 수 있다.

1. No index, no sorted: full table scan
2. No index, sorted: binary search
3. B+ tree index
4. Hash index & equality (Range가 아니면 Hash index도 유용)

Index를 사용하는 것을 결정하는 것은 qualify tuples의 수와 clustering에 좌우된다. 이러한 정보는 Catalog에 저장되어 있는데 예측일 뿐 실제로는 실행해보아야 한다.

만약에 unclustered indexes라도 RID Sorting을 통해 성능향상을 기대할 수 있는데 RID Sorting은 같은 page에 있는 tuple들 기준으로 Sorting하여 각 page를 한 번만 읽어도 되게 한다.

#### General Selection: Two Approaches

multiple index에서 selection을 수행하는 방법은 아래와 같다.

1. most selective access path를 찾는다.
   1. most selective access path는 가장 적은 tuple을 가져오는 access path이다.
2. RID intersection을 수행한다.
   1. most selective access path를 사용하여 tuple을 가져온다.
   2. 다른 access path를 사용하여 tuple을 가져온다.
   3. 두 결과를 intersect한다.

### Projection

Projection은 relation에서 특정 attribute만 가져오는 연산이다. 다만 Projection은 distinct를 수행하기 때문에 중복된 tuple을 제거해야 한다. 이를 위해서는 아래와 같은 방법을 사용한다.

1. Sort-based
   1. relation을 sort한다.
2. Hash-based
   1. relation을 hash한다.
3. Index-based
   1. 해당 attribute에 대한 index를 사용한다.

### Join

One Join Column은 nested loops join으로 구현이 가능하다.

#### Nested Loops Join

방법은 총 4개이다.

1. Tuple-oriented Nested Loops join
   1. outer relation의 tuple을 하나씩 가져온다.
   2. inner relation을 scan하여 조건을 만족하는 tuple을 찾는다.
   3. 이렇게하면 outer relation의 tuple 수만큼 inner relation을 scan해야 한다.
2. Page-oriented Nested Loops join
   1. outer relation의 page를 하나씩 가져온다.
   2. inner relation을 scan하여 조건을 만족하는 tuple을 찾는다.
   3. 이렇게하면 outer relation의 page 수만큼 inner relation을 scan해야 한다.
3. Block-oriented Nested Loops join
   1. outer relation의 block을 하나씩 가져온다.
   2. block에 대한 Hash table을 만든다.
   3. inner relation을 scan하여 조건을 만족하는 tuple을 찾는다.
   4. Hash table을 만드는 과정에서 cpu cost가 발생한다.
4. Index-oriented Nested Loops join
   1. outer relation의 tuple을 하나씩 가져온다.
   2. inner relation의 index를 사용하여 조건을 만족하는 tuple을 찾는다.
   3. 이렇게하면 outer relation의 tuple 수만큼 inner relation을 scan해야 한다.
   4. 하지만 index를 사용하기 때문에 inner relation을 scan하는 비용이 줄어든다.

#### Join: Sort-merge, Hash

Sort-merge join과 Hash join은 아래와 같은 공통점이 있다.

- data가 scan되고 나서는 각 특정 memory 그리고 temporary tablespace에 저장된다
- 이후에는 memory와 temporary tablespace에 저장된 data를 사용하여 join을 수행한다.
- 이떄 partitioning을 사용하여 memory와 temporary tablespace에 저장된 data를 작은 data로 나눈다.
- 이를 통해 비교해야 하는 tuple의 수를 줄인다.
- Inequality join에는 사용할 수 없다.

Sort-merge join과 Hash join의 차이점은 아래와 같다.

- Sort-merge
  - range를 통해 partitioning을 수행한다.
  - Cost는 sort cost + merge cost 즉 M log M + N log N + (M + N)이다.
  - data skew에 덜 민감하고 결과가 정렬되어 있다.
- Hash
  - grouping을 통해 partitioning을 수행한다.
  - Cost는 hash cost + probe cost 즉 3(M + N)이다.
  - relation sizes가 다를수록 더 유리하고 partition 이후에는 각자 probing을 하기 때문에 data skew에 민감하지만 parallelism이 가능하다.

#### Grace Hash Join

Grace Hash Join은 두 relation을 hash function을 사용하여 partitioning한다. 이후에는 partition 별로 불러와서 한 relation의 partition을 hash table로 만들고 다른 relation과 비교한다.

## Parser & Optimizer

SQL query가 들어오면 parsing을 하는데 일일히 parsing하는 것을 hard라고 하고 parsing을 한 번만 하고 그 결과를 재사용하는 것을 soft라고 한다. 이렇게 parsing이 완료되면 query optimizer가 실행계획을 생성한다. 각 실행계획 별로 catalog manager를 통해 cost를 추정하여 가장 좋은 실행계획을 선택한다.

> Query Execution Plan은 각 operator 별로 algorithm을 선택한다.

### Optimizer

어떻게 cost를 추정할 것인가에 대한 방법은 아래와 같다.

- Rule-based
  - rule을 사용하여 cost를 추정한다.
  - 특정 rule을 사용하여 cost를 추정하기 때문에 실제로 실행해보지 않아도 된다.
- Cost-based
  - 추정된 cost를 사용하여 가장 좋은 실행계획을 선택한다.
  - Cost base는 80% 정도의 정확도를 가지고 있다.

join을 수행하게되면 생성되는 plan은 (2(n-1)!)/(n-1)!이다. 어마어마한 공간이 필요하다. 이를 줄이기 위해 아래와 같은 방법을 사용한다.

- Dynamic Programming
  - the principle of optimality를 사용하여 중복되는 계산을 줄인다.
- only left-deep plan

그래도 여전히 많은 계산이 필요하다.

### Statistics and Catalog

catalogs에 의해 relations, indexes의 statistics를 관리한다. 이는 users에 의해 주기적으로 업데이트되는데 왜냐하면 어차피 추정을 위한 것이기 때문에 약간의 오차가 있어도 된다. 차라리 update 되는 cost를 아끼는 것이다. 더 자세한 정보들은 histogram을 사용한다. histogram은 특정 attribute의 값들을 bucket으로 나누어서 저장한다. 이를 통해 특정 attribute의 분포를 알 수 있다.
