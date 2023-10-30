# 알고리즘개론 10주 차

오늘은 dp 문제 중 하나인 Knapsack problem에 대해서 알아봤다.

## Knapsack problem

Knapsack problem은 배낭에 물건을 넣을 때 최대의 가치를 가지도록 하는 문제이다.

### 0-1 Knapsack problem

0-1 Knapsack problem은 물건을 넣을 때 0개 또는 1개만 넣을 수 있는 경우이다.

1. subproblem을 정의한다.
   1. K(i, w) = i번째 물건까지 고려했을 때 w만큼의 무게를 넣을 수 있을 때 최대의 가치
2. recurrence를 정의한다.
   1. K(i, w) = max(K(i-1, w), K(i-1, w-wi) + vi)
3. topological order를 정의한다.
   1. i는 증가하는 순서대로 계산한다.
   2. w는 증가하는 순서대로 계산한다.
4. base case를 정의한다.
   1. K(0, w) = 0
   2. K(i, 0) = 0
5. original problem을 정의한다.
   1. K(n, W)
6. time complexity를 계산한다.
   1. T(n, W) = O(nW) (보통 O(n^2))

즉 넣을 수 있는 공간이 없으면 이전 값을 그대로 가져오고 넣을 수 있는 공간이 있으면 안넣는 경우와 넣는 경우 중 최대의 가치를 가져온다.
