# 자료구조개론 4주 차

## String pattern matching

C-libary에도 pattern matching하는 함수 strstr이 있지만 이 함수의 동작 원리 및 효율적인 알고리즘이 무엇이 있는지 배운다.

### KMP

pattern을 사전에 조사해서 불필요하게 돌아가지고 않고 쭉 나아가고자 만든 string pattern matching 알고리즘이다.

#### Failure Function

이 Pattern을 조사하기 위해 Failure Function을 만들었다. 이 Failure Function은 같은 pattern이 앞에 없으면 -1이고 앞에 비슷한 pattern이 있으면 해당 인덱스를 테이블에 저장해둔다. 이 또한 사진을 보면서 예시를 참고하는 것이 좋아서 교안을 참고하는 것이 좋을 것 같다.

#### Pmatch

이제 위 Failure Function으로 pattern을 조사하고 있는 pmatch 함수를 알아보자. 이 함수는 string과 pattern을 받아서 string에 pattern이 있는지 없는지를 판단한다. 이 함수는 string의 인덱스를 i, pattern의 인덱스를 j라고 하고 i와 j가 각각 string과 pattern의 길이보다 작을 때까지 while loop을 돌면서 string[i]와 pattern[j]가 같으면 i와 j를 1씩 증가시키고 다르면 j가 0이면 i를 1 증가시키고 아니면 j를 failure[j-1] + 1로 바꾼다. 이렇게 하면서 j가 pattern의 길이와 같아지면 pattern이 string에 있었다는 것이고 i - lenp를 return한다.

## Quizs

### Quiz 10

Q. parms로 string, char을 받고 해당 string에 char이 몇개 있는지 return하는 strnchar 함수를 만드세요.

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
