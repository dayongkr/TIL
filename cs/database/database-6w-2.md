# 데이터베이스개론 6주 2 차시

## Analytic Functions

간단한 분석은 집계함수를 사용하면 되지만, 복잡한 분석은 집계함수로는 처리하기 어렵다. 이럴 때 사용하는 것이 Window Query이다.

이를 사용하면 성능, 생산성, 표준화된 문법에서 이득을 볼 수 있다.

### Families of Window Functions

- Ranking Functions
- Window Aggregation Functions
- LAG/LEAD Functions
- Reporting Aggregation Functions
- Statistical Functions
- 그 외 다양한 함수들이 있다.

### Key Concepts

- Second-Pass Grouping
  - 이미 앞에서 집계를 한 상태에서, PARTITION BY로 또 다시 집계를 해가지고 Second-Pass Grouping이라고 한다.
- Partitioning
  - PARTITION BY로 나누는 것을 Partitioning이라고 한다.
- Ordering
  - PARTITION BY로 나눈 후, ORDER BY로 정렬하는 것을 Ordering이라고 한다.
- Window
  - PARTITION BY로 나눈 후, ORDER BY로 정렬한 것을 Window라고 한다.

### Basic Syntax

```sql
<FUNCTION> (<argument>) OVER (<analytic clauses>)
```

- <FUNCTION> : Window Function
- <analytic clauses> : Partitioning, Ordering, Windowing

### Ranking Functions

#### Ranking Functions - ORDER BY

```sql
SELECT EMPNO, ENAME, SAL, 
RANK() OVER( ORDER BY SAL DESC) AS RANK
FROM   EMP
```

위 SQL은 Ranking을 하는데 SAL을 기준으로 내림차순으로 정렬하고 해당 Field의 이름을 RANK라고 정한다는 것을 의미한다.

#### Ranking Functions - PARTITION BY

```sql
SELECT EMPNO, ENAME, SAL,
RANK() OVER(PARTITION BY DEPTNO ORDER BY SAL DESC) AS DEPT_RANK
FROM   EMP
ORDER BY DEPTNO;
```

위 SQL은 Ranking을 하는데 DEPTNO를 기준으로 Partition을 나눈 후, SAL을 기준으로 내림차순으로 Partition 끼리 정렬하고 해당 Field의 이름을 DEPT_RANK라고 정한다는 것을 의미한다. 또한 마지막에 DEPTNO를 기준으로 정렬한다.

> WHERE 절에서는 사용할 수 없다. 따라서 Top-N과 같은 일을 수행하려면 FROM에 Subquery로써 사용해야 한다.

#### Tie Value

RANK는 동점자를 같은 수로 처리하기 때문에 동점자 처리를 위해 사용한다.

#### Row Number

```sql
SELECT EMPNO, ENAME, SAL, ROWNUM, 
ROW_NUMBER() OVER(ORDER BY SAL DESC) AS ROW_NUMBER
FROM   EMP
ORDER BY ENAME;
```

ROWNUM은 행의 순서를 나타내는 숫자를 반환한다. ROWNUM은 ORDER BY를 사용하지 않으면 순서대로 반환한다. 참고로 final ORDER BY는 ROWNUM에 영향을 주지 않는다.

ROW_NUMBER()은 RANK()와 같이 순위를 매긴다. 하지만 RANK()는 동점자가 있을 경우 동점자들의 순위가 같다. 하지만 ROW_NUMBER()는 동점자가 있을 경우 동점자들의 순위가 다르다.

> Sort를 할 때 NULL을 highest value로 취급하기 때문에 ORDER BY 뒤에 NULLS LAST를 붙이면 NULL이 가장 뒤에 오게 된다.

### Aggregates

```sql
SELECT DEPTNO, AVG(SAL),
RANK() OVER(ORDER BY AVG(SAL) DESC) AS DEPT_RANK
FROM   EMP
GROUP BY DEPTNO
```

위 SQL은 DEPTNO으로 그룹핑을 하고 그룹핑된 결과를 기준으로 AVG(SAL)을 내림차순으로 정렬하고 해당 Field의 이름을 DEPT_RANK라고 정한다는 것을 의미한다.

