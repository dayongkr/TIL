# 문제해결 6주 차 Review

## Weekly Challenges

### Longest Mountain in Array

> [LeetCode] [845. Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/)

정수 배열 arr의 subarray중 가장 긴 산의 길이를 구하면 되는데 없으면 0을 반환하면 된다.

``` c
int longestMountain(int *arr, int arrSize)
{
  if (arrSize < 3)
    return 0;
  int ans, i, j;
  ans = i = 0;
  while (i < arrSize - 1)
  {
    int phase = 0;
    j = i;
    while (j < arrSize - 1)
    {
      if (!phase && arr[j] < arr[j + 1] ||
          phase && arr[j] > arr[j + 1])
        j++;
      else if (!phase && i < j && arr[j] > arr[j + 1])
      {
        phase = 1;
        j++;
      }
      else
        break;
    }
    if (i < j && phase)
    {
      if (j - i + 1 > ans)
        ans = j - i + 1;
      i = j;
    }
    else
      i++;
  }
  return ans;
}
```

### Maximum Score of a Good Subarray

> [LeetCode] [1742. Maximum Score of a Good Array](https://leetcode.com/problems/maximum-score-of-a-good-subarray/)

subarray의 score는 i~j의 요소 중 제일 작은 요소 * 요소 개수이다. 또한 a good array는 i <= k <= j를 만족하는 배열이다. 따라서 k를 포함하는 subarray의 maxium score를 구하면 된다.

```c
int maximumScore(int *nums, int numsSize, int k)
{
  int l, r, min = nums[k];
  int ans = min;
  l = r = k;
  while (min > 0)
  {
    int left_num = l > 0 ? nums[l - 1] : 0;
    int right_num = r < numsSize - 1 ? nums[r + 1] : 0;
    if (left_num > right_num)
    {
      if (min > left_num)
        min = left_num;
      l--;
    }
    else
    {
      if (min > right_num)
        min = right_num;
      r++;
    }
    if (min * (r - l + 1) > ans)
      ans = min * (r - l + 1);
  }
  return ans;
}
```

### Ways to Split Array into Three Subarrays

> [LeetCode] [1712. Ways to Split Array into Three Subarrays](https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/)

양수인 정수의 배열이 주어지면 이를 3개의 subarray로 나눌 수 있는 방법의 수를 구하면 된다. 단, 각 subarray의 합은 같아야 한다. left의 합이 mid의 합보다 작거나 같고 mid의 합이 right의 합보다 작거나 같아야 한다. 또한 비어 있지 않는 연속적인 subarray만을 고려해야 한다.

```c
int sum[100001];
int waysToSplit(int *nums, int numsSize)
{
  sum[0] = nums[0];
  for (int i = 1; i < numsSize; i++)
    sum[i] = sum[i - 1] + nums[i];
  int ans = 0;
  for (int l = 0, r_min = 0, r_max = 0; l < numsSize - 2; l++)
  {
    if (r_min <= l)
      r_min = l + 1;
    while (r_min < numsSize - 1 && sum[l] > sum[r_min] - sum[l])
      r_min++;
    if (r_max < r_min)
      r_max = r_min;
    while (r_max < numsSize - 1 && sum[r_max] - sum[l] <= sum[numsSize - 1] - sum[r_max])
      r_max++;
    ans = (ans + r_max - r_min) % 1000000007;
  }
  return ans;
}
```

## Sliding Window

Sum과 Mean은 간단하게 구현이 가능한데 Max와 Min은 따로 구현해야 한다.

### Sliding Window Max, Min

Deque를 이용하여 구현할 수 있는데 Deque는 양쪽에서 삽입과 삭제가 가능한 자료구조이다.

Deque의 front는 가장 큰 값이고 back은 가장 작은 값이다. 참고로 가운데는 2 번째로 큰 값이다. 이를 사용해서 front에서 빼면 가장 큰 값이고 back에서 빼면 가장 작은 값이다. 이렇게 자료구조를 사용하면 O(N)으로 구현이 가능하다.
