# 알고리즘 3주 차

## Solving Recurrences

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
