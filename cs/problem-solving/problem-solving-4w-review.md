# 문제해결 4주 차 Review

## Weekly Challenges Week 5 Review

### 134. Gas Station

> [[LeetCode]134. Gas Station](https://leetcode.com/problems/gas-station/)

2개의 정수 배열(gas, cost)가 주어지는데 gas는 해당 gas station에 도착 했을 때 주유할 수 있는 gas의 양, cost는 해당 gas station에서 다음 gas station까지 갈 때 소모되는 gas의 양이다. 이때 한 바퀴를 돌 수 있는 시작점을 찾아서 리턴하라. 시작점이 없다면 -1을 리턴하라.

``` c
int canCompleteCircuit(int *gas, int n, int *cost, int costSize) {
  int sum = 0;
  for (int i = 0; i < n; i++) sum += gas[i] - cost[i];
  if (sum < 0) return -1;

  int start;
  sum = -1;
  for (int i = 0; i < n; i++) {
    if (sum < 0) {
    sum = 0;
    start = i;
    }
    sum += gas[i] - cost[i];
  }

  return start;
}
```

index 0부터 시작해서 실패하면 해당 index 앞부터 다시 시작하는 방식으로 풀 수 있다.

### 402. Remove K Digits

> [[LeetCode]402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

non-negative integer인 string type의 num 변수와 integer type k 변수가 주어지는데 k개의 digits을 제거하여 얻을 수 있는 가장 작은 수를 리턴하라.

``` c
char *removeKdigits(char *num, int k) {
  int len = strlen(num);

  int non_zero = 0;
  for (int i = 0; i < len; i++) if (num[i] != '0') non_zero++;
  if (non_zero <= k) return "0";

  char *ans = (char *)malloc(sizeof(char) * len);

  int j = 0, target_len = len - k;

  ans[0] = num[0];
  for (int i = 1; i < len; i++) {
    while (j >= 0 && ans[j] > num[i] && k) j--, k--; 
    ans[++j] = num[i];
  }

  ans[target_len] = 0;

  for (; *ans == '0'; ans++); // find the first non zero char

  return ans;
}
```

idea는 digits 앞에 더 큰 수가 있으면 제거하는 식으로 넘어간다.

만약에 non-zero numbers을 지울 수 있으면 result는 0, Trailing zeros를 제거해주는 부분이 필요하다.

### 350. Intersection of Two Arrays II

> [[LeetCode]350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

2 integer array가 주어지는데 이 arrays의 intersection을 리턴하라. intersection은 중복된 숫자를 포함한다.

> order는 상관이 없다.

``` c
#define LIMIT 1000
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize) {
  int count[LIMIT + 1];
  int *ans = (int *)malloc(sizeof(int) * max(nums1Size, nums2Size)), len = 0;
  for (int i = 0; i <= LIMIT; i++) count[i] = 0;
  for (int i = 0; i < nums1Size; i++) count[nums1[i]]++;
  for (int i = 0; i < nums2Size; i++)
  if (count[nums2[i]] > 0)
  {
    count[nums2[i]]--;
    ans[len++] = nums2[i];
  }
  *returnSize = len;
  return ans;
}

```

counting을 이용해서 풀 수 있다.

