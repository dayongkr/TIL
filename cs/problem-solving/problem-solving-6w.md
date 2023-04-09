# 문제해결 6주 차

이제부터는 PS에 대한 내용을 다루기 시작한다.

대회에서는 부분점수를 전략적으로 얻는 것이 중요하다.

## 대회 Tips

### 반복회수에 따른 시간복잡도

- N < 20
  - O(2^N) 또는 O(N!) 또는 O(2^N)등의 시간복잡도를 가지는 알고리즘을 사용해도 된다.
- N < 40
  - exhaustive search를 사용해도 된다.
  - 다만 가지치기를 통해 시간복잡도를 줄여야 한다.
- N < 5000
  - 10000 * 10000 이중 반복문은 약 1초가 걸린다.
  - 따라서 O(N^2)의 시간복잡도를 가지는 알고리즘을 사용해도 된다. 
- N < 10000
  - O(N^2)의 시간복잡도를 가지는 알고리즘은 작동하지 않을 것이다.
- N < 10,000,000
  - O(N log N)은 작동하지 않을 것이다. 따라서 O(N)을 사용해야한다.

### 데이터 범위를 생각해라

- -100 <= d[i] <= 100 와 같은 사전에 정의된 범위
  - O(N) sorting 가능
- 양수 또는 문자
  - 배열의 index로 사용 가능
- 실수
  - 순서만 중요할 경우 정수로 변환하여 사용 가능
- 32bit 정수
  - 배열의 index로 사용하면 안된다.

## Two Pointers

2 개의 포인터들을 사용해서 search space를 줄이는 방법이다.

두 가지 방법이 있다.

- Increasing
- Narrowing

### Two Pointers Example

만약에 정렬된 배열을 주고 2개의 수를 더해서 M이 되는 경우를 찾는다고 하자. 이때 O(N^2)의 시간복잡도를 가지는 알고리즘을 생각할 것이다. 하지만 이때 Two Pointers를 사용하면 O(N)의 시간복잡도를 가지는 알고리즘을 만들 수 있다.

일단 양 끝에 포인터를 두고 시작한다. 그리고 두 포인터가 가리키는 값의 합이 M보다 크면 오른쪽 포인터를 왼쪽으로, 작으면 왼쪽 포인터를 오른쪽으로 이동시킨다. 만약에 두 포인터가 가리키는 값의 합이 M과 같다면 정답이다.

이렇게되면 정답을 놓치는 경우가 있을 것 같다고 생각할 수 있다. 하지만 배열은 정렬되어 있기 때문에 두 포인터가 가리키는 값의 합이 M보다 크다면 그 뒤에는 더 큰 값이 나올 수 없다.

### Two pointer 냄새를 맡는 법

1. 배열을 탐색이 필요한 경우
2. 배열을 정렬하거나 정렬된 배열을 탐색해도 제약이 없는 경우
3. 2개의 변수를 사용해야하는 경우
4. 연속된 부분 배열을 탐색해야하는 경우
5. Naive한 방법으로 풀었을 때 시간복잡도가 O(N^2)이상인 경우
6. 검색할 공간에 point를 평가했을 때 남은 공간엔 대해 많은 것을 알 수 있는 경우

### Two Pointers Example in LeetCode

#### Subarray Product Less Than K

> [LeetCode](https://leetcode.com/problems/subarray-product-less-than-k/)

N < 30000 이기 때문에 O(N^2)의 시간복잡도를 가지는 알고리즘을 사용해도 된다. 하지만 Two Pointers를 사용하면 O(N)의 시간복잡도를 가지는 알고리즘을 만들 수 있다.

i와 j는 0에서부터 시작하는데 j가 배열의 크기 보다 작고 product 결과가 K보다 작을 때까지 j를 증가시킨다. 그후 j가 i보다 크면 subarray의 개수를 j - 1 만큼 증가시키고 product를 i번째 값으로 나누고 i를 증가시킨다. 그래야 다시 계산할 필요없이 다음 i번째 값부터 j번째 값까지의 곱을 구할 수 있다. 그리고 맨 처음에 i가 j 보다 크면 j를 i로 바꾸고 product를 1로 초기화한다.

```c
int numSubarrayProductLessThanK(int* nums, int numsSize, int k){
    int ans = 0, prod = 1, j = 0
    for(int i = 0; i < numsSize; i++) {
      if (j < i) {
        j = i;
        prod = 1;
      }

      while (j < numsSize && prod * nums[j] < k) {
        prod *= nums[j++];
      }

      if (j > i) {
        ans += j - i;
        prod /= nums[i];
      }
    }
    return ans;
}
```

#### Container With Most Water

> [LeetCode](https://leetcode.com/problems/container-with-most-water/)

2개의 막대 사이에 물을 부어서 가장 많은 물을 담을 수 있는 경우를 찾는 문제이다. 이때 물의 양은 두 막대 중 더 작은 막대의 높이 * 두 막대 사이의 거리이다.

해당 문제는 narrow 방식으로 풀 수 있다. 두 막대 사이의 거리가 가장 큰 경우를 찾는 것이기 때문에 두 막대 중 더 작은 막대를 한칸씩 이동시키면서 물의 양을 계산하면 된다.

```c
#define min(a, b) ((a) < (b) ? (a) : (b))

int maxArea(int* height, int heightSize){
    int l = 0, r = heightSize - 1, ans = 0, area;

    while(l < r) {
      if(ans < (area = min(height[l], height[r]) * (r - l))) {
        ans = area;
      }
      if(height[l] < height[r]) {
        l++;
      } else {
        r--;
      }
    }
}
```