# 데이터베이스 7주 차

## Data Mining

큰 데이터베이스에서 사소하지 않고 잘 알려지지 않고 유용한 흥미로운 정보, 경향 또는 패턴들을 를 찾는 과정이다.

이는 시장 분석, 위험 분석, 사기 탐지등에 사용된다.

### Data Mining Techniques

- Co-occurrence & Association Rules
  - 모든 구매자들이 구매한 상품들의 조합을 찾는다.
  - 기저귀와 맥주를 같이 구매한 사람들의 비율을 계산한다.
- Sequential Patterns
  - 해리포터 책을 사고 나서 3주 뒤에 해리포터 영화를 보는 사람들의 비율을 계산한다.
- Classification
  - 고객의 정보를 통해 고객의 성향을 예측한다.

이러한 buisiness intelligence를 통해 더 나은 서비스를 제공할 수 있다.

### Frequent Itemsets

- Support
  - 특정한 조합이 발생한 횟수를 전체 트랜잭션의 수로 나눈 값 즉 비율이다.
  - Support(A) = (A가 발생한 횟수) / (전체 트랜잭션의 수)
  - minsup을 설정하고 이보다 작은 support를 가진 조합은 제외한다.

#### Frequent Itemsets: An Optimization

A-priori algorithm으로 최적화가 가능한데 이는 subset이 frequent itemset이 아니면 그 조합도 frequent itemset이 아니라는 것을 이용한다.

예를들어  {A, B, C, D}가 있는데 {A}, {B}, {C}만 frequent itemset이라면 다음 조합에서 {D}를 제외한 {A, B}, {A, C}, {B, C} itemset을 조사하고 만약에 {B, C}가 frequent itemset이 아니라면 {A, B, C}도 frequent itemset이 아니라는 것을 알 수 있어 조사도 안하고 넘어갈 수 있다.

#### Support vs Confidence

Support와 Confidence를 이용하여 Association Rule을 찾는다. Support는 조합이 발생한 횟수를 전체 트랜잭션의 수로 나눈 값이고 Confidence는 조합이 발생한 횟수를 조합의 첫번째 아이템이 발생한 횟수로 나눈 값이다.

- Support(A -> B) = A & B
- Confidence(A -> B) = A | B = Support(A -> B) / Support(A)

위와 같이 나타낼 수 있다.

### Practice

``` sql
create or replace type fi_num as table of number;
select cast(itemset as fi_num) itemset, support, length, total_tranx
from table(dbms_frequent_itemset.fi_transactional(
      cursor(select cust_id, prod_id
          from sales),
      (5000/7059),
      2,
      5,
      null,
      null)
);
```

위와 같이 itemset을 저장할 type을 만들고 dbms_frequent_itemset을 이용하여 frequent itemset을 찾는다. 첫 번째 인자는 cursor로 트랜잭션을 넘겨주고 두 번째 인자는 minsup, 세 번째 인자는 minlen, 네 번째 인자는 maxlen이다. 마지막 두 인자는 원래는 포함할 itemset과 제외할 itemset을 넘겨주는데 null로 넘겨주면 모든 itemset을 포함한다.

type을 string으로 바꾸고 싶으면 다음과 같이 하면 된다.

``` sql
create or replace type fi_str as table of varchar2(100);
```
