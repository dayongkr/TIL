# C언어 기초

> 군대 전역 후 말하는 감자가 되어버렸다...
> 처음부터 다시 시작해보자🥲

이식성, 유연성, 효율성이 뛰어난 고급 언어이다.

따라서 보통 OS, compiler, high performance library, db 등 성능이 중요하거나 이식성이 필수적인 프로그램을 작성할 때 사용한다.

## Compilation process - 컴파일 과정

C언어와 같은 사람이 이해할 수 있는 고급언어를 기계가 이해할 수 있는 저급언어로 변환하는 과정으로 `Preprocessing > Compilation > Assembling > Linking` 순서로 수행된다.

### Preprocessing - 전처리

Preprocessing은 `#include`, `#define`과 부분을 처리하거나 주석을 삭제하고 특정 문자열을 다른 문자열로 바꾸는등 말 그대로 compile하기 전에 필요한 일들을 처리하는 과정이다.

### Compilation - 컴파일

Preprocessing을 거친 코드의 syntax analysis을 수행하고 error가 없으면 기계어로된 파일(*.s)을 생성한다.

### Assembling - 어셈블리

object file을 온전히 기계가 이해할 수 있는 binary code로 된 오브젝트 파일(*.o)을 생성한다.

### Linking - 링크

오브젝트 파일(*.o)을 모두 연결해 실행 파일을 만드는 과정이다.

## main function

프로그램이 시작될 때 호출되는 함수로 `entry-point function`(진입점 함수)라고 부른다.

``` c
int main(void) {...}
// 또는
int main() {...}
```

위와 같이 정의하는 것이 표준형이다.

``` c
void main(void) {...}
```

위와 같이 정의하는 경우도 있는데 이는 표준에 어긋나기 때문에 지양하자.
참고로 return type이 void가 아닌 이상 함수에는 `return value`이 필히 있어야 하지만 main 함수 같은 경우는 예외라서 적지 않아도 된다.
