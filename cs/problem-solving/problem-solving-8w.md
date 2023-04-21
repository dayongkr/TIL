# 문제해결 8주 차

CS 학부생으로써 abstraction, recursion, types는 반듯이 알아야 할 3가지 개념이라고 교수님이 말씀하셨다. 그중 recursion을 이번 수업에서 다루게 되었다.

## Recursion

끝이 나야 하기 때문에 stop condition을 반듯이 명시해야 한다. 어쨋든 이렇게 계속 호출하다가 stop condition을 충족해서 return을 하게 되면 그때부터 자신을 호출한 함수에게 return value을 주면서 돌아가게 된다.

이를 사용하면 top-down 방식으로 문제를 해결할 수 있다. 또한 반복문 보다 코드가 간결해지고 이해하기 쉬워진다.

Recursion으로 문제를 해결하려면 가장 작은 문제의 답 즉 base case를 알아야 한다. 또한 P(n)을 더 작은 문제로 나누어서 표현할 수 있어야 한다.

```c
// P(n) := n!
// P(0) = 1
// P(n) = n * P(n-1)

int f(int n) {
  if(n == 0)  return 1; // base case
  return f(n - 1) * n; // p(n) = n * p(n-1)
}
```

다만 대놓고 basecase와 표현 방식을 알려주지 않기 때문에 이를 알아내는 것이 key point이다.

### Example of Recursion

#### Tower of Hanoi Problem

3 rods(A,B,C)가 있고 n개의 크기가 다른 disks가 있는데 이를 몇 개의 Rule을 지키면서 다른 rod로 옮기는 문제이다.

- Rule
  - 한 번에 하나씩 옮길 수 있다.
  - rod의 top에서만 뺄 수 있고 다른 rod의 top에만 넣을 수 있다
  - 작은 disk는 큰 disk 위에 놓을 수 없다.

결국 우리는 제일 큰 disk를 rod C에 옮겨야 한다. 그리고 그 순간에는 모든 디스크들은 rod B에 있어야 한다.

위 사실을 통해 P(n, from, via, to) = P(n-1, from, to, via) + move disk n to rod to + p(n-1, via, from, to); 라는 식을 도출할 수 있다.

#### Genrating Strings

a,b,c로 이루어진 n개의 문자열을 만드는 문제이다. 이를 반복문으로 구현을 할 수 있지만 그렇게 되면 n이 바뀔 때마다 반복문을 직접 추가해야 하기 때문에 코드가 길어진다. 이를 재귀적으로 구현하면 코드가 간결해진다.

```c
char a[10] = "";
int f(int n) {
  if(n == 0){
    printf("%s\n", a);
    return;
  }
  else {
    a[n-1] = 'a';
    f(n-1);
    a[n-1] = 'b';
    f(n-1);
    a[n-1] = 'c';
    f(n-1);
  }
}
```

위와 같이 하면 일단 맨처음엔 aaaa가 출력대고 그다음 순서인 aaab 그 다음인 aaac와 같이 모든 경우의 수가 출력된다.

#### Find K-th Bit in N-th Binary String

> [LeetCode 1545. Find Kth Bit in Nth Binary String](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/)

양수인 정수 n, k가 주어지는데 S(n)은 S(n-1) + 1 + reverse(invert(S(n-1)))이다. 여기서 S(1)은 0이다. 이때 S(n)의 k번째 bit를 구하는 문제이다.

이는 재귀적으로 풀 수 있다. 다만 full string을 구하지 않고도 풀 수 있다. 일단 S(n)의 length는 2^n - 1이다. 그리고 가운데 2 ^ (n-1)에는 무조건 1이 들어가므로 k가 해당 값이면 1을 return 해당 값보다 작으면 find(n-1,k)를 하고 크면 reverse하고 invert한 값이어야 하므로 find(n,k) = 1 - find(n-1, 2^n - k)이다. 1 - find 부분은 invert 하는 부분 2^n - k는 rverse 하는 부분이다.

이를 코드로 구현하면 다음과 같다.

```c
char findKthBit(int n, int k) {
  if (n == 1) return '0';
  int i = 1 << (n - 1);

  if (k < i) return findKthBit(n - 1, k);
  else if (k == i) return '1';
  else return '0' + '1' - findKthBit(n - 1, 2 * i - k);
}

참고로 마지막에 1 - find 부분이 '0' + '1' - find로 되어 있는데 이는 ASCII 코드 기준으로 연산을 하고자 '0'을 추가하여 return 값도 '0'과 '1'이 되도록 했다.
```

### Predict the Winner

> [LeetCode 486. Predict the Winner](https://leetcode.com/problems/predict-the-winner/)

> two players, optimal play, winner prediction은 recurison 또는 dp를 사용하라는 힌트가 될 수 있다.

해당 문제는 정수 배열이 주어지면 2 플레이어는 양쪽에서 숫자를 하나씩 뽑아서 더하고 더 큰 사람이 이기는 게임이다. 이때 두 플레이어가 최선을 다해서 게임을 진행한다고 할 때 첫번째 플레이어가 이길 수 있는지 판단하는 문제이다. 시작은 첫 번째 플레이어이다.

앞에서 시작했을 때랑 뒤에서 시작했을 때 두가지 경우로 나누어서 계산한 후 둘 중에 하나라도 player 1이 이기면 true를 return하면 되기 때문에 두 계산의 결과 중 큰 값을 기준으로 return하면 된다.

그리고 turn이라는 변수를 두어서 turn이 1이면 결과에 더하고 -1이면 결과에서 빼서 결국 결과가 0보다 크면 player 1이 이기고 0보다 작으면 player 2가 이기는 것이다.

```c
#define max(a, b) (((a) > (b)) ? (a) : (b))
int predict(int* nums, int s, int e, int turn) {
  if(s == e) return turn * nums[s];

  int a = turn * nums[s] + predict(nums, s + 1, e, -turn);
  int b = turn * nums[e] + predict(nums, s, e - 1, -turn);

  return turn * max(turn * a, turn * b);
}

bool PredictTheWinner(int* nums, int numsSize){
  return predict(nums, 0, numsSize - 1, 1) >= 0;
}
```
