# 문제해결 12주 차 Review

## Weekly Quiz

### Perfect Squares

> [LeetCode](https://leetcode.com/problems/perfect-squares/)

정수 n이 주워지면 perfect square numbers의 합으로 n을 만들 수 있는 최소 개수를 구하는 문제이다.

square number i를 만들 수 있는 최소 개수는 `dp[i] = min(dp[i], dp[i - j * j] + 1)`로 구할 수 있다.

### Partition Equal Subset Sum

> [LeetCode](https://leetcode.com/problems/partition-equal-subset-sum/)

정수 배열 nums가 주어지면 배열을 두 개의 부분집합(서로의 합이 같은)으로 나눌 수 있는지를 구하는 문제이다.

> 발표한 문제

### Longest Palindromic Subsequence

> [LeetCode](https://leetcode.com/problems/longest-palindromic-subsequence/)

string s를 주어지면 s의 subsequence 중 가장 긴 palindrome의 길이를 구하는 문제이다.

이차원 배열을 사용하여 i~j를 포현하여 palindrome의 길이를 구할 수 있다. 이때 i, j가 같을 경우 A\[i][j] = A\[i + 1][j - 1] + 2, i, j가 다를 경우 A\[i][j] = max(A\[i + 1][j], A\[i][j - 1])로 구할 수 있다.

이 또한 이전 결과가 다음 결과에 영향을 주기 때문에 큰값부터 작은 값으로 구해야 한다.

> palindrome: 앞으로 읽으나 뒤로 읽으나 같은 string
