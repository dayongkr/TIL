# 문제해결 9주 차

## Recursion Advanced

### 언제 recursion을 사용해야 할까?

- 수열을 계산하는데 recursive definition이 주어졌을 때
  - 같은 케이스를 여러번 반복해서 계산해서 시간적 손해
  - stack frame 제한에 걸린다.
  - 위 2가지 이유로 dp를 사용해야 할 수 있다.
- 완전 탐색 (Exhaustive Search) 문제
  - 모든 경우의 수를 다 해보는 문제
  - e.g. combinations와 permutations을 다 해보는 문제
- data structure를 traverse하는 문제
  - e.g. 이진트리를 traverse하는 문제, flood fill(on a graph)
    - 이진트리의 subtree도 이진트리이기 때문에 recursion을 사용하기 좋다.
- 문제를 두 개의 작은 subproblem으로 나누는 문제
  - e.g. merge sort, quick sort
  - divide and conquer

### Recursion의 제한

- Repetition
  - 같은 문제를 여러번 푸는 경우
  - memoization을 통해 해결할 수 있다.
- Call stack overflow
  - recursive function call의 깊이가 너무 깊어지는 경우
- Excessive search space
  - 탐색할 수 있는 공간이 너무 커지는 경우
  - pruning을 통해 해결할 수 있다.

#### Repetition

Fibonacci 수열을 계산하는 함수에서 이 같은 경우가 발생한다. 예를 들어 F(10)을 구하면 F(9)와 F(8)을 구해야 한다. 그런데 F(9)를 구할 때 F(8)을 구하는 과정이 중복된다. 이런 경우를 repetition이라고 한다.

이런 경우를 해결하기 위해 memoization을 사용한다. memoization은 계산한 값을 저장해두었다가 다시 계산하지 않도록 하는 기법이다. 이를 통해 repetition을 해결할 수 있다.

구현은 간단한데 배열을 선언하고 해당 배열을 -1로 초기화한다. 그리고 함수를 호출할 때마다 배열에 값을 저장해두고 해당 값이 -1이 아니라면 저장된 값을 반환하도록 한다. 이렇게 하면 한 번 계산한 값을 다시 계산하지 않게 된다.

다만 2개 이상의 인자의 조합을 통해 계산하는 경우에는 배열을 2차원 이상의 multidimensional 배열로 선언해야 한다.

### Pruning

LeetCode의 문제 중 Target Sum를 예로 Pruning을 설명하셨다. 해당 문제는 n개의 nums 배열과 integer인 target이 주어지는데 nums 배열의 원소들을 더하거나 빼서 target을 만들 수 있는 경우의 수를 구하는 문제이다.

이는 Test(nums, n, i, target) = Test(nums, n, i+1, target - nums[i]) + Test(nums, n, i+1, target + nums[i])로 표현할 수 있다. 또한 stop condition은 i == n일 때이다. 이때 target이 0이면 1을 반환하고 아니면 0을 반환한다. 되게 오래 걸리는 코드인데 pruning을 통해 시간을 단축할 수 있다.

남아 있는 nums 배열의 원소들을 모두 더해도 target을 만들 수 없다면 더 이상 탐색할 필요가 없다. 또한 남아 있는 nums 배열의 원소들을 모두 빼도 target을 만들 수 없다면 더 이상 탐색할 필요가 없다. 이를 통해 시간을 단축할 수 있다.

### Common Mistakes

- memoization에서 배열을 0으로 초기화하는 경우
  - 만약에 해당 문제에서 0이 정답이라면 0으로 초기화하면 안된다.
- problem size를 줄이지 않는 경우
  - stop condition에 확실히 닿을 수 있도록 한다.
- Stop condition을 잘못 설정하는 경우
  - 잘못 설정하여 skip이 발생할 경우 Stack Overflow가 발생할 수 있다.
- Recursion이 stop condition 앞에 오는 경우
  - stop condition을 먼저 설정하고 recursion을 호출한다.
- Memo를 할당 해놓곤 사용하지 않는 경우
  - memo를 할당하고 사용하지 않으면 메모리를 낭비하게 된다.

### Example

#### Flood Fill

> [LeetCode 733. Flood Fill](https://leetcode.com/problems/flood-fill/)

m\*n grid image에서 주어진 좌표의 색을 newColor로 바꾸고 주어진 좌표와 인접한 좌표들 중 색이 같은 좌표들을 모두 newColor로 바꾸는 문제이다. 이는 recursion을 통해 dfs로 해결할 수 있다.

> 4방향만 고려하면 된다.

같은 방식이라도 여러 표현으로 구현할 수 있는데 일단 가고 확인하는 코드와 가기 전에 확인하는 코드로 구현할 수 있다. 또한 반복문을 사용하여 구현할 수 있다.

시간복잡도는 O(m\*n)이고 즉 O(N^2)이다. 만약에 BFS로 구현하고 싶다면 queue를 사용하면 된다.

#### N-Queens II

> [LeetCode 52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)

n\*n board에서 n개의 queen을 놓는 경우의 수를 구하는 문제이다. queen은 가로, 세로, 대각선으로 이동할 수 있다. 따라서 각 queen은 같은 행, 같은 열, 같은 대각선에 있을 수 없다. 이 또한 recursion을 통해 해결할 수 있다.
