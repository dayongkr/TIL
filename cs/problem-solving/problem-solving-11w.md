# 문제해결 11주 차

## Sorting

Comparison-based와 non-comparison-based로 나눌 수 있다. Comparsion-based는 key를 비교하여 정렬하는 것이고 non-comparison-based는 key를 index로 두고 정렬하는 것이다.

### Time Complexity of Sorting

- Naive Sorting: O(n^2)
  - Selection Sort, bubble sort, insertion sort
  - 요소 중 조금만 틀린 경우나 배열의 크기가 작은 경우에 사용
  - 구현이 간단하다.
- Efficient Sorting: O(nlogn)
  - Merge sort, quick sort, heap sort
  - 기본적으로 해당 sorting 알고리즘을 사용한다.
- Non-comparison-based Sorting: O(n)
  - Counting sort, radix sort
  - key의 범위가 작은 경우에 사용한다.
  - key의 범위가 크면 메모리를 많이 사용하게 된다.

### Merge vs Quick vs Heap

- Merge Sort
  - 같은 값의 순서가 보장된다. 즉 Stable
  - 추가적인 메모리가 필요하다.
- Quick Sort
  - 같은 값의 순서가 보장되지 않는다. 즉 Unstable
  - 추가적인 메모리가 필요하지 않다.
  - cache friendly하기 때문에 빠르다.
- Heap Sort
  - 같은 값의 순서가 보장되지 않는다. 즉 Unstable
  - 추가적인 메모리가 필요하지 않다.
  - input data가 바뀔 때 좋은데 PS 문제에서는 input data가 바뀌지 않기 때문에 잘 사용하지 않는다.

이중 Merge Sort를 설명하셨는데 기본적인 개념은 일단 Divide한 후 sort하면서 merge를 함으로써 정렬을 하는 것이다.

이는 재귀적으로 구현할 수 있고, 이 때 base case는 left가 right보다 크거나 같을 때이다.

### Counting Sort

모든 숫자가 정수이고 점수의 범위가 작을 때 즉 dense한 경우에 사용한다. 구현 방법은 간단한데 각 숫자의 개수를 세고 그 숫자를 그 개수만큼 출력하면 된다. 따라서 배열로 구현하면 제일큰 숫자만큼의 메모리가 필요하다.

## Data Structure

Stack과 Queue를 구현하는 방법에 대해 설명하셨다. 다만 이는 여러 수업을 통해 배웠기 때문에 구현에 대한 팁 몇가지만 정리하려고 한다.

- s\_ prefix를 붙여서 구현하면 좋다.
  - C에서는 함수를 global context에서 노출되기 때문에 이름이 충돌할 수 있다.
- typedef를 써서 요소의 type을 바꿔주면 좋다.
  - 요소의 type을 바꿀 필요가 있을 때 한번에 바꿀 수 있다.
- peek와 pop은 flag를 사용해서 구현하면 좋다.
  - 성공적으로 수행했는지 실패했는지 알 수 있다.

### Queue Example: Maze Exploration

Queue를 사용하면 BFS로 최소 경로를 찾을 수 있다. 만약에 recursive하게 구현하면 미로 크기가 커지면 stack overflow가 발생할 수 있다. 따라서 queue를 사용해서 구현하면 된다.

구현 방식은 먼저 현재 좌표, 현재 좌표까지 이동한 거리를 담은 구조체를 만든다. 맨 처음엔 시작 주소와 0을 담은 구조체를 넣고 시작한다. 그리고 queue가 비어있지 않은 동안 다음을 반복한다.

- queue에서 하나를 꺼낸다.
- 꺼낸 좌표가 도착 좌표와 같다면 종료한다.
- 꺼낸 좌표에서 갈 수 있는 좌표를 모두 queue에 넣는다.
- 꺼낸 좌표에서 갈 수 있는 좌표를 모두 queue에 넣을 때 거리를 1 증가시킨다.
- queue가 비어있으면 도착 좌표에 도달할 수 없다.

이렇게 BFS로 구하면 모든 좌표까지의 최소 거리를 구할 수 있다. DFS로 구하면 최소 거리를 구할 수 없다.
