# 프로그래밍언어 12주 차

## Subprograms2

### Parameters

- Multidimensional arrays
  - C, C++: 2차원 배열을 함수의 인자로 전달할 때, 2차원 배열의 크기를 명시해야 한다.
    - `void f(int a[][10])`
    - 또는 pointer를 사용한다.
      - `void f(int *a, int n, int m)`
      - `a[i][j]`는 `*(a + i * m + j)`로 표현할 수 있다.
    - 2차원 배열의 크기를 명시하지 않고 전달하는 방법은 없다.
- Subprogram 전달
  - C, C++: 함수를 인자로 전달할 수 없다.
    - 함수 포인터를 사용한다.
      - `void f(int (*g)(int))`
      - `g`는 `int`를 인자로 받아 `int`를 반환하는 함수를 가리키는 포인터이다.
      - `(*g)(3)`은 `g`가 가리키는 함수에 `3`을 인자로 전달한 결과이다.
      - 이 방식은 indirectly call이라고 한다.
  - Python
    - 함수를 인자로 전달할 수 있다.
      - 단순히 함수를 인자로 전달하면 된다.
      - python은 deep binding으로 정의된 환경 기준으로 변수를 찾는다
        - shallow binding은 함수가 호출된 환경 기준으로 변수를 찾는다
        - ad hoc binding은 함수가 인자로 전달된 환경 기준으로 변수를 찾는다

### Overloading

- C, C++: return type이 다르면 overloading이 가능하다.
  - `void sum(int a, int b)`
  - `int sum(int a, int b)`

### Generic Subprograms

- 제네릭이란 타입에 독립적인 코드를 작성하는 것을 말한다.
- 자바에서는 extends를 사용하여 bound가 있는 제네릭을 사용할 수 있다.
  - `public class Generic<T extends Comparable<T>>`
- 또는 wildcard type을 사용할 수 있다
  - `public class Generic<T extends Comparable<?>>`

### Design Issues for Functions

- side effects를 허락할지?
- 어떤 타입의 반환값을 허락할지?
  - C는 array, 함수를 제외하고는 모든 타입을 반환할 수 있다.
  - Java 그리고 C#은 모든 타입을 반환할 수 있다.
  - Python 그리고 Ruby는 method를 first-class object로 취급하기 때문에 모든 타입을 반환할 수 있다.
  - Lua는 모든 타입을 반환할 수 있다.

### User-Defined Overloaded Operators

- C++, Ada, Python, Ruby는 operator의 overloading을 허락한다.
  - C++는 `operator` 키워드를 사용한다.
  - Python은 `__add__`와 같은 형태로 사용한다.

### Closure

- 함수를 반환했을 때 그 함수가 정의된 환경을 기억하는 것을 말한다.
- Pyhton은 closure를 지원한다.