처리되는 순서가 중요하다!

#### Aggregates as Analytic Functions

```sql
SELECT EMPNO, ENAME, SAL,
ROUND( AVG(SAL) OVER() ) AS AVGSAL,
SAL - ROUND( AVG(SAL) OVER() ) AS DIFF
FROM   EMP
```

OVER 안에 아무것도 없으면 전체를 대상으로 한다.

#### Ntiles

```sql
SELECT  EMPNO, ENAME, SAL,
NTILE(2) OVER(ORDER BY SAL DESC)  AS NTILE2,
NTILE(4) OVER(ORDER BY SAL DESC)  AS NTILE4,
NTILE(10) OVER(ORDER BY SAL DESC) AS NTILE10
FROM   EMP;
```

N 등분을 했을 때 몇 번째 등분에 위치하는지 알려주는 함수이다.

### Window Functions

timing window 및 sliding window로 현재 시점을 기준으로 여러개의 rows를 다루는 것이다. sliding window는 정렬되었어야 의미가 있으니 ORDER BY가 필요하다.

> 하나의 partition내에서 window를 사용할 수 있다.

```sql
SELECT EMPNO, ENAME, SAL, SUM(SAL) OVER(ORDER BY EMPNO
ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)
AS ACC_SAL
FROM   EMP
```

ROWS ~ ROW까지가 windowing을 정의하는 부분이다. UNBOUNDED PRECEDING은 처음부터, CURRENT ROW는 현재 행까지를 의미한다. 즉 처음부터 현재 행까지의 합을 구하는 쿼리이다.

```sql
SELECT EMPNO, ENAME, SAL, SUM(SAL) OVER( ORDER BY EMPNO
ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING ) ACC_SAL
FROM   EMP
```

위 쿼리는 앞 뒤 1개의 행을 포함하여 합을 구하는 쿼리이다.

#### RANGE

```sql
SELECT EMPNO, ENAME, SAL,SUM(SAL) OVER(ORDER BY EMPNO
RANGE BETWEEN 100 PRECEDING AND 200 FOLLOWING)
AS ACC_SAL
FROM   EMP
```

RANGE를 사용하면 Column의 값에 기반하여 window를 정의할 수 있다. 따라서 위 쿼리는 현재 행의 SAL에서 100 이전의 행의 SAL과 200 이후의 행의 SAL의 총합을 구하는 쿼리이다.

#### DEFAULTS

```sql
SELECT EMPNO, ENAME, SAL, SUM(SAL) OVER(ORDER BY SAL) FROM EMP;
```

위 쿼리는 DEFAULTS sliding window를 수행하여 `RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`을 수행한 것과 같다.

#### Time Interval

```sql
SELECT EMPNO, ENAME, HIREDATE, SAL, ROUND( AVG(SAL) OVER(ORDER BY HIREDATE
RANGE BETWEEN INTERVAL '6' MONTH PRECEDING
AND  INTERVAL '6' MONTH FOLLOWING) ) AS MOV_AVG
FROM   EMP;
```

위 쿼리는 HIREDATE를 기준으로 6개월 전과 6개월 후의 SAL의 평균을 구하는 쿼리이다.

### Additional Functions

- RATIO_TO_REPORT
  - 비율을 구하는 함수이다.
- FIRST_VALUE
  - windowing을 사용할 때 첫번째 값을 구하는 함수이다.
- LAST_VALUE
  - windowing을 사용할 때 마지막 값을 구하는 함수이다.
- LAG
  - windowing을 사용할 때 이전 행의 값을 구하는 함수이다.
  - 뒤에 값을 넣으면 그만큼 뒤의 행을 구할 수 있다.
  - LAG(SAL,1,0)으로 하면 NULL 값을 0으로 처리할 수 있다.
- LEAD
  - windowing을 사용할 때 다음 행의 값을 구하는 함수이다.
  - 뒤에 값을 넣으면 그만큼 뒤의 행을 구할 수 있다.
  - LAG(SAL,1,0)으로 하면 NULL 값을 0으로 처리할 수 있다.
