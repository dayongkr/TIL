# 데이터베이스개론 6주 차

## Advanced SQl Features

### Deductive Logics(Tree traversal)

Tree/Graph data가 유행하면서 RDBMS도 이에 맞게 확장해서 사용하고 있다. 이를 위해서는 Tree traversal이 필요하다.

self-join으로 hierarchy를 구현 가능하지만 별도로 Hierarchical queries를 지원하기 때문에 이를 사용하는 것이 좋다.

기존 존재하던 relation을 이용해서 tree를 구현하는 것이기 때문에 Deductive DB이라고 한다.

#### Hierarchical Queries

```sql
SELECT [LEVEL], column, expr...
FROM table
[WHERE condition]
[START WITH condition]
[CONNECT BY PRIOR condition]
```

- LEVEL: 현재 노드의 level을 나타낸다.
- START WITH: condition에 해당하는 tuple을 root node를 지정한다.
- CONNECT BY PRIOR: parent node를 지정한다.

``` sql
SELECT empno, ename, job, mgr
FROM emp
START WITH empno = 7698
CONNECT BY PRIOR mgr = empno
```

``` sql
SELECT empno, ename, job, mgr
FROM emp
START WITH empno = 7698
CONNECT BY empno = PRIOR mgr
```

위 두 쿼리는 bottom-up으로 tree를 탐색한다. empno 7698이 root node이고 해당  emp의 mgr 값이 empno인 node가 parent node이다.

#### Print Tree

Level과 Lpad를 이용해서 tree를 출력할 수 있다.

``` sql
SELECT LPAD(' ', 3 * LEVEL - 3) || ename, LEVEL, empno
FROM emp
START WITH mgr IS NULL
CONNECT BY PRIOR empno = mgr
```

LPAD는 내장 함수로 문자열을 왼쪽으로 채워주는 함수이다.

#### Eliminate a branch

``` sql
SELECT empno, ename, job, mgr
FROM emp
WHERE ename != 'SCOTT'
START WITH ename = 'JONES'
CONNECT BY PRIOR empno = mgr
```

위 SQL은 ename이 'SCOTT'인 node만 제거하는 것이 아니라 해당 node의 하위 node도 모두 제거한다.

#### Recursion in SQL 2000

``` sql
WITH RECURSIVE ancestor(id, ancestor_id) AS (
  SELECT id, ancestor_id
  FROM parent
  UNION ALL
  SELECT p.id, e.ancestor_id
  FROM parent p, ancestor a
  WHERE p.id = a.ancestor_id
)

SELECT * FROM ancestor
```

위 SQL은 ancestor table을 만들어서 recursive하게 parent table을 참조하는 것이다. 위는 표준이다.

### Data Cube

Group by와 달리 multi-level aggregation을 지원한다.

``` sql
SELECT model, year, color, sum(amount)
FROM sales
GROUP BY CUBE(model, year, color)
```

위 SQL은 model, year, color에 대한 multi-level aggregation을 수행한다.

``` raw
+--------+------+-------+----------+
| model  | year | color | sum      |
+--------+------+-------+----------+
|        |      |       |  1000000 |
|        |      | red   |   200000 |
|        |      | blue  |   300000 |
|        |      | green |   400000 |
|        | 2000 |       |    50000 |
|        | 2000 | red   |    10000 |
|        | 2000 | blue  |    15000 |
|        | 2000 | green |    20000 |
|        | 2001 |       |    50000 |
|        | 2001 | red   |    10000 |
|        | 2001 | blue  |    15000 |
|        | 2001 | green |    20000 |
|cube    |      |       |  1000000 |
|cube    |      | red   |   200000 |
|cube    |      | blue  |   300000 |
|cube    |      | green |   400000 |
...
```

data cube는 multi-level aggregation을 지원하기 때문에 group by보다 더 많은 정보를 얻을 수 있다.

결과가 위처럼 비어있으면 null인지 all인지 구분할 수 없기 때문에 grouping 함수를 사용한다.

``` sql
SELECT model, color, sum(amount), grouping(model) as T1
FROM sales
GROUP BY CUBE(model, color)
```

``` raw
+--------+-------+----------+------+
| model  | color | sum      | T1   |
+--------+-------+----------+------+
|        |       |  1000000 |    1|
|        | red   |   200000 |    1|
|        | blue  |   300000 |    1|
|        | green |   400000 |    1|
|cube    |       |  1000000 |    0|
|cube    | red   |   200000 |    0|
...
```

아니면 decode와 grouping를 사용해서 구분할 수 있다.

``` sql
SELECT decode(grouping(model), 0, to_char(model), 'ALL') as model, color, sum(amount)
FROM sales
GROUP BY CUBE(model, color)
```

``` raw
+--------+-------+----------+
| model  | color | sum      |
+--------+-------+----------+
| ALL    |       |  1000000 |
| ALL    | red   |   200000 |
| ALL    | blue  |   300000 |
| ALL    | green |   400000 |
|cube    |       |  1000000 |
...
```

#### Rollup

``` sql
SELECT model, year, color, sum(amount)
FROM sales
GROUP BY ROLLUP(model, color)
```

Rollup은 data cube와 비슷하지만, data cube는 모든 level의 aggregation을 수행하지만 rollup은 최상위 level만 aggregation을 수행한다.

### Pivot

pivot은 column을 row로 바꾸는 것이고 unpivot은 그 반대이다.

``` sql
SELECT * FROM (SalesTable PIVOT (Sales for Month IN ('JAN','Feb','Mar')))
SELECT * FROM (SalesReport UNPIVOT (Sales for Month IN ('JAN','Feb','Mar')))
```

``` raw
+--------+--------+--------+
| Year   | Month  | Sales  |
+--------+--------+--------+
| 2000   | JAN    | 100    |
| 2000   | FEB    | 200    |
| 2001   | JAN    | 300    |
| 2001   | FEB    | 400    |
| 2001   | MAR    | 500    |
+--------+--------+--------+

// pivot

+--------+--------+--------+--------+
| Year   | JAN    | FEB    | MAR    |
+--------+--------+--------+--------+
| 2000   | 100    | 200    | NULL   |
| 2001   | 300    | 400    | 500    |
+--------+--------+--------+--------+
```
