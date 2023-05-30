# 문제해결 13주 차 Reivew

## Weekly Problem Review

### Split Array with Same Average

> [문제 링크](https://leetcode.com/problems/split-array-with-same-average/)

저번 sum 문제와 유사한데 이번에는 average를 구하는 문제이다. 기존 문제에 elements의 개수를 추가하면 된다.

따라서 subproblem A\[k][j]로 정의하고 k개의 element를 사용해서 j를 만들 수 있는지를 저장한다. 이 때 base case는 A\[1]\[nums[i]] = true이다. 점화식은 다음과 같다.

- A\[k][j] = true if A\[k-1]\[j-nums[i]] is true

그리고 answer case는 dp 배열을 순회하면서 A\[i]\[j]가 true이고 sum \* (n-i) == j \* n이면 true를 반환한다.

비트마스크를 사용해서 풀 수도 있는데 이는 일단 건너뛰고 나중에 다시 풀어보는 것으로 하자.

### Maximum Value of K Coins From Piles

> [문제 링크](https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/)

이 문제는 piles에서 위에서 coin을 하나씩 빼서 얻을 수 있는 최대 점수를 구하는 문제이다.

subproblem은 A\[i]\[j] = i 번째 pile에서 j개의 coin을 빼서 얻을 수 있는 최대 점수로 정의한다. 따라서 점화식은 max(A\[i-1]\[j-c] + sum(piles\[i][0:c]))이다. 즉 piles에서 c개를 뽑아서 얻을 수 있는 최대 점수를 구하고 나머지는 A\[i-1]\[j-c]에서 구한다.

### Range Sum Query 2D - Immutable

> [문제 링크](https://leetcode.com/problems/range-sum-query-2d-immutable/)

이 문제는 2차원 배열에서 특정 범위의 합을 구하는 문제이다.

subproblem은 a\[i]\[j]는 0, 0부터 i, j까지의 합이라고 정의한다. 이 때 점화식은 a\[i]\[j] = a\[i-1]\[j] + a\[i]\[j-1] - a\[i-1]\[j-1] + matrix\[i]\[j]이다. 그 후 이렇게 구한 dp 배열을 적절히 사용해서 구간 합을 구하면 된다.
