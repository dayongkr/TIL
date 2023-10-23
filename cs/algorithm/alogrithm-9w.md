# 알고리즘개론 9주 차

## Worst-case linear-time selection

1. n개의 원소를 5개씩 그룹으로 나눈다. -> O(n)
2. 각 그룹에서 중간값을 찾는다. -> O(n)
3. 중간값들의 중간값을 찾는다. -> T(n/5)
4. 중간값들의 중간값을 pivot으로 하여 partition을 한다. -> O(n)
5. pivot의 index를 i라고 하면 -> T(7n/10 + 6)
   1. i = k이면 pivot을 return한다.
   2. i > k이면 pivot의 왼쪽 부분을 재귀적으로 찾는다.
   3. i < k이면 pivot의 오른쪽 부분을 재귀적으로 찾는다.

즉 T(n) = O(n) + T(n/5) + T(7n/10 + 6)이다. 이를 substitution method를 이용해서 계산하면 T(n) = O(n)이다.

## Dynamic programming

마케팅 텀으로 dynamic이 붙은 거지 제일 중요한 부분은 이미 계산 했던 부분을 다시 계산하지 않도록 memoization을 하는 것이다.

대표적인 예로 LCS가 있는데 이는 가장 긴 공통 부분 수열의 길이를 구하는 알고리즘이다. 이를 구하는 방법은 다음과 같다.

1. x[i] = y[j] 이면 c[i][j] = c[i-1][j-1] + 1
2. x[i] != y[j] 이면 c[i][j] = max(c[i-1][j], c[i][j-1])

만약에 가장 긴 공통 부분 수열 자체를 구하고 싶으면 x[i] = y[j]일 때마다 stack에 넣고 나중에 stack을 pop하면 된다.
