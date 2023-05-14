# 시스템프로그램 11주 차

## Loop Unrolling

combine5에서는 loop unrolling을 통해 성능 향상을 시키려고 했다.

```c
acc = (acc OP data[i]) Op data[i+i];
```

위 코드가 inner loop인데 위와 같이 하면 성능 향상이 되지 않는다. 왜냐하면 두 Op 모두 이전 연산의 결과를 사용하기 때문이다. 따라서 여전히 n개의 operations의 critical path가 존재한다.

이를 해결하려면 2가지 방법이 있다.

### Multiple Accumulators

```c
//inner loop
acc0 = acc0 OP data[i];
acc1 = acc1 OP data[i+1];
...
//outer loop
*dest = acc0 OP acc1;
```

위와 같이하면 짝수 번째와 홀수 번째를 병렬로 계산할 수 있다. 이를 통해 두 Op은 서로 독립적이게 된다. 따라서 n/2개의 operations의 critical path가 존재한다. 이로써 parallel하게 계산할 수 있다.

하지만 FP 연산에서는 이러한 방법이 적용되지 않는다. 왜냐하면 FP 연산은 associative하지 않기 때문이다. 하지만 모든 경우에 적용되지 않는 것은 아니다. 따라서 개발자의 판단이 중요하다.

> FP는 rounding이나 overflow가 발생할 수 있기 때문에 associative하지 않다.

### Reassociation transformation

```c
acc = acc OP (data[i] OP data[i+1]);
```

위와 같이하면 반복간의 data-dependency가 하나로 줄어든다. 따라서 n/2개의 operations의 critical path가 존재한다. 이로써 parallel하게 계산할 수 있다.

> 일반적으로 accumulator를 사용하는게 reliable하다.

### SIMD

지금까지 SIMD를 사용하지 않았는데 사용하게되면 거의 4배 또는 8배의 성능 향상을 기대할 수 있다. 예를들어 vmulps와 같은 경우에는 4개의 FP 연산을 한번에 수행할 수 있기 때문이다.

## Some Limiting Factors

두 가지 제한사항에 대해 알아보자.

- Register spilling
- Branch prediction

### Register spilling

위에서 accumulator를 사용하면 성능 향상을 기대할 수 있다고 했다. 하지만 이는 register의 수가 충분할 때에만 가능하다. 만약 accumulator의 수가 register의 수보다 많다면 register spilling이 발생한다. 이때 memory에 접근해야하기 때문에 성능이 저하된다.

### Branch prediction

branch prediction이 잘못되면 pipeline이 flush되어 성능이 저하된다. 따라서 쓸대없는 branch를 줄이는 것이 중요하다. loop와 같은 경우에는 prediction이 잘 되기 때문에 성능 저하가 적다. 다만 if문과 같은 경우에는 conditional move를 사용하는 것이 좋다.

```c
if (a > b) {
    c = a;
} else {
    c = b;
}
// conditional move
c = (a > b) ? a : b;
```

위와 같이하면 branch prediction이 발생하지 않기 때문에 성능 향상을 기대할 수 있다.

### 성능 향상 하는 법 정리

- High-level design
  - alogrithms, data structures를 잘 적용하기
- Basic coding principles
  - 최적화를 막는 것들을 찾아 compiler가 최적화할 수 있도록 하기
    - 연산들을 가능한 loop 밖으로 빼기
    - 함수 호출을 최소화하기
    - 불필요한 메모리 접근을 최소화하기
  - 즉 반복문 안을 잘 살펴보기
- low-level design
  - loop unrolling
    - accumulator 사용하기
  - register spilling 줄이기
  - 예측 불가능한 branch 줄이기
  - conditional move를 통해 conditional branch 줄이기

## Program Profiling

큰 규모의 프로그램은 직접 최적화할 부분을 찾기 어렵기 때문에 Code profiler를 통해 최적화할 부분을 찾는다. 우리는 linux에서 제공하는 gprof를 사용할 것이다.

### gprof

2 가지 형태의 결과를 제공한다.

- flat profile
  - 각 함수별로 얼마나 많은 시간을 사용했는지 보여준다.
- call graph
  - 각 함수가 어떤 함수를 호출했는지 보여준다.

#### gprof 사용법

3가지 단계로 나눠서 사용한다.

1. compile
   - -pg 옵션을 주어야한다.
2. run
   - 실행하면 gmon.out 파일이 생성된다.
3. analyze
   - gprof 실행파일

#### gprof 결과 해석

flat profile에서는 다음과 같은 정보를 제공한다.

- % time
  - 해당 함수가 전체 시간 중 얼마나 사용했는지
- cumulative seconds
  - 해당 함수가 실행된 후 누적 시간
- self seconds
  - 해당 함수가 실행된 후 소요된 시간
- calls
  - 해당 함수가 실행된 횟수
- self s/call
  - 한번 실행될 때 소요된 시간
- name
  - 함수 이름

call graph에서는 다음과 같은 정보를 제공한다.

- index
  - 함수의 index
- % time
  - 해당 함수가 전체 시간 중 얼마나 사용했는지
- self
  - 해당 함수가 실행된 후 소요된 시간
- children
  - 해당 함수가 호출한 함수들의 시간
- called
  - 해당 함수가 호출한 함수들의 횟수
- name
  - 함수 이름
