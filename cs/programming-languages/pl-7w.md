# 프로그래밍언어 7주 차

## Data Types

- data type: 객체의 집합을 정의한 것
- descriptor: 변수의 속성의 집합

### Primitive Data Types

- 거의 hardware와 비슷한 data type
- integer, real, boolean, character, complex, string, decimal
  - decimal: 자리수가 정해져 있는 실수
  - character: ascii 또는 unicode
  - string
    - primitive가 아닌 경우도 있다. (c, c++)
    - length(길이 제한)
      - static(COBOL, Java, Python), limited dynamic(C, C++), Dynamic(Javascript)
    - descriptor
      - compile time: length, type
      - runtime: current length, max length ...
  - ordinal type
  - 순서가 있는 type
  - enumeration type, subrange type
    - subrange type: 범위가 정해진 type
      - parent type을 가져오고 제약을 추가해서 구현한다.

### Type Compatibility

- 대부분 언어에서 연산은 자동으로 type conversion을 한다.
  - 대입도 자동으로 type conversion을 한다.
  - 보통 type conversion은 작은 type에서 큰 type으로만 가능하다.
- double x = m / n;
  - m, n이 정수 15, 16이라면 x는 0이 된다.
  - 따라서 m, n을 먼저 double로 바꿔줘야 한다.

### Array

- c는 정의할 때 크기를 정하고 java는 대입할 때 크기를 정한다.
- dope vector: 크기등과 같으 descriptor를 저장하는 array
- Java는 array를 object로 취급한다
- Indexing
  - Fortran 그리고 Ada는 parenthesis를 사용한다.
  - 나머지 대부분은 bracket을 사용한다.
  - C, C++, Perl, Fortran은 range checking을 하지 않는다.
  - Java, ML, C#은 range checking을 한다.
- Categories
  - Static array
    - compile time에 크기가 결정된다.
    - global(file) scope
    - C
  - Fixed stack-dynamic array
    - 크기는 compile time에 결정되지만 메모리는 runtime에 할당된다.
    - stack에 할당된다.
  - Stack-dynamic array
    - runtime에 크기가 결정된다.
    - stack에 할당된다.
    - arr[n]
  - Fixed heap-dynamic array
    - 크기는 compile time에 결정되지만 메모리는 runtime에 할당된다.
    - heap에 할당된다.
    - c에서 malloc을 사용할 때
  - Heap-dynamic array
    - 위와 동일한데 변수를 사용한다.
- Heterogeneous array
  - 동일한 타입이 아니라 여러 타입을 저장할 수 있다.
  - Perl, Python, Ruby, Javascript
