# 문제해결 1주 차 2차시

C언어에 대한 5가지를 배우게 된다.

1. Variables, Operators and Control Flow
2. Arrays and Functions
3. IO, Strings, and Structures
4. Pointers
5. Dynamic Memory Allocation and Miscellaneous Topics

## 컴퓨터 구조 개요

다른 수업과 많은 부분 겹쳐서 몇 개만 정리해보겠다.

- 용량 계산 간단하게 하기
  - 2^10 = 1,024 유사 10^3 = 1000
  - 2^32 = 2^30 \* 2^2 = 4 \* 10^(3*3) 따라서 4gb
- b와 B와 완전히 다르다
  - b = bit, B = byte
  - 100Mbps(mega bits er second) = 12.5 megabytes per second

## 1. Variables, Operators and Control Flow

### Variables

초기화하지 않으면 0이 아니라 쓰레깃값이 있다.

#### Suffix

  |Type|Suffix|
  |-|-|
  |int, double|No suffix|
  |unsigned int|U,u|
  |long long|LL,ll|
  |unsigned long long|ULL, ull|
  |float|F,f|

  위와 같은 접미사를 안 붙이면 int type이라고 해석될 수도 있다.

#### Precison(Floating)

float은 1bit를 sign(양수, 음수) 8bit를 exponent, 23bits를 significand와 같은 숫자를 저장하는데 사용한다.

> 7자리 숫자 사용 가능

double은 1bit를 sign, 11bits를 exponent, 52bits를 significand를 저장하는데 사용한다.

> 16자리 숫자 사용 가능

따라서 당연히 exponent와 significand이 들어가는 저장소의 크기가 큰 double이 정확성이 높아진다.

> e.g. 1.2345 = 12345(significand) * 10^-4(exponent)

### Operators

#### Unary and Binary Operator = 단항과 이항 연산자

```c
-3 // unary
3-5 // binary
```

#### Assignment Operators

(LHS) = (RHS)

Left hand side에는 값을 저장할 변수, Right hand side에는 변수든 값이든 아무거나 와도 된다.

``` c
int x, y;
y = (x=5) +1 // x == 5, y==6
```

대입한 후 대입된 값을 반환

``` c
a=b=c // a = (b=c)
```

Assignments work right to left.

#### Type Conversion

> 3 + 2.0f == 5.0

정보 손실을 막기 위해 숫자를 더 많이 담을 수 있는 데이터로 자동 변환된다.

#### Integer Promotion

char + char 또는 short + short 연산을 하더라도 연산 과정에서는 Int로 Type Conversion이 일어나며 연산 후 다시 char로 바뀐 후 저장하게 된다.

### Control Flow - 흐름제어

if, else와 같은 흐름을 바꿀 수 있는 statments 을 배우게 된다.

## 마무리

수업 2시간짜리 사전 영상이라서 당황을 많이 했지만, 매우 기본적인 C 문법을 다루셔서 빠르게 들을 수 있었고 정리한 것도 별거 없었다. 그래도 교수님이 직접 C를 복습시켜주니 아주 좋은 수업이었다.
