# 자료구조개론 14주 차

## Sorting

Comparison 기반의 sorting algorithm을 배운다.

### Sorting Terminology

- Stable: 같은 key를 가진 원소들의 순서가 정렬 전과 정렬 후에도 유지되는 것
- Decision Tree: sorting의 절차를 tree로 표현한 것으로 각 vertex는 key의 비교를 나타내고 각 branch는 비교의 결과에 따라 나뉜다.
  - height은 최소한 log(n!) + 1인데 이는 최악의 경우의 비교 횟수이다.
  - log(n!) >= (n / 2) \* log(n / 2)와 같으므로 최악의 경우의 비교 횟수는 n \* log(n)이다. 따라서 비교기반 sorting algorithm의 lower bound는 n \* log(n)이다.

### Insertion Sort

- Worst Case: O(n^2)
- Best Case: O(n)

1 ~ n-1까지 list[i]를 정렬된 list[0] ~ list[i-1]에 삽입하는 알고리즘이다. 구현을 어떻게 하는지에 따라 다르지만 보통 맨 앞에는 비워두고 임시로 저장하는 용도로 사용한다. 그리고 나서 list[i-1] 부터 list[1]까지 비교를 하는데 한 칸씩 뒤로 밀면서 비교를 하다가 list[i]보다 큰 값을 만나면 그 자리에 list[i]를 삽입한다.

### Bubble Sort

- Worst Case: O(n^2)
- Best Case: O(n)

이웃한 두 원소를 비교하여 큰 값을 뒤로 보내는 알고리즘이다. 끝까지 수행하면 매 반복에서의 가장 큰 값이 맨 뒤로 이동하게 되기 때문에 뒤에는 정렬이 되어있다고 가정하고 수행한다.

### Selection Sort

- Worst Case: O(n^2)
- Best Case: O(n^2)

list[i]부터 list[n-1]까지의 원소 중 가장 작은 값을 찾아 list[i]와 swap하는 알고리즘이다. 해당 알고리즘은 앞에서 부터 정렬이 되어있다고 가정하고 수행한다.

### quick sort

- Worst Case: O(n^2)
  - pivot이 항상 최솟값이나 최댓값인 경우
- Best Case: O(n \* log(n))

먼저 pivot을 임의로 정한 후 pivot보다 작은 값은 왼쪽, 큰 값은 오른쪽으로 보내는 알고리즘이다. 이후 왼쪽과 오른쪽을 각각 quick sort를 수행한다.

### merge sort

- Worst Case: O(n \* log(n))
- Best Case: O(n \* log(n))

일단 list를 계속 반으로 나눈 후 각각 정렬을 하면서 합친다. 합칠 때는 두 list의 맨 앞의 값을 비교하여 작은 값을 먼저 넣는다. 그러면 보통 한쪽 list가 먼저 끝나게 되는데 이 때 나머지 list를 그대로 넣어주면 된다. 수업에서는 재귀를 사용하지 않고 반복문으로 구현하였다.

### heap sort

- Worst Case: O(n \* log(n))
- Best Case: O(n \* log(n))

heap을 이용하여 정렬하는 알고리즘이다. 먼저 max heap으로 만든 후 root와 마지막 원소를 swap하고 마지막 원소를 제외한 나머지 heap을 max heap으로 만든다. 이를 반복하면 정렬이 완료된다.

## Hashing

Symbol Table을 구현하는 방법 중 하나로 hash table을 사용하는 방법이 있다. hash table은 key를 hash function을 통해 index로 변환한 후 해당 index에 저장하는 방식이다. hash function은 key를 index로 변환하는 함수로 key가 같으면 같은 index를 반환해야 한다.

### Hashing Terminology

- Identifier density: key의 개수 / table의 크기
  - identifier density가 높을수록 collision이 발생할 확률이 높다.
- Load factor: n / (slot의 갯수 \* bucket의 크기)
  - 결국 identifier density와 같은 의미이다.
- synonym: 같은 index에 저장되는 key
- collision: synonym이 발생하는 경우
- overflow: bucket이 꽉 차서 더 이상 저장할 수 없는 경우

### Hash Function

Hash function은 연산이 간단해야하고 collision이 적고 편향되지 않아야 한다. 또한 모든 index에 대해 key가 저장될 확률이 같아야 하는 unifrom hashing을 만족해야 한다. hash function의 종류로는 아래와 같은 것들이 있다.

- mid square method
  - key를 제곱한 후 중간의 몇 비트를 index로 사용하는 방법
- division method
  - key를 table의 크기로 나눈 나머지를 index로 사용하는 방법
  - 2의 제곱수에 너무 가깝지 않은 소수를 사용하는 것이 종종 좋은 선택이다.
  - 짝수로 연산을하면 짝수는 짝수로 홀수는 홀수로 연산되기 때문에 홀수로 연산하는 것이 좋다.

### Overflow Handling

Open Addressing과 Chaining이 있다. Open Addressing은 collision이 발생하면 다른 index에 저장하는 방법이고 Chaining은 collision이 발생하면 해당 index에 linked list를 만들어서 저장하는 방법이다.

#### Open Addressing

- Linear Probing
  - overflow가 발생하면 다음 index에 저장하는 방법
  - index = (index + 1) % table size
  - clustering이 발생할 수 있다.
- Random Probing
  - random number를 생성하여 index를 찾는 방법
  - 단 항상 같은 sequence의 random number을 사용한다.

Random Probing이 unsuccessful search(insert), successful search 모두 linear probing보다 좋은 성능을 보인다.

만약에 Open addressing을 사용하는 환경에서 어느 record가 삭제되면 tombstone을 사용하는데, tombstone은 해당 index에 더 이상 record가 없음을 표시하는 것이다. search 과정에서 tombstone을 만나면 계속해서 다음 index를 찾아나가야 한다. insert 과정에서 tombstone을 만나면 그 자리에 insert를 하면 된다.
