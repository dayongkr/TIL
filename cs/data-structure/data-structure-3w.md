# 자료구조개론 3주 차

## Array

### Sparse Matrix

단순히 2차원 배열을 만들다 보면 사용하지 않는 공간이 생겨서 공간 낭비가 생긴다. 이러한 배열을 Sparse Matrix라고 하는데 이를 해결하는 방법이 있다.

``` c
struct sparse {
  int row;
  int col;
  int value
};
```

수업에서는 row, col, value 값을 갖는 구조체(좌표와 값을 가진)를 만들고 해당 구조체로 배열을 만들어 빈 곳이 없도록 만들어서 이를 해결했다. 이를 Sparse Matrix representation이라고 한다.

### Transposing a Matrix

Sparse Matrix representation 방식으로 2차원 배열을 만들 때 보통 정렬을 하면서 저장한다. 따라서 Matrix의 row와 col을 transposing 하려면 col 기준으로 또 정렬하면서 col과 row의 값을 바꿔주면 된다. 참고로 row 기준으로 이미 정렬되었기 때문에 같은 col 값이 있더라도 위에서부터 진행하면 된다.

단순한 방법으로 위를 수행하려면 매번 완전 탐색을 해야 하지만 각 column의 개수를 알면 해당 col보다 작은 element가 몇 개 있는지 알고 있기 때문에 transpose하고 나서 넣을 자리를 알 수 있기 때문에 한 번 탐색으로 transpose가 가능하다.

### String

C에서는 String을 char의 배열로 표현한다.

#### String Function

- char \*strcat(char \*dest, char *src)
  - string concatination
- char \*strncat(char \*dest, char *src, int n)
  - src string의 n개 string만 잘라서 concatination
- int strcmp(char \*str1, char *str2)
  - string comparison
- int strncmp(char \*str1, char *str2, int n)
  - str1, str2의 앞에서 n개의 문자를 비교
- char \*strcpy(char \*dest, char *src)
  - dest에 src string을 copy
- char \*strncpy(char \*dest, char *src, int n)
  - src string 앞에서 n개 문자를 copy
- size_t strlen(char *s)
  - 문자열 길이
- char \*strchr(char *s, int c)
  - string에서 character가 있는 위치를 return
- char \*strtok(char \*s, char *delimiters)
  - delimiters 혹은 token이 나올 때마다 string을 자름
- char \*strstr(char \*s, char *pat)
  - strchr과 비슷한데 얘는 string의 위치
- size_t strspn(char \*s, char *spanset)
  - spanset에 없는 문자의 첫 위치 return
- size_t strcspn(char \*s, char *spanset)
  - spanset에 있는 문자의 첫 위치 return
- char \*strpbrk(char \*s, char *spanset)
  - strcspn과 동일한 기능이지만 pointer를 return

## Quiz

### Quiz 7

Q. 500x500 matrix가 있을 때 nonzero element가 몇 개 있을 때부터 기본 2-D array representation이 Sparse Matrix representation 보다 효과적일까?

A. int type은 C에서 4 bytes이므로 2-D array representation으로 500 * 500 matrix를 나타내려면 1,000,000 bytes가 필요하다. Sparse Matrix representation에서 구조체는 3개의 int data를 가지고 있으니 각 구조체는 12 bytes를 가지고 있기 때문에 nonzero element가 83,334개 있으면 1,000,008 bytes가 필요하므로 이때부터 2-D array representation이 더 효과적이다.

### Quiz 8

``` c
    for (i = 0; i < numCols; i++)
    {
      rowTerms[i] = 0;
    }
    for (i = 1; i <= numTerms; i++)
    {
      rowTerms[a[i].col]++;
    }
    startingPos[0] = 1;
    for (i = 1; i < numCols; i++)
    {
      startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }
```

위 코드는 Fast Matrix Transpose을 수행하는 코드의 일부분이다. rowTerms 없이 똑같이 작동하도록 만들어라.

``` c
startingPos[0] = 1;
for (i = 1; i < numCols; i++)
{
  startingPos[i] = 0;
}
for (i = 1; i <= numTerms; i++)
{
  startingPos[a[i].col]++;
}
for (i = 1; i < numCols; i++)
{
  startingPos[i] += startingPos[i - 1];
}
```

위와같이 startingPos를 재사용하면 된다.

### Quiz 9

i~j 부분을 제거해주는 string remove function을 구현해라. 아래와 같이 뼈대가 주어짐

``` c
void stringremove(char *s, int i, intj) {}
```

``` c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringremove(char *s, int i, int j)
{
  char *str = (char *)malloc(sizeof(char) * (strlen(s) + 1));
  str = strncat(str, s, i);
  str = strcat(str, s + j + 1);
  strcpy(s, str);
}
```

strncat으로 앞부분을 살리고 strcat과 pointer 사용으로 뒷부분을 살렸다.
