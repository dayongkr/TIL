# 자료구조개론 2주 차

이번 수업은 크게 Array와 Strucutre을 다룬다. 이번 수업 또한 다른 수업이랑 겹치는 부분이 많고 기본적인 내용들이 많아서 최대한 간추려서 정리하였다.

## Array

``` c
int list[5] // int type을 5개를 담을 수 있는 list 선언
int *list = (int *) malloc(sizeof(int) * 5); // 동적 할당
```

연속적인 메모리 위치의 집합, 동일 타입한 데이터의 모음, <index, value>의 한 쌍이다.

### 주소 및 값 불어오기

``` c
(list + 2) 또는 &list[2] // 주소 가져오기
*(list + 2) 또는 list[2] // 값 가져오기
```

Array에서 주소 및 값을 가져오는 방법은 두 가지이다.

### 2차원 배열

데이터를 담을 memory block과 첫 주소를 담을 memory block이 추가로 필요하게 된다.

추상적으로 n*m 테이블로 표현하는 것이지 당연히 선형적으로 저장한다.

### Dynamically Allocated Arrays

프로세스 중에 데이터를 할당하는 방식으로 보통 malloc 함수를 사용해서 배열을 만든다. 필요한 만큼의 크기로 배열을 선언할 수 있으므로 불필요한 메모리 낭비를 막을 수 있다.

2차원 배열을 만들고 싶으면 이중 포인터를 사용하면 된다.

> Row만큼의 배열을 만들고 해당 요소에 Col만큼의 배열을 각각 연결하여 구현

### Quiz4

Q. 동적 할당 배열을 사용해서 2차원 배열을 구현하는데 각 Row에 Col이 정해져 있는데 length 배열을 사용해서 구현하시오.

length 크기를 체크해서 Row의 개수를 확인하고 각 Element에 있는 숫자를 사용해서 Col의 개수를 확인하는 방식으로 간단하게 풀었다.

## Structure

``` c
struct {
  char name[10];
  int age;
  float salary;
} person;

strcpy(person.name, "korykang");
person.age = 34;
person.salary = 35000;
```

위와 같이 객체와 같은 역할을 하는 자료구조이다.

> 각 item은 각자의 이름, type을 가지고 있고 이를 모은 게 Structure이다.

```c
typedef struct humanBeing{
  char name[10];
  int age;
  float salary;
}

humanBeing person1, person2;
```

위와 같이 Data type으로 만들어서 다음에 계속 사용할 수 있다.

> person1 == person2와 같이 비교 연산은 안되고 각각 item마다 비교해야한다.

### Assignments

```c
person1 = person2;
```

위와 같이 할당하면 각각 주소를 넣어주는게 아니라 각각 요소마다 값으로  할당하게 된다.

### Quiz5

Q. 구조체를 사용해서 reactancle, triangle, circle의 구조를 만들어라.

자세한 기준을 알려주시지 않으셔서 그냥 간단하게 길이, 각도, 반지름으로 각각 구현하였다.

## Polynomial Abstarct Data Type - 다항식 ADT

Coefficents와 Exponents의 조합으로 Exponent가 0보다 클 때까지 순차적으로 만든다.

그래서 수업에서는 Polynomial끼리 더하는 알고리즘을 구현하는 방법에 대해서 나오는데, 이때 배열을 사용하면 유용하기 때문에 오늘 수업에 포함된 것 같다.

알고리즘을 보면 각 Polynomial의 Exponent를 서로 비교해서 큰 Exponent의 Coefficent을 가져오고 갔으면 둘이 더하고 이런 식으로 계속 Exponent가 큰 부분부터 작은 부분까지 반복해서 최종값을 구하는 식이였다.

### Quiz6

Q. Array와 Struct 을 사용해서 polynomial의 Remove, Attach 함수를 구현하여라.

일단 Struct 이랑 해당 함수들의 알고리즘은 설명을 해주셨기 때문에 거기에 맞게 구현하였다.

Struct는 poly의 차수, 차수별 coef로 구현되어있고 Remove는 최대 차수를 지우는 함수 Attach는 coef를 해당 차수에 붙이는 함수이다.
