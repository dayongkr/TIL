# 자료구조개론 5주 차

## Stack

Stack은 LIFO(Last In First Out) 구조를 가지고 있다. Stack은 push와 pop이라는 연산을 가지고 있다. push는 stack의 top에 element를 추가하는 연산이고, pop은 stack의 top에 있는 element를 제거하는 연산이다.

computer architecture에서 배우고 있는 procedure call에서 stack을 사용하는게 stack의 대표적인 예이다.

### Stack 활용

- Line editing
- Bracket matching
- Maze solving
- Expression evaluation

> top은 stack의 마지막 element를 가리키고, base는 stack의 첫번째 element를 가리킨다.

## Queue

Queue는 FIFO(First In First Out) 구조를 가지고 있다. Queue는 enqueue와 dequeue라는 연산을 가지고 있다. enqueue는 queue의 tail에 element를 추가하는 연산이고, dequeue는 queue의 head에 있는 element를 제거하는 연산이다.

Job scheduling이 대표적인 예이다.

> tail은 queue의 마지막 element를 가리키고, head는 queue의 첫번째 element를 가리킨다.

계속 rear index를 증가시키다보면 배열의 끝에 도달하기 때문에 더이상 rear index를 증가시킬 수 없다. 이때 rear index를 0으로 초기화시켜서 배열의 처음부터 다시 사용할 수 있도록 한다. 이렇게 배열의 처음부터 다시 사용할 수 있도록 하는 것을 circular queue라고 한다.

일부로 한 칸을 비우고 front와 rear가 같으면 queue가 empty이고, rear가 front보다 1 작으면 queue가 full이라고 구현하여 circular queue를 구현할 수 있다.

## Quiz

### Quiz 13

stack implementation을 사용하여 10개의 랜덤 정수를 생성하고 스택에 push하는 프로그램을 작성하라. 그리고 스택에 있는 정수를 pop하여 출력하는 프로그램을 작성하라.

rand, time header를 사용해서 랜덤 정수를 생성하고 슬라이드에 있는 stack 예시를 사용해서 구현했다.

### Quiz 14

모든 공간을 사용할 수 있는 circular queue를 구현하라.

count 변수를 추가하고 add하면 count 증가 delete하면 count 감소하도록 구현했다. 그리고 empty, full을 체크하는 조건문에 각각 count == 0, count == MAX를 추가하면 된다.

### Quiz 15

rows와 colums가 주어졌을 때 처음부터 끝까지 가는데 걸리는 최대 거리를 구하시오.

최대 거리는 첫 번째와 마지막 칸도 계산에 포함 한다면 모두 칸을 한 번씩 방문한 m * n번이다.
