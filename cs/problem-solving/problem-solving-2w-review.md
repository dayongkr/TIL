# 문제해결 2주 차 REVIEW

## 2주 차 문제 해설

### Move Zeros

> [Move Zeros - LeetCode](https://leetcode.com/problems/move-zeroes/)

정수 배열 nums 에서 0을 찾아 뒤에 몰아넣어라.

``` c
void moveZeroes(int* nums, int numsSize) {
  int p = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i]) nums[p++] = nums[i];
  }
  for (; p < numsSize; p++) nums[p] = 0;
}
```

nums[i]가 0이 아니면 nums[p++]에 대입해서 앞에서부터 0이 아닌 수를 차곡차곡 쌓은 후 마지막에 남은 공간은 0으로 채우는 방식으로 해결하셨고 in place 방식으로 해결하셨다.

시간 복잡도는 O(N)이다.

> in place: 추가 자료구조 없이 문제를 해결하는 방법

### Single Number

> [Single Number - LeetCode](https://leetcode.com/problems/single-number/)

정수 배열 nums 에는 숫자 하나를 제외하곤 다 2번씩 등장하는데 이때 혼자인 숫자를 찾아라.

> 단, 선형 시간 복잡도와 상수 공간 복잡도를 사용해라

``` c
#define OFFSET 30000
int arr[OFFSET * 2 + 1];
int singleNumber(int* nums, int numsSize){
  for(int i = 0; i < OFFSET * 2 + 1; i++) arr[i] = 0;
  for(int i = 0; i < numsSize; i++)
    arr[nums[i] + OFFSET]++;
  for(int i = 0; i < OFFSET * 2 + 1; i++)
    if(arr[i] == 1) return i - OFFSET;
  return 0;
}
```

위 문제 해결 방법은 너무 비효율적이고 XOR 게이트를 사용하면 효율적으로 풀 수 있다. (bit가 같으면 0 다르면 1을 return)

> XOR 연산자는 교환, 결합 법칙이 성립한다.

```c
int singleNumber(int* nums, int numsSize) {
  for (int i = 1; i < numsSize; i++) nums[0] ^= nums[i];
  return nums[0];
}
```

예를 들어 3 ^ 5 ^ 3 ^ 2 ^ 2는 교환 법칙으로 3 ^ 3 ^ 2 ^ 2 ^ 5 와 같고 결합 법칙과 self inverse로 인해 결국 5만 남게 된다. 이를 활용하면 O(N), in place 방식으로 풀 수 있는 문제였다.

### Maximum Subarray

> [Maximum Subarray - LeetCode](https://leetcode.com/problems/maximum-subarray/)

정수 배열 nums의 Subarray 중 가장 큰 Sum 값을 구해라.

직관적으로 비교하게 되면 O(N^2) 또는 O(N^3) 시간 복잡도가 발생하므로 timeout이 발생하므로 위와 같이 O(N)으로 풀어야한다.

``` c
#include <limits.h>
int maxSubArray(int* nums, int numsSize) {
  int max_sum = INT_MIN, sum = 0;
  for (int i = 0; i < numsSize; i++) {
    if (sum > 0) sum += nums[i];
    else sum = nums[i];
    if (sum > max_sum) max_sum = sum;
  }
  return max_sum;
}
```

오른쪽으로 나아가면서 더하다가 sum 값이 0보다 작게되면 sum 값을 nums[i] 값으로 초기화하고 만약에 sum 값이 max_sum 보다 크다면 max_sum을 sum으로 초기화 하는 코드이다. 이와 같이 문제를 푼다면 시간복잡도 O(N)으로 풀 수 있다.

### Majority Element

> [Majority Element - LeetCode](https://leetcode.com/problems/majority-element/)

정수 배열 nums 에서 가장 많이 등장하는 element를 구해라.

> 단. Majority element는 배열 크기 n/2개 이상 등장한다.

결국 과반수인 수를 찾는 Boyer-Moore Voting algorithm을 사용하는 문제이다.

#### Boyer-Moore Voting

ME에 영향을 끼치지 않는 배열에 있는 요소들을 없애서 문제를 작게 만드는 것이 주된 아이디어이다. 결국 요소들을 비교하면서 없애나간다.

- 만약에 a1, a2가 서로 다르면 둘 다 없애도 ME에는 영향이 없다.
  - a1이 ME이거나 a2가 ME여도 ME에 영향이 없고 둘 다 ME 가 아니어도 영향이 없으니 둘 다 없애도 된다.
- 만약에 a1, a2가 서로 같으면 다른 수를 가진 2개의 요소를 더 찾아서 삭제해도 ME에는 영향이 없다.

따라서 반복문을 통해 nums 을 선형 탐색하면서 candidate와 같으면 count를 +1 다르면 -1을 하고 만약에 count가 0이라면 candidate를 해당 요소로 바꾸면 된다.

``` c
int majorityElement(int* nums, int numsSize) {
  int count = 0, candidate = 0;
  for (int i = 0; i < numsSize; i++) {
    if (count == 0) candidate = nums[i];
    count += candidate == nums[i] ? 1 : -1;
  }
  return candidate;
}
```

따라서 위와 같이 구현되었다.

## 시간 복잡도

이미 다른 수업에서 한번 자세히 다뤘다.

- Worst-case time
  - 계산하기 편해서 제일 많이 사용하는 time complexity
- Average time
- Best-case time
  - 거의 사용하지 않는다
