# 문제해결 9주 차 Review

기말에는 중간때와 같이 코딩테스트 느낌으로 하는데 1 ~ 2번 문제는 동일하게 나올 예정이고 나머지 두 문제는 Recursion과 DP문제가 나온다 한다.

## Weekly Probelm Solution

### Letter Tile Possibilities

> [Leet Code 1079. Letter Tile Possibilities](https://leetcode.com/problems/letter-tile-possibilities/)

n 개의 tiles가 주어지는데 tiles는 알파벳으로 이루어져 있다. 이 tiles로 만들 수 있는 모든 경우의 수를 구하는 문제이다. 이때 tiles의 length는 1~7로 제한된다.

---

모든 경우의 수를 구하는 것으로 recursion으로 구할 수 있다는 힌트를 얻을 수 있다. 이때 여러가지 방법이 있다.

1. 모든 문자열을 만들고 중복 검사를 한다.
2. 위와 비슷하지만 string을 정수로 mapping하여 좀 더 효율적인 중복 검사를 한다.
3. 각 알파벳의 frequency를 세고 이를 이용하여 문자열을 생성하면 중복 검사를 하지 않아도 된다.
4. 수학적으로 푸는 방법인데 수식은 n! / arr[0]!_arr[1]!_...\*arr[25]! 이다.

4번 문제는 현실적으로 코딩테스트에서 사용하기 어렵고 3번 또는 2번 방법을 사용하는 것이 좋다.

### Number of Ways of Cutting a Pizza

> [Leet Code 1444. Number of Ways of Cutting a Pizza](https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/)

사각형 피자를 2차원 배열로 주어지는데 요소가 'A'이면 사과가 올라가 있고 . 이 있으면 비어 있는 조각을 의미한다. 또한 정수형 k가 주어지는데 이는 피자를 k번 자를 것이다. 이때 피자를 k번 자르는 경우의 수를 구하는 문제이다. 이때 피자는 반드시 사과가 있는 조각이 하나 이상 있어야 한다.

---

가로 세로로 각각 잘라서 모든 경우의 수를 테스트 해본다. 함수의 형태는 cut(row, column, k)로 row 혹은 column을 1 씩 줄이고 k도 1을 줄이면 남은 부분을 또 자르는 식으로 재귀적으로 구현할 수 있다. 이때 재귀적으로 구현할 때 메모이제이션을 사용하면 더 빠르게 구현할 수 있다.

### Wildcard Matching

> [Leet Code 44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)

string s와 pattern p가 주어지는데 pattern p는 \*와 ?를 포함한다. 이때 string s가 pattern p와 매치되는지 확인하는 문제이다. 이때 \*는 모든 문자열을 의미하고 ?는 한 문자를 의미한다.

---

?와 일반적인 character은 손쉽게 구현이 가능하지만 \*는 어디까지 나아갈지 알 수 없기 때문에 모든 경우의 수를 확인해야 한다. 이때 재귀를 사용하면 된다. 또한 간혹 \*이 연속으로 나오는데 이는 사전에 하나로 합치는 것이 좋다. 또한 memoization을 사용하면 더 빠르게 구현할 수 있다.
