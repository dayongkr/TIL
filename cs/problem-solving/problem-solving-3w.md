# 문제해결 3주 차

## Input and Output

제일 low level은 read(), write() 함수가 있는데 이를 활용해서 좀 더 편하게 만든 함수들이 scanf()와 printf()이다.

> 이처럼 미리 정의된 유용한 함수들을 standard functions라고 한다.

### Useful Header Files

- stdio.h
  - standard input and output operations
- math.h
  - mathematical operations
- string.h
  - string operations
- stdlib.h
  - standard library for general functions

### scanf

``` c
int scanf(const char * format, argument list);
```

보다시피 scanf는 return type이 void가 아니다. scanf는 몇 개의 char를 입력받았는지 return을 해준다. 따라서 입력받은 수가 0인지 아닌지를 확인할 수 있다.

만약에 입력이 "30   12.5 -5"와 같이 space가 여러 개 있더라도 그냥 30, 12.5, -5로 쪼개진다.

scanf는 overflow에 취약하기 때문에 간혹 특정 컴파일러들은 scanf를 컴파일하려고 하지 않는다.

### Format Specifiers

scanf에서는 간단한 format specifier를 사용하지만, printf 같은 경우에는 더 복잡한 specifier를 사용할 수 있다.

> %[flags][width][.precision][length]specifier

- specifier
  - %g: use the shortest representation
    - 392.65 instead of 392.65000
    - 유효숫자 최대 6개만 표현
  - %p: pointer address
  - %f
    - double이든 float이든 출력할 땐 사용 가능 다만 입력받을 땐 구별하기
- length
  - ll -> long long 입력
- .precision
  - 소수점 아래
- width
  - 출력 가로 길이
- flags
  - -: 왼쪽 정렬
  - +: 양수도 부호 출력
  - 0: 숫자 0으로 공백 채우기

``` c
printf("%+010.3f", 123.45678) // +00123.457
```

### consume '\n'

scanf와 fgets()는 \n을 가져가지 않기 때문에 다음번 입력에 \n이 들어가서 원치 않은 결과를 얻을 수 있다. 이를 해결하는 방법은 아래 3가지가 있다.

- Use sca nf("%d\n", &n);
- Use getchar() after scanf()
- Use fflush(stdin)

근데 각각의 문제가 있으므로 fgets(), sscanf() 함수의 조합으로 사용하는 게 안전하다. 먼저 fgets()로 \n까지 입력받고 sscanf()로 원하는 부분만 가져가면 된다.

또는 scanf("%d%\*c)를 사용해서 \n 문자를 가져가지만, 저장은 하지 않는 식으로도 처리할 수 있다. 다만 만약에 입력이 space 후에 \n이 오면 이미 %*c는 space를 지우는 데 사용됐으므로 \n은 또 소비가 안 된다.

## String

1 byte의 char의 배열로 string을 구성하고 ASCII Code를 사용한다는 내용을 얘기하셨는데 이는 다른 수업에서 익히 들은 내용이라 패스!

문자열끼리 대입과 비교는 당연히 안 된다!

``` c
char * fgets(char *str, int n, FILE * stream)
```

Whitespace 가 있는 문자열을 받으려면 fgets 함수를 사용해야 한다.

- str: copy 할 string pointer
- n: 카피할 최대 문자 수
- stream: FILE 객체 포인터가 들어가는데 콘솔에서 읽어 올 거면 stdin을 사용한다.

``` c
const char * str
```

위와 같이 const를 붙이게되면 해당 포인터에 있는 값을 수정하지 못하게 할 수 있다.

### Unicode

지구상에 있는 모든 문자를 정수로 Mapping한 것이 Unicode이다. 덕분에 한글, 한자, 이모지 등을 표현할 수 있다.

> ASCII Code와 호환이 된다.

컴퓨터로 저장할 수 있게 2진수로 변환하는 Encoding 과정이 필요한데 이를 Unicode Transformation Format 줄여서 UTF라고 한다. UTF는 가변적으로 1~4 bytes로 Encoding을 하며 UTF-8, UTF-16, UTF-32와 같이 나누어져 있다.

## Structure

``` c
struct pet {
  char name[10];
  char gender;
  int age;
}

pet dog = {"dog"}; // name 이외 0으로 초기화
pet cat = {0}; // 모두 0으로 초기화
pet pig; // 쓰레기값
```

위와 같이 초기화를 하나라도 해야 쓰레깃값을 피할 수 있다.

Sturcture도 비교가 되지 않지만, 복사는 가능하다. 물론 배열도 구조체 멤버라면 복사가 가능하다.
