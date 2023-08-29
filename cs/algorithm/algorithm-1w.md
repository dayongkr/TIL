# 알고리즘개론 1주 차

해당 수업은 MIT 강의를 포함해서 진행된다.

## Induction

먼저 유도에 대해서 집고 넘어가셨다. 유도에는 3가지 요소가 있는데 먼저 basis, induction hypothesis, induction step이다. 이 3가지 요소를 잘 이해하고 있어야 유도를 이해할 수 있다.

- Basis
  - induction을 시작하기 위한 가장 기본적인 조건이다.
  - e.g. n = 0을 보통 basis로 잡는다.
- Induction Hypothesis
  - induction을 시작하기 위한 가정이다.
  - e.g. n = k일 때, induction이 성립한다고 가정한다.
- Induction Step
  - induction을 진행하기 위한 단계이다.
  - k (k <= n)의 일부를 증명하는 과정이다.
  - e.g. n = n + 1일 때, induction이 성립한다는 것을 보인다.

이렇게 k의 일부를 증명하는 것을 weak induction이라고 한다. 이와 반대로 k의 일부가 아닌 모든 것을 증명하는 것을 strong induction이라고 한다.

## Algorithm 이란?

알고리즘이란 문제를 풀기 위한 특정한 일을 수행하는 명령어들의 유한한 집합이다. 알고리즘이 만족해야하는 조건은 다음과 같다.

- input
  - 알고리즘은 0개 이상의 input을 받아들인다.
- output
  - 알고리즘은 1개 이상의 output을 반환한다.
- definiteness
  - 알고리즘은 각 명령어가 명확하게 정의되어야 한다.
- finiteness
  - 알고리즘은 유한한 수의 명령어로 구성되어야 한다.
- effectiveness
  - 알고리즘은 모든 명령어가 충분히 간단해야 한다.

### Analysis of Algorithm

알고리즘의 분석은 Random Access Machine (RAM)을 기준으로 한다. RAM은 다음과 같은 특징을 가진다.

- 각 명령어는 상수 시간에 실행된다. (unit time)
- 모든 메모리의 주소는 동일한 시간에 접근할 수 있다.
- 동시 실행을 하는 동작은 없다.

그리고 알고리즘의 효율성은 실행시간으로 측정하지 않고 기초적인 연산의 횟수로 측정한다. 이를 Big-O 표기법으로 표현한다. 이는 asymptotic performance를 나타내는 것으로, input의 크기가 충분히 커질 때, 실행시간이 어떻게 변화하는지를 나타낸다.

그리고 분석은 3가지 경우로 나누어진다.

- Worst Case
  - 가장 최악의 경우를 나타낸다.
  - 분석하기 쉬운 편이라서 많이 사용된다.
- Average Case
  - 평균적인 경우를 나타낸다.
  - 분석하기 어렵다.
    - 랜덤하고 실제 세계 입력들은 평균을 구하기 어렵다.
- Best Case
  - 가장 최선의 경우를 나타낸다.
  - 분석하기 어렵다.
    - 실제 세계에서는 최선의 경우가 거의 없다.

## MIT 1. Algorithm and computation

해당 수업에서는 계산 문제 풀기, 정확성 증명, 효율성, 소통을 중점적으로 다룬다.

알고리즘 소개를 위해 생일 문제를 예시로 들었다. 생일 문제는 생일이 같은 사람이 있는지를 구하는 문제이다. 이러한 문제를 풀기 위한 알고리즘을 정의를 했고 이를 위에서 배운 induction을 통해 증명을 했다.

## 마무리

결국 이번 수업에서 제일 중요한 부분은 correctness와 effectiveness를 증명하는 방법인 것 같다. 따라서 induction에 대한 이해를 높이는 것이 중요할 것 같다.
