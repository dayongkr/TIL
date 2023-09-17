# 알고리즘 3주 차

## Solving Recurrences

Recurrence란 더 작은 입력에 대한 값으로 표현된 방정식 또는 부등식이다.

recurrence의 시간 복잡도를 구하는 방법은 다음과 같다.

- substitution method
- recursion-tree method
- master method

### substitution method

한국말로는 치환법 또는 대입법이다.

간단하게 설명하자면 일단 recurrence의 시간 복잡도를 추측하고, 추측한 시간 복잡도를 induction을 이용하여 증명하는 방법이다.

#### suubstitution method의 예시

T(n) = 2T(n/2) + n

1. T(n) = O(n log n)이라고 추측한다.
2. Induction goal: T(n) <= cn log n
   1. c > 0, n >= n0
3. induction hypothesis: T(n/2) <= c(n/2) log (n/2)
4. Proof of induction goal
   1. T(n) = 2T(n/2) + n <= 2c(n/2) log (n/2) + n
   2. cn log n - cn log 2 + n <= cn logn
   3. cn log 2 >= n
   4. c >= 1
   5. n >= 1
   6. 따라서 T(n) = O(n log n)

### recursion-tree method

한국말로는 재귀 트리 방법이다.

recurrence를 트리로 표현하고, 트리의 높이와 각 노드의 시간 복잡도를 구하여 recurrence의 시간 복잡도를 구하는 방법이다.

#### recursion-tree method의 예시

T(n) = 2T(n/2) + n

- recurrence를 트리로 표현한다.
  - root node: T(n)
  - left child node: T(n/2)
  - right child node: T(n/2)
- 각 노드의 시간 복잡도를 구한다.
  - root node: n
  - left child node: n/2
  - right child node: n/2
- 트리의 높이를 구한다.
  - log n
- recurrence의 시간 복잡도는 O(n log n)이다.

### master method

T(n) = aT(n/b) + f(n)의 꼴인 recurrence의 시간 복잡도를 구하는 방법이다.

단 a >= 1, b > 1, f(n) > 0이다.

기본적인 개념은 f(n)과 n^logb a를 비교하여 recurrence의 시간 복잡도를 구하는 것이다.

1. f(n) < n^logb a
   - T(n) = n^logb a

- f(n) = n^logb a
  - T(n) = n^logb a log n
- f(n) > n^logb a
  - T(n) = f(n)
  - 단 a f(n/b) <= cf(n)이어야 한다.
    - c < 1, n >= n0

#### master method의 예시

T(n) = 2T(n/2) + n

- a = 2, b = 2, f(n) = n
- f(n) = n^logb a = n
- 따라서 T(n) = n^logb a log n = n log n

## binary heap

binary heap은 priority queue를 구현하는데 사용되는 자료구조이다. binary heap은 다음과 같은 특징을 가진다.

- complete binary tree이다.
  - index로 표현할 수 있다.
  - parent node의 index는 `i/2`이다.
  - left child node의 index는 `2i+1`이다.
  - right child node의 index는 `2i+2`이다.
- 추가로 자식 노드는 부모 노드보다 크지 않다.
- 최대 힙의 경우, 루트 노드가 최대값이다.

### insert

binary heap에 새로운 값을 추가하는 방법은 다음과 같다.

1. binary heap의 마지막 노드에 새로운 값을 추가한다.
2. 추가한 노드와 부모 노드를 비교한다.
3. 추가한 노드가 부모 노드보다 크다면, 두 노드를 swap한다.
4. 추가한 노드가 부모 노드보다 작거나 같다면, 추가한 노드가 binary heap의 조건을 만족할 때까지 2~3을 반복한다.
5. 추가한 노드가 binary heap의 조건을 만족하면 종료한다.

시간 복잡도는 `O(log n)`이다.

### delete

binary heap에서 값을 삭제하는 방법은 다음과 같다.

1. root 노드와 마지막 노드를 swap한다.
2. 마지막 노드를 삭제한다.
3. root 노드와 가장 큰 값을 가진 자식 노드를 비교한다.
4. root 노드가 자식 노드보다 작다면, 두 노드를 swap한다.
5. root 노드가 자식 노드보다 크거나 같다면, root 노드가 binary heap의 조건을 만족할 때까지 3~4를 반복한다.
6. root 노드가 binary heap의 조건을 만족하면 종료한다.

시간 복잡도는 `O(log n)`이다.

### heap sort

heap sort는 binary heap을 이용하여 정렬하는 방법이다. heap sort는 다음과 같은 특징을 가진다.

- binary heap을 이용하여 정렬한다.
- in-place sort이다.
- 시간 복잡도는 `O(n log n)`이다.
