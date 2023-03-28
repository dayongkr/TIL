# 데이터베이스개론 5주 차

## Aggregate Operators

- COUNT
- SUM
- AVG
- MAX
- MIN

> 표준에 따르면 중복 aggregate operator를 사용할 수 없다.

``` sql
SELECT S.sname, S.age FROM Sailors S WHERE S.age > (SELECT MAX(S2.age) FROM Sailors S2);
```

위와 같은 쿼리로 S.sname, S.age를 출력하는데 S2.age가 가장 큰 tuple을 찾아서 S.age가 그보다 큰 tuple만 출력한다.

``` sql
SELECT S.sname, S.age FROM Sailors S WHERE S.age > ALL(SELECT S2.age FROM Sailors S2);
```

MAX를 사용하지 않고 ALL을 사용하여 위와 같은 쿼리를 작성할 수 있다.

### GROUP BY

``` sql
SELECT S.sname, S.age FROM Sailors S GROUP BY S.age;
```

위와 같은 쿼리로 S.sname, S.age를 출력하는데 S.age가 같은 tuple들을 그룹으로 묶어서 출력한다. 참고로 GROUP BY 뒤에는 grouping-list가 오므로 여러개의 attribute를 grouping할 수 있다.

여기서 S.age는 grouping attribute로 중복하지 않는다. sorting이 먼저 이루어지고 그 다음에 grouping이 이루어진다.

#### HAVING

``` sql
SELECT S.sname, S.age FROM Sailors S GROUP BY S.age HAVING S.age > 20;
```

위와 같은 쿼리로 S.sname, S.age를 출력하는데 S.age가 같은 tuple들을 그룹으로 묶어서 출력하는데 S.age가 20보다 큰 tuple만 출력한다.

> Group을 대상으로 조건을 걸어서 출력하는 것이다.

#### Example

``` sql
SELECT S.sname, MIN(S.age) FROM Sailors S GROUP BY S.rating HAVING COUNT(*) > 1;
```

위와 같은 쿼리로 S.rating이 같은 tuple들을 그룹으로 묶어서 출력하는데 그 그룹의 tuple의 개수가 1보다 큰 그룹만 출력한다.

## Practice

### like

``` sql
SELECT * FROM Sailors WHERE sname LIKE 'B%';
```

like를 사용하여 B로 시작하는 sname을 가진 tuple을 출력한다.

``` sql
SELECT * FROM Sailors WHERE sname LIKE '%B';
```

또는 like를 사용하여 B로 끝나는 sname을 가진 tuple을 출력할 수 있다.



``` sql
SELECT * FROM Sailors WHERE sname LIKE '_B';
```

_는 한 글자를 의미한다.

### subquery

만약에 runtiem에 two or more rows가 나오면 error가 발생한다. 이를 방지하기 위해서는 subquery를 사용하여 하나의 row만 나오도록 한다.

#### Multiple rows

``` sql
SELECT * FROM Sailors WHERE EXISTS(SELECT rating FROM Sailors WHERE sname = 'Bert');
```

위와 같은 쿼리로 Bert라는 sname을 가진 tuple이 존재하는지 확인할 수 있다.

``` sql
SELECT * FROM Sailors WHERE rating = ANY(SELECT rating FROM Sailors WHERE sname = 'Bert');
```

ANY를 사용하여 Bert라는 sname을 가진 tuple이 존재하는지 확인할 수 있다.

``` sql
SELECT * FROM Sailors WHERE age >= ALL(SELECT age FROM Sailors WHERE sname = 'Bert');
```

ALL을 사용하여 Bert라는 sname을 가진 사람들의 나이보다 같거나 많은 사람을 출력할 수 있다.

#### In From Clause

``` sql
SELECT * FROM Sailors S1, (SELECT * FROM Sailors WHERE sname = 'Bert') S2 WHERE S1.rating = S2.rating;
```

FROM Clause안에 subquery를 사용하여 Bert라는 sname을 가진 tuple의 rating과 같은 tuple을 출력할 수 있다.

### Group By

``` sql
SELECT rating, COUNT(*) FROM Sailors GROUP BY rating;
```

위와 같은 쿼리로 rating이 같은 tuple들을 그룹으로 묶고 그 그룹의 tuple의 개수를 출력할 수 있다.

``` sql
SELECT rating, SUM(age) FROM Sailors GROUP BY rating;
```

위와 같은 쿼리로 rating이 같은 tuple들을 그룹으로 묶고 그 그룹의 tuple의 나이의 합을 출력할 수 있다.

#### MAX

``` sql
SELECT rating, MAX(age) FROM Sailors;
```

위와 같이하면 error가 발생한다. 왜냐하면 MAX는 grouping attribute가 될 수 없기 때문이다.

``` sql
SELECT rating, MAX(age) FROM Sailors GROUP BY rating;
```

따라서 위와 같이 그룹을 지정해주어야 한다. 참고로 여기서 rating은 개별 field가 아니라 tuple을 의미한다.

``` sql
SELECT ename, MAX(salary) FROM Sailors GROUP BY rating;
```

위와 같이 하면 똑같이 error가 발생한다. ename은 개별 field이기 때문이다.

### Outer Join

``` sql
SELECT dname, max(sal) from emp e, dept d where e.deptno(*) = d.deptno group by dname;
```

(*)는 outer join을 의미한다. 따라서 만약에 dept에는 있지만 emp에는 없는 tuple이 있으면 그 tuple도 출력한다.
