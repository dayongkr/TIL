# 자바 프로그래밍 실습 3주 차

## String

``` java
String str = "str";
String str = new String("str");
```

리터럴 방식은 Java heap Memory에 있는 String Pool에 저장되고 클래스 생성자 방식은 Java Heap의 새로운 object를 만들어 저장되게 된다.

String은 non-primitive type으로 참조하는 식으로 사용하고 불변성을 가진다.

### String Methods

- length()
  - 문자열 길이
- charAt(int index)
  - index 위치에 있는 문자를 반환
- substring(int begin, int end)
  - begin부터 end-1까지 잘라서 반환
  - end가 없으면 문자 끝까지 잘라서 반환
- concat(string s2)
  - s2를 문자열 뒤에 붙여서 반환
- equal(string s)
  - 문자열 값으로 비교해준다. (content comparison)
- split(string s)
  - s를 기준으로 문자열을 나누어 배열로 반환

### Type Casting

- String to Int
  - Integer.valueof(s1)
- String to Double
  - Double.valueof(s1)
- Int to String
  - Integer.toString(n)
- Double to String
  - Double.toString(n)

## 과제

3가지의 새로운 String Methods를 만들어야 했다.

- s1 문자열의 index 위치에 s2 문자열을 집어 넣기
  - substing으로 두 개로 찢은 다음 con at을 써서 s1 두 개와 s2를 이어 붙임
- s 문자열을 역순으로 정렬하기
  - s의 length 함수와 charAt 함수로 구현
- s1 문자열에서 s2 문자열 모두 지우기
  - s2를 기준으로 split 해서 나온 배열을 concat으로 다시 이어 붙임

위 방법으로 빠르게 구현했으나 jar 파일로 제출하라고 해서 혹시 몰라 Eclipse와 jdk 버전을 다시 설치 후 제출하다 보니 조금 늦어졌다.
