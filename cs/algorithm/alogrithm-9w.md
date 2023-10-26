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

### SRTBOT

MIT 강의에서 나온 recursion을 위한 framework이다.

1. subproblem을 정의한다.
2. recurrence를 정의한다.
3. topological order를 정의한다.
4. base case를 정의한다.
5. original problem을 정의한다.
6. time complexity를 계산한다.

Fibonacci sequence를 예로 들어보자.

1. subproblem을 정의한다.
   1. F(i) = i번째 Fibonacci number (1<= i <= n)
2. recurrence를 정의한다.
   1. F(i) = F(i-1) + F(i-2)
3. topological order를 정의한다.
   1. i는 증가하는 순서대로 계산한다.
4. base case를 정의한다.
   1. F(1) = 1, F(2) = 1
5. original problem을 정의한다.
   1. F(n)
6. time complexity를 계산한다.
   1. T(n) = T(n-1) + T(n-2) + O(1)
   2. T(n) = O(2^n)
   3. 단. memoization을 사용하면 n \* O(1) additions을 하기 때문에 O(n)이 된다.

merge sort도 SRTBOT으로 풀 수 있는데 merge sort는 이전 값들을 사용하지 않기 때문에 memoization이 도움이 되지 않는다.

### Good subproblems

subproblem을 정의할 때에는 아래 3가지를 고려해야 한다.

- prefix: x[:i] O(n)
- suffix: x[i:] O(n)
- subsequence: x[i:j] O(n^2)
