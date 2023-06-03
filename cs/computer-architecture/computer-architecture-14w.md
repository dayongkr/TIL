# 컴퓨터구조개론 14주 차

## TLB

PTE는 메모리에 저장되어 있다보니 접근하는데 시간이 오래걸린다. 그래서 TLB라는 것을 사용한다. TLB는 Translation Look-aside Buffer로 PTE의 cache인 것이다. TLB는 보통 associative memory로 구현된다. TLB는 PTE의 cache이기 때문에 TLB miss가 발생하면 PTE를 찾아서 TLB에 저장한다. 근데 만약에 PTE에도 없다면 page fault가 발생한다. 이땐 page fault handler가 PTE를 메모리에 올리고 TLB에 저장한다.

![Memory Access Scenarios](./imgs/2023-05-30-16-06-08.png)

## Floating Point

소수를 binary를 표현하는 방법에 대해서 배웠는데 초반에는 Binary로 단순히 정수부분 fraction 부분을 나눠서 표현하는 fixed-point format를 설명하셨는데 이는 범위의 제한되어서 좋지 않은 방법이였다. 그래서 표준화된 IEEE 754에 대해서 설명하셨다.

### IEEE 754 Floating Point Format

Single precision은 32bit, Double precision은 64bit이다. Single precision은 1bit sign, 8bit exponent, 23bit fraction으로 구성되어있고 Double precision은 1bit sign, 11bit exponent, 52bit fraction으로 구성되어있다.

#### Single Precision Example

만약에 -0.75를 표현한다면 다음과 같이 표현할 수 있다.

- -0.75 = -(3/4) = -(3 \* 2^-2) = -1.1 \* 2 ^ -1
- sign: 1
- exponent: -1 + 127 =-1 + Bias = 126 = 01111110
- fraction: 100000000000...0

#### Single Precision Range

Exponent의 00000000과 11111111은 따로 사용되는 것들이 있어 사용을 못한다. 따라서 범위는 아래와 같다.

- Smallest: 1.0 \* 2^-126
- Largest: (2 - 2^-23) \* 2^127

#### Limitation

0.1을 single precision으로 표현하면 e는 123, fraction은 10011001100110011001101이 된다. 이를 다시 10진수로 표현하면 0.100000001490116119384765625가 된다. 즉, 0.1을 정확히 표현하지 못한다.

#### Floating Point Operations

- Addition
  - exponent가 큰 쪽에 맞춰서 fraction을 shift한다.
  - 두 fraction을 더한다.
  - normalize한다.
  - round을 하고 필요에 따라 normalize한다.

이는 hardware로 구성되는데 위와 같은 과정을 거쳐야 하기 때문에 integer adder 보다 복잡하고 느리다. 간단히 살펴보면 아래와 같다.

- Compare Exponent
  - Small ALU에 넣어 비교한다.
- Shift smaller number right
- Add fraction
  - Big ALU에 넣어 더한다.
- Normalize
  - shift를 진행한다.
- Round
  - 필요에 따라 normalize한다.

#### Bias를 사용하는 이유

bias를 exponent를 unsigned로 사용할 수 있어 bit로 비교가 가능하다.

#### Special Values

- 0
  - exponent: 0
  - fraction: 0
- Infinity
  - exponent: 11111111
  - fraction: 0
- NaN
  - exponent: 11111111
  - fraction: non-zero

#### Denormalized Numbers

exponent가 0이면서 fraction이 0이 아닌 경우이다. 이는 0이 아니지만 normalized number로 표현할 수 없는 경우이다. 이는 0.0 \* 2^-126 ~ 1.0 \* 2^-126 범위를 표현할 수 있다.

> exponent는 항상 1 - Bias이다.
