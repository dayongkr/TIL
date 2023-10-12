# 프로그래밍언어 6주 차

## Scope

변수가 유효한 범위를 의미한다.

- local scope
  - 선언된 단위 내에서만 유효하다.
- non-local scope
  - 선언되지 않은 단위에서도 유효하다.
- global scope
  - 프로그램 전체에서 유효하다.

### Static Scope (Lexical Scope)

- 프로그램 코드를 작성하는 시점에 결정된다.
- 주어진 이름이 나올 떄까지 scope을 넓혀가며 찾는다.
- 종종 nested function을 지원한다.
- hierarchy
  - global scope
    - python은 function 안에서 global 변수를 사용할 수 있다.
  - class scope
    - class member는 class 전체에서 유효하다.
  - method scope
    - java에서는 method name과 local name이 같아도 된다.
      - 단 localname끼리는 다르다.
    - method body
  - code block scope
- multiple files
  - c에서 extern을 사용하면 정의만 하고 선언은 다른 파일에서 할 수 있다.
  - static을 사용하면 다른 파일에서 사용할 수 없다.
    - 따라서 symbol table에 여러 개의 static 변수가 들어갈 수 있다.
  - static이 아닌 변수가 이름이 같으면 link error가 발생한다.
- scope hole
  - 변수가 선언되지 않은 scope는 밖에서 선언된 변수를 사용한다.

### Dynamic Scope

- 프로그램이 실행되는 시점에 결정된다.
- 예를들어 Perl은 dynamic scope를 지원한다.
- local keyword를 사용하면 잠시 copy를 만들어서 사용한다.

### limit name collision

- limit scope of variables
- nested function
- moudles
  - 명시적으로 export할 수 있다.
- namespace
  - java에서는 package를 사용한다.
  - name을 encapsulate한다.

## Lifetime

scope랑 경계가 애매한데 lifetime은 변수가 메모리에 존재하는 기간을 의미한다.

## etc

- constant
  - 컴파일 시간에 값을 알 수 있는 변수를 의미한다. 하지만 간혹 elaboration time에 값을 알 수 있는 경우도 있다.
    - elaboration time: 컴파일 시간과 실행 시간 사이의 시간
- Declariation order
  - c, c++는 선언부터 블럭의 끝까지 사용할 수 있다.
  - c#은 선언한 블럭 전체에서 사용할 수 있다.
- Referencing Environment
  - 현재 scope에서 사용할 수 있는 변수들의 집합
