# 문제해결 3주 차 Review

## weekly problem 해설

### [LeetCode] Roman To Integer

I, V, X, L, C, D and M과 같은 Roman numerals의 주어지면 decimal integer로 변환해라.

``` c
int map(char c)
{
  if (c == 'I')
    return 1;
  if (c == 'V')
    return 5;
  if (c == 'X')
    return 10;
  if (c == 'L')
    return 50;
  if (c == 'C')
    return 100;
  if (c == 'D')
    return 500;
  if (c == 'M')
    return 1000;
  return 0;
}
intromanToInt(char *s)
{
  int len = strlen(s), sum = 0;
  for (inti = 0; i < len; i++)
  {
    if (map(s[i]) < map(s[i + 1]))
      sum -= map(s[i]);
    else
      sum += map(s[i]);
  }
  return sum;
}
```

처음엔 각 문자를 숫자로 mapping 하는 함수를 만들고 만약에 문자 앞에 자기보다 작은 문자가 있으면 빼는 로직만 구현하면 된다.

### [LeetCode] Excel Sheet Column Number

columnTitle이 주어지면 해당 String을 Excel sheet의 column number로 변환해라.

``` c
int titleToNumber(char *columnTitle)
{
  int ans = 0;
  for (int i = 0; i < strlen(columnTitle); i++)
    ans = ans * 26 + (columnTitle[i] - 'A' + 1)
}
```

26진수 10진수로 변환하는 문제이다. 따라서 각 자리에 26^n을 곱해준 것을 서로 더하면 값이 나온다.

### [LeetCode] Longest Substring Without Repeating Characters

주어진 문자열 중 중복되는 문자가 없는 substring 중 가장 큰 substring의 길이를 구해라.

``` c
int check[128];
int lengthOfLongestSubstring(char *s)
{
  int left = 0, ans = 0;
  for (int i = 0; i < 128; i++)
    check[i] = 0;
  for (int right = 0; right < strlen(s); right++)
  {
    while (check[s[right]] && left < right)
      check[s[left++]]--;
    check[s[right]]++;
    if (right - left + 1 > ans)
      ans = right - left + 1;
  }
  return ans;
}
```

2 pointer를 사용해서 구현하는 데 매번 초기화하는 방식이 아니라 이중 반복문이지만 O(N)로 빠르게 수행할 수 있다.

> 반드시 Two loops라고 O(N^2)가 아니다.

### [LeetCode] Find the Index of the First Occurrence in a String

needle과 haystack string을 입력받고 haystack에 needle이 등장하는 index를 반환해라.

ASCII Code의 합이 같지 않으면 문자열이 같을 일이 없다는 사실을 사용하고도 좀 더 빠른 알고리즘을 구현할 수 있지만 최악은 O(NM)임은 변함없다.

matching을 사용한 KMP 알고리즘으로 예를 들어주셨다.

## Review

### Complexity of Algorithm

- big-oh(g)
  - g에 뭔가를 곱한 것보다 느리다.
  - 따라서 표현할 때 tight 하게 하는 게 중요하다.
- big-theta(g)
  - g와 똑같은 비율이다.
  - 증명할 게 많다 보니 잘 사용하지 않는다.
- big-omega(g)
  - g에 뭔가를 곱한 것보다 빠르다.

#### Guessing Complexity from Problem Size

입력의 크기를 보고 어떤 시간 복잡도까지 사용할 수 있을지 힌트를 얻을 수 있다.
