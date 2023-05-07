# 문제해결 10주 차

어려운 문제들은 optimization을 통해 해결할 수 있다. 따라서 O(log n)과 같은 시간복잡도를 가지는 알고리즘을 사용해야 할 수 있다.

이러한 O(log n)과 같은 시간복잡도는 문제를 2개 또는 k 개의 조각으로 나눌때 일어난다. 대표적인 data structure/algorithm으로는 아래와 같다.

- Binary search
- Sorting
  - quick sort
  - merge sort
- Partition (recursion)
  - 여기까지가 중요한 부분
- Tree data structure
  - red-black tree
  - interval tree
  - 높이가 log n이라서 traversal이 O(log n)이다.
- Priority queue
  - binary heap

## Binary Search

보통 sorted array에 target index를 찾는 문제를 binary search를 통해 해결할 수 있다. 이름 그대로 매 search 마다 array를 반으로 나누어서 탐색하는 방법이다.

가운데 요소가 target보다 크면 왼쪽, 작으면 오른쪽을 탐색한다. 이를 반복하면 O(log n)의 시간복잡도를 가지게 된다. 이를 구현하는 방법은 recursive하게 구현할 수도 있고, iterative하게 구현할 수도 있다.

```c
// recursive
int binary_search(int arr[], int l, int r, int target) {
  if(l > r) return -1;

  int mid = l + (r - 1) / 2; // overflow 방지
  if(arr[mid] == target) return mid;
  else if(arr[mid] > target) return binary_search(arr, l, mid - 1, target);
  else return binary_search(arr, mid + 1, r, target);
}
```

l >= r이 아니라 l > r 인 이유는 l == r 일 때에도 mid를 구해야 하기 때문이다. 그리고 mid를 구할 때 overflow가 발생할 수 있으므로 l + (r - 1) / 2로 구해야 한다. 하지만 보통의 문제로는 overflow가 발생하지 않는다.

```c
// iterative
int binary_search(int arr[], int l, int r, int target) {
  while(l <= r) {
    int mid = l + (r - 1) / 2;
    if(arr[mid] == target) return mid;
    else if(arr[mid] > target) r = mid - 1;
    else l = mid + 1;
  }
  return -1;
}
```

위의 코드는 정말 많이 사용하는 코드로 교수님이 꼭 기억하라고 하셨다.

### Additional Case

위에서 배운 코드는 target이 array에 딱 한 번만 존재하는 경우에만 사용할 수 있다. 문제는 이러한 경우는 없고 아래 4 가지 경우를 많이 사용한다.

- Index of first occurrence
- Index of last occurrence
- Index of least element greater than target
- Index of greatest element less than target

#### Index of first occurrence

```c
int first_occurrence(int arr[], int l, int r, int target) {
  int res = -1;
  while(l <= r) {
    int mid = l + (r - 1) / 2;
    if(arr[mid] == target) {
      res = mid; // return 하지 않고 res에 저장
      r = mid - 1; // 왼쪽에 더 있는지 확인
    }
    else if(arr[mid] > target) r = mid - 1;
    else l = mid + 1;
  }
  return res;
}
```

binary search 코드를 기반으로 몇 가지 수정만 하면 된다.

#### Index of last occurrence

```c
int last_occurrence(int arr[], int l, int r, int target) {
  int res = -1;
  while(l <= r) {
    int mid = l + (r - 1) / 2;
    if(arr[mid] == target) {
      res = mid; // return 하지 않고 res에 저장
      l = mid + 1; // 오른쪽에 더 있는지 확인
    }
    else if(arr[mid] > target) r = mid - 1;
    else l = mid + 1;
  }
  return res;
}
```

#### Index of least element greater than target

```c
int least_greater(int arr[], int l, int r, int target) {
  int res = -1;
  while(l <= r) {
    int mid = l + (r - 1) / 2;
    if(arr[mid] > target) {
      res = mid; // return 하지 않고 res에 저장
      r = mid - 1; // 왼쪽에 더 있는지 확인
    }
    else l = mid + 1; // 같거나 작으면 오른쪽에서 least greater가 나올 수 있다.
  }
  return res;
}
```

#### Index of greatest element less than target

```c
int greatest_less(int arr[], int l, int r, int target) {
  int res = -1;
  while(l <= r) {
    int mid = l + (r - 1) / 2;
    if(arr[mid] < target) {
      res = mid; // return 하지 않고 res에 저장
      l = mid + 1; // 오른쪽에 더 있는지 확인
    }
    else r = mid - 1; // 같거나 크면 왼쪽에서 greatest less가 나올 수 있다.
  }
  return res;
}
```

### Common Mistakes

- l <= r이 아니라 l < r로 하면 안된다. l == r일 때에도 mid를 구해야 하기 때문이다.
- 초기에 r에다가 arr.length - 1을 넣어야 한다. 그렇지 않으면 segmentation fault가 발생할 수 있다.
- least(target)은 last(target) + 1이 아니다.
- 반드시 배열은 sorted 되어 있어야 한다.

### Binary Search on Solution Space

binary search는 보통 주어진 input(array)에서 target을 찾는데 사용한다. 하지만 이를 응용해서 solution space에서 target을 찾는데 사용할 수도 있다.

> solution space: 가능한 모든 해의 집합

#### Capacity To Ship Packages Within D Days

> [LeetCode](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

주어진 weights 배열에서 순서대로 배를 태워서 D일 안에 모든 packages를 배로 옮길 수 있는 최소 capacity를 구하는 문제이다.

- capacity가 0이면 모든 packages를 배로 옮길 수 없다.
- capacity가 매우 크면 모든 packages를 배로 옮길 수 있다.
- capacity c가 가능하면 c+1도 가능하다.

이러한 사실을 사용해서 binary search를 할 수 있다. l을 0, r을 매우 큰 값으로 두고 binary search 하면서 mid 값만 가능한 값인지 확인하면 된다. 이러면 O(nlogn)으로 해결할 수 있다.

#### Nth Digit

> [LeetCode](https://leetcode.com/problems/nth-digit/)

1부터 m까지의 숫자를 이어서 만든 string에서 n번째 digit을 구하는 문제이다.

먼저 m까지의 숫자를 이어서 만든 string의 길이를 구하고 그 길이를 이용해서 n번째 digit을 구할 수 있다.

- 1 ~ 9 = 1 \* (9 - 1 + 1)
- 10 ~ 99 = 2 \* (99 - 10 + 1)
- 10^i ~ 10^(i+1)= (i + 1) \* (10^(i+1) - 10^i + 1)
- 10^i ~ M = (i + 1) \* (M - 10^i + 1)

위의 식을 이용해서 m까지의 숫자를 이어서 만든 string의 길이를 구할 수 있다. 그리고 이 길이가 n보다 작은 m 중 가장 큰 m에 n번째 digit이 속한다. 이는 위에서 배운 binary search case 중 index of greatest element less than target을 이용해서 구할 수 있다.

이렇게 하면 m을 구할 수 있는데 이젠 m에서 n번째 digit을 구하면 된다. 해당 digit이 m의 몇 번째 digit인지 구하고 m의 크기를 구한 후 10으로 나누고 마지막에 10으로 나누면 원하는 값이 나온다.
