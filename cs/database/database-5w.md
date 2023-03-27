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
