# C에서의 입출력

C에서는 `<stdio.h>` 헤더 파일에 있는 `printf`, `scanf` 함수를 사용하여 출력과 입력하게 된다.

## 출력

``` c
#include <stdio.h>

int main(void) {
  printf("Hello");
}
```

앞서 설명한 것과 같이 printf 함수를 사용해서 출력하게 되는데 위와 같이 문자열을 Argument(인수)에 넣어주면 된다.

### Format specifier(서식 지정자)

printf는 다른 여타 언어들과 같이 Format specifier 기능이 있다.

``` c
// 앞으로 include, main 함수 정의 생략
printf("%d", 10); // 10
```

위와 같이 문자열 안에 `%d`와 같은 Format specifier를 넣고 다음 인수에 value를 넣어서 사용하면 된다.

위 예시는 정수값을 문자열 안에 넣고 싶을 때 사용하는 Format specifier이다.

- %d
  - 정수를 10진수로 출력
- %f, %F
  - 실수를 부동소수점 표기 방식으로 출력
- %c
  - 문자 출력

> 이외에도 다양한 서식 지정자가 있지만 주로 사용되는 것만 정리!

그리고 위 Format specifier에 숫자를 붙이면 문자의 폭과 소수점 이하 자릿수를 설정할 수 있다.

먼저 넓이는 서식 지정자 사이에 원하는 넓이를 적으면 된다.

``` c
printf("%3d",3) // 출력:  3
printf("%-3d",3) // 출력:3
```

그러면 위와 같이 숫자만큼 넓이를 설정하게 되고 위 코드는 오른쪽 정렬, 아래 코드는 왼쪽 정렬을 하는 것을 볼 수 있다.

``` c
printf("%.2f", 0.333) // 출력:0.33
printf("%6.2f", 0.333) // 출력:  0.33
```

소수점 이하 자릿수는 사이에 . + 원하는 자릿수를 적으면 원하는 자릿수 초과하는 건 버리고 이하만 출력되게 된다.

. 앞에 숫자를 적으면 앞서 설명한 넓이와 똑같은 기능을 하게 된다.

## 입력

보통 C언어의 입력이라 하면 `scanf`를 떠올리기 십상인데 `scanf`는 입력받는 문자를 모두 저장하려고 하므로 `buffer overflow`가 발생할 수 있어서 최대로 받을 크기를 설정할 수 있는 `scanf_s`를 사용하는 것이 좋다. 

다만 C를 알고리즘 과제 및 감 잡는데 공부하고 있고 `scanf_s`는 Vs Studio에서 지원하는 기능인데 본인은 Vscode를 사용하고 있으므로 패스!!

어쨋든 `scanf`를 사용해서 입력을 받을건데 `printf`와 매우 유사하므로 쉽다.

``` c
int a;
scanf("%d", &a);
```

위와 같이 인수에 서식 지정자, &변수 순으로 작성을 하면 끝!

> 문자를 입력 받을 땐 앞서 말한 `buffer overflow`를 조심하자!

Format specifier은 출력과 동일하므로 저장할 변수 앞에 & 연산자를 붙이는 것만 기억하면된다.

> `&변수`에서 & 연산자는 변수의 주소를 반환하는 연산자이다.