# 데이터베이스개론 5주 차 2

## null

값이 없는 tuple을 null이라고 한다. null은 값이 없는 것이기 때문에 비교 연산자를 사용할 수 없다.

``` sql
SELECT * FROM Sailors WHERE sname IS NULL;
```

따라서 IS NULL, IS NOT NULL을 사용하여 null이거나 아닌 tuple을 찾을 수 있다.

``` sql
SELECT * FROM Sailors WHERE age > 8;
```

만약에 age가 NULL일 때를 고려하기 위해 Unknown이 logic에 포함되어 오류가 발생하지 않는다.

``` sql
SELECT COUNT(*) FROM Sailors WHERE age > 8;
```

COUNT(*)는 예외적으로 null을 포함하여 계산한다. 나머지 aggregate operations는 null을 포함하지 않는다.

``` sql
CREATE TABLE Sailors (
    sid INTEGER NOT NULL,
    sname VARCHAR(20) NOT NULL,
    rating INTEGER NOT NULL,
    age INTEGER
);
```

NOT NULL을 사용하여 null이 아닌 값만 저장할 수 있다.

PK는 암시적으로 NOT NULL이다. 다만UNIQUE는 암시적으로 NOT NULL이 아니다.

### IN VS EXISTS

일반적으론 IN과 EXISTS는 비슷한 역할을 한다. 하지만 EXISTS는 subquery의 결과가 null이 아닌지를 확인한다.

## Integrity Constraints

``` sql
CREATE TABLE Sailors (
    sid INTEGER NOT NULL,
    sname VARCHAR(20) NOT NULL,
    rating INTEGER NOT NULL,
    age INTEGER,
    CONSTRAINT sailors_rating ...
);
```

Constraints는 이름을 지정할 수 있다. 이름을 지정하지 않으면 자동으로 이름이 지정된다.

### General

``` sql
CREATE TABLE Sailors (
    sid INTEGER NOT NULL,
    sname VARCHAR(20) NOT NULL,
    rating INTEGER NOT NULL,
    age INTEGER,
    CHECK (rating >= 0 AND rating <= 10)
);
```

CHECK를 사용하여 특정 조건을 만족하는 tuple만 저장할 수 있다. 이를 통해 좀 더 자세한 조건을 만족하는 tuple만 저장할 수 있다.

``` sql
CREATE TABLE  Reservesc(
  sname  CHAR(10),
  bid  INTEGER,
  day  DATE,
  PRIMARY KEY  (bid,day),
  CONSTRAINT  noInterlakeRes
  CHECK ('Interlake' <> (
      SELECT  B.bname
      FROM  Boats B
      WHERE  B.bid=bid)))
```

위와 같이 subquery를 사용하여 특정 조건을 만족하는 tuple만 저장할 수 있다.

> <>는 NOT EQUAL이다.

#### Assertion

``` sql
CREATE ASSERTION sailors_rating CHECK (rating >= 0 AND rating <= 10);
```

위와 같이 Assertion을 만들면 모든 Relational Schema에 적용된다.

### Trigger

Trigger는 특정 조건이 만족되었을 때 자동으로 실행되는 procedure이다. Trigger는 Assertion 보다 더 자세한 조건을 만족하는 tuple만 저장할 수 있다.

``` sql
CREATE TRIGGER sailors_rating
    BEFORE INSERT OR UPDATE ON Sailors // Event
    FOR EACH ROW
    WHEN (NEW.rating < 0 OR NEW.rating > 10) // Condition
    BEGIN // Action
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Rating must be between 0 and 10'; 
    END;
```

위와 같이 ECA Rule이라고 불리는 Event-Condition-Action Rule을 사용하여 Trigger를 만들 수 있다.
