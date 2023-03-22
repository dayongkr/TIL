# 자료구조개론 4주 차

## String pattern matching

C-libary에도 pattern matching 하는 함수 strstr이 있지만 이 함수의 동작 원리 및 효율적인 알고리즘이 무엇이 있는지 배운다.

### KMP

pattern을 사전에 조사해서 불필요하게 돌아 가지고 않고 쭉 나아가고자 만든 string pattern matching 알고리즘이다.

#### Failure Function

이 Pattern을 조사해서 해당 pattern 안의 문자들이 서로 겹치는 부분이 있는지를 조사하는데 이를 Failure Function이라고 한다. 이 함수는 pattern의 길이만큼의 배열을 만들고 이 배열의 각 원소는 해당 pattern의 인덱스를 의미한다. 이 배열의 각 원소는 해당 인덱스의 문자가 pattern의 처음부터 끝까지 일치하는 문자열의 길이를 의미한다.

> 문자열의 길이를 의미하게 만들 수도 있고 일치하는 인덱스를 의미하게 만들 수도 있다.

#### Pmatch

이제 위 Failure Function으로 Patter의 서로 겹치는 부분을 알 수 있는 table을 얻었으니 이 table을 가지고 string을 조사하면서 pattern과 일치하는 부분을 찾는 pmatch 함수를 만들 수 있다. 이 함수는 string의 길이만큼의 반복문을 돌면서 pattern의 길이만큼의 반복문을 돌면서 string과 pattern을 비교한다. 이때 pattern의 길이만큼의 반복문을 돌면서 string과 pattern을 비교할 때 pattern의 인덱스가 0이 아니고 string과 pattern이 일치하지 않으면 pattern의 인덱스를 failure function의 값으로 바꾸고 다시 string과 pattern을 비교한다. 이렇게 하면 pattern의 일부가 일치하는 부분을 건너뛰고 다음 인덱스부터 비교를 시작한다. 이렇게 하면 string의 길이만큼의 반복문을 돌면서 pattern의 길이만큼의 반복문을 돌면서 string과 pattern을 비교하는 것보다 효율적이다. 이렇게 만든 pmatch 함수는 string과 pattern이 일치하는 부분의 시작 인덱스를 return 한다.

## Quizs

### Quiz 10

Q. parms로 string, char을 받고 해당 string에 char이 몇 개 있는지 return 하는 strnchar 함수를 만드세요.

``` c
int strnchar(char *s, char p)
{
  int n = 0;
  for (int i = 0; s[i]; i++)
  {
    if (p == s[i])
      n++;
  }
  return n;
}
```

수업 내용에 비해 쉬운 문제였다.

### Quiz 11

주어진 3 strings의 failure function을 수행하라.

- aaaab
  - -1 0 1 2 -1
- ababaa
  - -1 -1 0 1 2 0
- abaabaab
  - -1 -1 0 0 1 2 3 4

### Quiz 12

pmatch() 안에 있는 while loop을 for loop으로 바꿔보시요.

``` c
int pmatch(char *string, char *pat)
{
  int lens = strlen(string);
  int lenp = strlen(pat);
  for (int i = 0, j = 0; i < lens && j < lenp;)
  {
    if (string[i] == pat[j])
    {
      i++;
      j++;
    }
    else if (j == 0)
      i++;
    else
      j = failure[j - 1] + 1;
  }
  return (j == lenp ? i - lenp : -1);
}
```
