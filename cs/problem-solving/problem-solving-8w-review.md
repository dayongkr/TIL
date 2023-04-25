# 문제해결 8주 차 Review

## Weekly Quiz 8w

### 1823. Find the Winner of the Circular Game

> [문제 링크](https://leetcode.com/problems/find-the-winner-of-the-circular-game/)

해당 문제는 ~/PS/LeetCode/Find-the-Winner-of-the-Circular-Game.md에 이미 따로 정리해놓았다.

#### 1823. Find the Winner of the Circular Game 해설

f(n, k)라고 두고 f(4, 2)에서 시작하면 0부터 시작하는데 f(5, 2)에서 시작하면 n이 4일 때 인덱스는 2이다. 즉 k만큼 뒤로 밀려있다. 이를 통해 점화식 f(n, k) = (f(n-1, k) + k) % n을 얻을 수 있다. f(1, k) = 0에서 base point를 얻을 수 있다.

### 1863. Sum of All Subset XOR Totals

> [문제 링크](https://leetcode.com/problems/sum-of-all-subset-xor-totals/)

정수 배열 nums에 있는 모든 subset의 XOR 값의 합을 구하는 문제이다.

#### 1863. Sum of All Subset XOR Totals 해설

subset을 bit mask를 통해 표현할 수 있다. 예를 들어 nums = [1, 3, 5]라면 0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111이 된다. 이때 0b001은 1을 포함하고 0b010은 3을 포함하고 0b011은 1과 3을 포함한다. 이를 통해 subset을 표현할 수 있다. 그렇게 구한 subset을 통해 XOR 값을 구하면 된다.

좀 더 익숙해지면 재귀를 통해 구할 수도 있다. 재귀를 통해 구할 때는 현재 인덱스의 값을 포함하는 경우와 포함하지 않는 경우로 나누어서 구할 수 있다.

### 60. Permutation Sequence

> [문제 링크](https://leetcode.com/problems/permutation-sequence/)

1~n까지 순열에서 k번째 순열을 구하는 문제이다. 예를 들어 n이 3일 때는 (1,2,3), (1,3,2), (2,1,3), (2,3,1)... 이 나오므로 k가 3일 때는 (2,1,3)가 나와야 한다.

#### 60. Permutation Sequence 해설

모든 경우의 수를 구하고 k 번째를 구하는 방법으로도 풀 수 있다. 생성된 string을 저장하는 str 배열, k번째까지 구하기 위한 count 변수, 해당 인덱스의 문자를 생성했는지를 확인하기 위한 used 배열, str[i]를 채우기 위한 perm(n,k,i) 함수를 만들어서 풀 수 있다.

### 1922. Count Good Numbers

> [문제 링크](https://leetcode.com/problems/count-good-numbers/)

여기서 말하는 good number란 홀수 자리에는 소수가 짝수 자리에는 짝수가 오면 good number라고 한다. 이때 문제는 n이 주어졌을 때 n 자리의 good number의 개수를 구하는 문제이다.

## Mid-term Review

기말은 1~2번 문제는 쉽거나 비슷하게 가고 3~4번 문제는 중간 이후로 배운 내용들이 들어갈 수 있다.

### 1번 문제 - 보석 세공

1. 무게를 10 늘리기
2. 순도를 5 늘리기
3. 복제하기

> 복제는 여러번 가능, 복제 후에는 세공 불가

모든 가능성을 고려해서 최댓값을 구하는 문제이다. 3번 작업은 무조건 마지막에 수행하는 것이 이득이다.

### 2번 문제 - 맛집

첫째 날을 0, 둘째 날을 1, 셋째 날을 2로 생각. 출력시 + 1

3일(a) 방문하지 않고, 4일(l) 방문한다면 d % (a+l) < a일 경우 방문하지 않고 d%(a+l) >= a 일 경우 방문한다. 즉 주기는 (a+l)이다. 주기가 18까지로 정해졌으므로 O(N)으로는 풀 수 있으니 d를 하나씩 증가시키면서 확인해도 된다.

### 3번 문제 - 던전 탐험

방의 개수가 최대 20개이고, 방문할지 안할지를 결정하므로 최대 2^20의 가지수가 존재한다. 2^20은 1,000,000이므로 완전 탐색으로 풀 수 있다.

방문하지 않으면 0 방문하면 1로 표시하여 bitmask를 이용하여 방문 여부를 확인한다. 따라서 bit를 만드는 부분과 이를 해석해서 점수를 매기는 부분을 나눠서 생각하면 될 것 같다.

### 4번 문제 - 어쨋든 등장

문자에서 query를 찾는 문제인데 k 간격 까지는 봐준다. 하지만 단순히 query의 각 문자가 text에 등장할 때 마다 매칭하면 틀린 경우가 발생한다. 아무도 푼 사람이 없어서 솔루션은 포함하시지 않으셨다.
