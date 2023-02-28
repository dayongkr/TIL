# 자료구조개론 1주 차

`Fundamentals of Data Structures in C`라는 교재를 가지고 자료구조와 알고리즘의 기초 개념들을 배운다.

## System Life Cycle

효율적으로 개발하기 위해 알고 있으면 좋다.

- Requirements
  - 문제 정의하는 과정 (입력하고 출력값 정의)
- Analysis
  - 정의한 것을 쪼개서 간단한 연산 단위로 나타내는 과정
- Design
  - `Analysis`에서 좀 더 구체적으로 설계하는 과정 *ex) 이 데이터는 정수로 저장*
  - 설계 마지막 단계
- Refinement and coding
  - 특정 언어로 구현
  - 구현 시작
- Verification
  - 디버깅 및 검증 단계
- Error removal
  - 검증 과정에서 발생한 오류 해결

위에서부터 아래로 진행하게 되는데 각 단계에서 확실하게 하고 넘어가야 다시 돌아가야 하는 불필요한 과정을 겪을 필요가 없게 된다.

## Abstract Data Type - ADT

객체와 객체의 작동을 추상적으로 나타내며 따로 구현하지 않는다.

``` c
int hello(); // abstract
...
int hello() { // implementation
  printf("hello");
}
```

## Pointers

C에 있는 고유적 개념으로 주소를 저장할 때 사용하는 기능이다.

- &변수
  - 변수의 주소
- *포인터변수
  - 포인터 주소에 있는 값.

``` c
int i, *pi;
pi = &i // &i == pi
*pi = 10 // i == 10
```

잘만 이해하면 간단한 개념이지만 매우 헷갈리는 개념이다.

## Dynamic Memory Allocation

동적 메모리 할당이란 프로그램 실행 중에 동적으로 메모리(`Heap` 영역)를 할당하는 것을 말한다.

C언어에서는 `<stdlib.h>`파일에 있는 `malloc` 함수로 할당하고 `free`로 해제한다.

반드시 필요가 없어진 것은 `free`로 메모리를 다시 풀어주자!

참고로 `malloc`는 반환 값이 `void*`이기 때문에 `cast operator`로 데이터 타입을 변환해줘야 한다.

```c
int *pi;
pi = (int *) malloc(sizeof(int));
...
free(pi);
```

위 사실들을 활용해서 동적 할당을 해보자면 위와 같이 `malloc`을 사용해서 할당하고 다음에 반드시 `free` 함수를 사용해서 반환해주면 된다.

## 퀴즈 1 - 동적 메모리 할당으로 2차원 배열 구현

### Double pointer (이중 포인터)

해당 문제를 풀려면 먼저 이중 포인터를 알아야한다.

``` c
int a = 1;
int *pi = &a;
int **ppi = &pi;
```

변수 a의 주소를 포인터 변수 pi에 저장하고 포인터 변수 pi의 주소를 이중 포인터 변수 pi에 저장하는 코드이다.

> 즉 주소를 담을때 별이 한개씩 붙는다.
> ex. **pi의 주소름 담으려면 ***pi을 선언해야한다.

이중? 뭔가 2차원 배열에 사용할 수 있을 것 같다는 느낌이 든다.
