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

### Dynamic Memory Allocation

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

### 퀴즈 1 - 동적 메모리 할당으로 2차원 배열 구현

#### Double pointer (이중 포인터)

해당 문제를 풀려면 먼저 이중 포인터를 알아야한다.

``` c
int a = 1;
int *pi = &a;
int **ppi = &pi;
```

변수 a의 주소를 포인터 변수 pi에 저장하고 포인터 변수 pi의 주소를 이중 포인터 변수 pi에 저장하는 코드이다.

> 즉 주소를 담을때 별이 한개씩 붙는다.
> ex. pi의 주소름 담으려면 pi을 선언해야한다.

이중? 뭔가 2차원 배열에 사용할 수 있을 것 같다는 느낌이 든다.

#### 코드

``` c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int w = 5, h = 5; // 배열의 넓이와 높이 설정
  int **arr = (int **)malloc(sizeof(int *) * h); 

  for (int i = 0; i < h; i++)
  {
    arr[i] = (int *)malloc(sizeof(int) * w);
  }

  // 메모리 해제
  for (int i = 0; i < h; i++)
  {
    free(arr[i]);
  }
  free(arr);

  return 0;
}
```

2차원 배열이기 때문에 주소 안에 또 주소가 들어가야 하므로 앞서 말한 이중 포인터를 사용해야 한다.

그래서 처음에 이중 포인터를 선언하고 malloc 함수를 사용해 포인터 변수가 들어갈 만한 크기의 메모리를 할당해주고 반복문을 사용해서 포인터 변수에도 정수 데이터들이 들어갈 만한 크기의 메모리를 할당해줬다.

마지막으로 어차피 프로그램이 종료돼서 불필요하지만, 메모리도 해제해 줬는데 메모리 할당 순서 반대로 해제를 해줘야 한다.

> 해체는 설치의 역순!

## 알고리즘

유한한 명령어들의 집합을 알고리즘이라고 한다. 

그리고 모든 알고리즘은 아래 기준들을 만족해야 한다.

- 입력
- 출력
- 명확성 Definiteness
- 한시성 Finiteness
- 효율성 및 실행 가능성 Effectiveness & Feasible

### 선택 정렬

한 쪽으로 전체 탐색한 후 제일 작은 수를 맨 앞으로 가져오는 정렬 알고리즘

``` c
#include <stdio.h>

void swap(int *min, int *pre);

int main(void)
{
  int arr[3] = {3, 1, 2}; // 임의 배열 수동으로 생성
  int index = sizeof(arr) / sizeof(int); // 배열의 인덱스

  for (int i = 0; i < index; i++) // N^2 시간 복잡도
  {
    int minIndex = i;
    for (int j = i+1; j < index; j++)
    {
      if (arr[j] < arr[minIndex])
      {
        minIndex = j;
      }
    }
    swap(&arr[minIndex], &arr[i]);
  }
  return 0;
}

void swap(int *min, int*pre) 
{
  int temp = *pre;
  *pre = *min;
  *min = temp;
}
```

### 퀴즈 2 - 정수값 3개를 오름차순으로 정렬해서 출력해라


``` c
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(void)
{
  int temp;
  int x = rand() % 100, y = rand() % 100, z = rand() % 100;
  if (x > y)
  {
    swap(&x, &y);
  }
  if (x > z)
  {
    swap(&x, &z);
  }
  if (y > z)
  {
    swap(&y, &z);
  }
  printf("%d %d %d\n", x, y, z);
  return 0;
}
```

선택정렬을 사용하지 말라는 걸 보면 배열을 쓰면 안 될 것 같았다.

그래서 어차피 변수가 3개 밖에 없으니 모든 조건을 따져서 자리를 바꾸는 코드를 짰다.

시간복잡도 O(N)이니 양호한 것 같기도 한데 결국 선택정렬이랑 유사한 것 같아서 찜찜  하긴하다.

## 성능 분석

Space complexity, Time complexity를 기준으로 성능을 분석한다.

- Space complexity
  - 메모리를 얼마나 사용하는지
- Time complexity
  - 얼마나 빨리 수행되는지
  - 요즘은 대용량 시대라서 주로 Time complexity 기준으로 성능을 분석


### Time Complexity

compile time + run time으로 측정하는데 보통 runtime만 측정한다.

하지만 시간으로 따지게 되면 시스템 성능 차이로 더 복잡한 코드가 더 빠르게 측정될 수도 있기 때문에 program step으로 시간복잡도를 측정하게 된다.

예를들어 변수에 값을 초기화하거나 반복문을 작동할 때 +1이 되고 변수를 선언할 땐 측정하지 않는다.

#### Counting the Steps

위에 설명되어있는 방법으로 예시 코드의 시간 복잡도를 측정해보자.

``` c
float sum(float list[], int n) {
  float tempsum = 0; // +1
  for (int i = 0; i<n; i++){ // +(n+1)
    tempsum += list[i]; // +n
  }
  return tempsum; // +1
}
```

변수에 대입으로 +1, 변수 대입 및 반복문 +(n+1), 반복문 내 변수 대입 +n, 마지막 반환 +1 총 2n+3이 발생한다.

n이 매우 큰 숫자로 증가하면 뒤에 상수 +3은 실질적으로 의미가 없어지기 때문에 보통 상수는 무시하는데 이를 Asymptotic Notation(점근적 표기법)이라고 한다.

### Asymptotic Notation - O(빅오)

자세한 내용은 알고리즘 개론에서 수업에서 소개될 예정이다.

어쨋든 해당 표기법은 다양하게 존재하지만 보통 빅오로 표기한다.

### 😁빅오 표기법(시험에 낸다고 강조)

모든 n >= n0에 대하여 O<=f(n)<c*g(n)인 양의 상수 c와 n0가 존재하면 f(n)=O(g(n))이다.

예를들어 설명하자면 아래와 같다.

- n >=2 일떄 3n+2 <= 4n 이므로 3n+2 = O(n)이다
- n >=3 일떄 3n+3 <= 4n 이므로 3n+3 = O(n)이다
- n >=10 일떄 100n+6 <= 101n 이므로 100n+6 = O(n)이다
- n >=5 일떄 10n^2+4n+2 <= 11n^2 이므로 10n^2+4n+2 = O(n^2)이다
- n >=4 일떄 6*2^n+n^2 <= 7*2^n 이므로 6*2^n+n^2 = O(2^n)이다

위에 적은 내용이 빅오 표기법으로 표현하는 방법이니 꼭 기억해두자.. 객관식으로 내기 좋은 부분이라고 강조하셨다.

참고로 빅오 표기법의 순서는 아래와 같다.

O(1) < O(log n) < O(n) < O(nlogn) < O(n^2) < O(n^3) < O(2^n)

왼쪽부터 오른쪽으로 시간 복잡도가 안 좋아지는 순서대로 나열했다.
> 보통 O(nlogn)까지를 좋은 시간 복잡도라고 한다.

### 퀴즈 3 - 주어진 식이 올바른 이유를 설명해라

빅오표기법으로 나타낸 4가지 식을 주었으며 예제보다 비교적 복잡한 식들이었지만 증명 조건이 어렵지 않아서 금방 풀었다.
