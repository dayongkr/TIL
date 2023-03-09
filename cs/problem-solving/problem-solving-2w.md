# 문제해결 2주 차

## C언어 기초 개념 및 문법

### Scope Rule

정의된 변수가 어디서 직접 접근할 수 있는지를 나타내는 것을 scope라고 한다.

- Global Scope
  - 모든 함수 밖에서 정의된 변수들
  - 어디에서든 접근이 가능
  - function은 블록이 끝나기 전에도 호출할 수 있는데 이를 recursive call(재귀 호출)이라고 한다.
  - 보통 Data Segment에 저장
  - 0으로 항상 초기화
  - 더 많은 공간을 제공하기 때문에 큰 데이터를 저장하려면 Global Scope에 저장하는 게 안전하다.
- Local Scope
  - 함수 또는 블록 안에 정의된 변수들
  - 블록 안에서만 접근이 불가능
  - 보통 Stack에 저장
  - 0으로 초기화 되어 있지 않다. 다만 OS마다 정책이 다를 수 있으므로 달라질 수 있다.

C언어에서는 함수는 변수가 아니기 때문에 함수 안에 함수를 정의할 수 없다. 따라서 Local function 이런 건 없다.

### Array

C언어는 매우 유연한 언어이기 때문에 컴파일 과정에서는 문제가 없다가 런타임 과정에서 정해진 배열 인덱스 이상에 접근한다면 오류가 발생하기 때문에 조심해야 한다.

기본 배열은 Compile time에 크기가 정해지기 때문에 malloc을 사용해서 동적 할당 배열을 사용하게 된다. 하지만 시험에서는 일정한 크기를 정해줄 것이기 때문에 굳이 사용하지 않아도 된다.

``` c
int n;
scanf("%d",&n);
int arr[n];
int arr2[n+1]; // 이건 불가능
```

위와 같은 배열 선언을 Varying Length Arrays라고 하는데 C99지원한다. 다만 이 또한 이 강의에서는 사용하지 않는다. 참고로 Global scope에서는 사용하지 못한다.

### Functions

return value type을 void라고 선언해도 return은 사용할 수 있으나 뒤에 아무것도 붙이면 안 된다.

- parameter (매개변수)
  - 정의할 때 쓰는 것
- argument (인수)
  - 함수를 호출할 때 쓰는 것

이름과 어떠한 매개변수를 가지고 반환 값이 무엇인지 선언을 먼저 하고 나중에 구현해도 된다. 다만 이처럼 Declaration은 여러 번 해도 돼지만 Definition은 한 번만 해야 한다.

#### Call by Value & Call by Reference

- Call by Value
  - 인자의 값이 복사되어 매개변수로 전달된다.
- Call by Reference
  - 인자에 있는 변수 자체가 reference 형태로 전달된다.

C에서는 모든 전달 형태가 Call by Value이다. Pointers는 결국 주소의 값을 전달하므로 실질적으로 Call by Reference가 아니다.
