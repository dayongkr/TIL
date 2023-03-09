# 시스템 프로그램 2주 차

문자, 정수, 실수를 표현하고 조작하는 방법을 배우게 된다.

## Information Storage

이미 다른 강의에서 수업해서 Byte, Word에 대한 기초 설명은 패스!

|type|32-bit M| 64-bit M|
|-|-|-|
|char|1|1|
|short|2|2|
|int|4|4|
|😀 long|4|8|
|int32_t|4|4|
|int64_t|8|8|
|😀 char *|4|8|
|float|4|4|
|double|8|8|

32bit, 64bit 시스템은 서로 C 언어의 데이터 타입(long, char*)마다의 용량이 다를 수 있다.

### Byte ordering

메모리에 객체를 어떻게 저장할지 정하는 것이다.

- Little edian
  - LSB to MSB
  - e.g. 0x01234567 -> 01, 23, 45, 67
- Big endian
  - MSB to LSB
  - e.g. 0x01234567 -> 67, 45, 23, 01
  - 주로 사용하는 인텔 시스템에서 Byte ordering

### Strings

문자열 마지막은 NULL(Ox00)이고 ASCII 코드를 사용해서 표현한다. (숫자도 ASCII에 따라 표현한다.)

### Code

같은 코드이더라도 OS나 시스템이 다르면 다르게 나타낸다. 앞으로는 인텔 64bit 기준으로 배울 예정이다.

### Bit-level operations in C

- ~
  - NOT 연산자
- &
  - AND 연산자
  - masking을 위해서 많이 사용한다.
    - e.g. 0x1234ABCD & 0xFF = 0xCD
- |
  - OR 연산자
- ^
  - XOR 연산자

### Logical operations in C

&&는 둘 중의 하나가 0이면 0이므로 앞에 가 이미 0이면 뒤에는 계산할 필요가 없어서 하지 않으니 이를 조심해야 한다.

> 이를 Early Evaluation이라고 한다.

### Shift operations in C

- x << k
  - x를 k bits만큼 왼쪽으로 움직이는데 넘어가면 사라지고 비어 있는 공간은 0으로 채워지게 된다.
- x >> k
  - 위 연산자의 반대이지만 비어 있는 공간을 signed 같은 경우 맨 왼쪽에 있던 값으로(arithmetic right shift) 그리고 unsigned 같은 경우에는 0으로(logical right shift) 채워지게 된다.

## Integer Representations

C의 경우 limits.h 파일을 통해 각 데이터의 최소 최댓값을 알 수가 있다.

### Encoding unsigned integers

B2U(X)는 2^i * X[i]를 모두 더한 것과 같다. 범위는 [0, 2^w - 1]과 같다.

### Encoding signed integers

- Signed-magnitude (B2S)
  - MSB를 Sign bit로 사용해서 양수, 음수를 구분
  - 0의 표현이 2개이다.
  - floating-point numbers에서 일부 사용된다.
- 1's-complement (B2O)
  - MSB를 Sign bit로 사용
  - 1001 -> 0110, -6 -> 6 방식으로 변환
  - 0의 표현이 2개이다.
- 2' s-complement (B2T)
  - 0의 표현은 하나이다. 따라서 음수 하나를 더 표현할 수 있다.
  - ~x +1 == -x
  - 표현 범위는 [-2^(w-1), 2^(w-1)-1]이다.
  - 제일 많이 사용되는 표현 방법

### Type conversion (signed <-> unsigned)

#### unsigned -> signed

||Decimal|Binary|
|-|-|-|
|unsigned short x|2003|00000111 11010011|
|short ix = (short) x|2003|00000111 11010011|
|unsigend short y|47806|10111010 10111110|
|short iy = (short) y|-17730|10111010 10111110|

- x < 2^(w-1)일 땐 -> x
- x >= 2^(w-1)일 땐 -> x - 2^w

bit pattern은 유지되는데 signed number로 해석된다. 표현할 수 있는 공통된 부분은 그대로 유지되지만, 나머지는 음수 쪽으로 내려가게 된다.

#### signed -> unsigned

||Decimal|Binary|
|-|-|-|
|short ix|2003|00000111 11010011|
|unsigned short x = (unsigend short) ix|2003|00000111 11010011|
|short iy|-2003|10111010 10111110|
|unsigend short y = (unsigend short) iy|63533|10111010 10111110|

- x >= 0일 땐 -> x
- x < 0일 땐 -> x + 2^w

bit pattern은 유지되는데 unsigned number로 해석된다. 위와 달리 음 수부분이 공통부분 위로 올라가게 된다.

#### Type conversion in C

C에서는 이러한 과정들이 Explicit(명시적), Implicit(암시적) 두 방식 모두 작동하게 된다.

> e.g. (int) ux, tx = ux 각각 explicit와 implicit이다.

|Expression|Type|Evaluation|
|-|-|-|
|0 == 0U|unsigned|1|
|-1 < 0|signed|1|
|-1 < 0U|unsigned|0|

위와 같이 signed와 unsigned가 섞여 있는 연산은 Implicit 하게 unsigned로 바뀌므로 조심해야 한다.

### Expanding the bit representation

16bit -> 32bit 또는 32bit -> 64bit로 확장하는 방법을 의미한다.

- Zero extension
  - w bits -> w+k bits 일 경우 왼쪽 bit를 모두 0으로 채워주는 방식
- Sign extension
  - w bits -> w+k bits 일 경우 왼쪽 bit를 sign bit로 채워주는 방식

### Truncating for unsigned & signed

k보다 큰 w bits를 k bits로 변환하는 방법을 의미하는데, 상위 (w-k) bits만큼 떼어내 진다.

> 수식으로 나타내면 w mod 2^k이며 signed일 경우 맨 앞은 당연히 sign bit으로 취급한다.

### Example in c

``` c
strlen(s) - strlen(t) > 0 // 이렇게 사용하면 안 된다.
strlen(s) > strlen(t) // 옳은 사용 방법
```

위와 같은 코드를 작성하면 안 되는 이유는 strlen는 unsigned int return 하므로 만약에 t가 s보다 길이가 길 경우 원치 않은 결과를 얻을 수 있다.

``` c
#include <stdio.h>

int main()
{
  unsigned char c;

  while ((c=getchar()) != EOF) {
    putchar(c);
  }
}
```

EOF는 C에서는 int -1로 표현된다. 그런데 c 변수는 unsigned char라고 선언했기 때문에 c는 EOF를 다르게 저장하여 while 조건문이 항상 true가 되고 따라서 무한 반복되는 형상을 일으킬 것이다.

## 마무리

어쨌든 코딩할 때 unsigned, signed 등의 conversion을 조심하자. 예를 들어 unsigned인 data type에 0이 저장되어 있는데 여기에 -1 연산을 하면 원치 않은 결과를 얻을 수 있으니 조심하자.

따라서 음수를 가지지 않더라도 범위 문제가 생기지 않는 이상 굳이 unsigned로 선언하는 걸 지양하자. flag의 의미로 사용할 때는 unsigned를 사용해도 좋지만, 수치로 사용될 때 사용하는 건 추천하지 않는다. 따라서 대부분의 언어에선 unsigned를 지원하지 않는다.
