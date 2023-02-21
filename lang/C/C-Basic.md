# C언어 기초

> 군대 전역 후 말하는 감자가 되어버렸다... 처음부터 다시 시작해보자🥲

이식성, 유연성, 효율성이 뛰어난 고급 언어이다.

따라서 보통 OS, compiler, high performance library, db 등 성능이 중요하거나 이식성이 필수적인 프로그램을 작성할 때 사용한다.

## Compilation process

C언어와 같은 사람이 이해할 수 있는 고급언어를 기계가 이해할 수 있는 저급언어로 변환하는 과정으로 `Preprocessing > Compilation > Assembling > Linking` 순서로 수행된다.

### Preprocessing

Preprocessing은 `#include`, `#define`과 부분을 처리하거나 주석을 삭제하고 특정 문자열을 다른 문자열로 바꾸는등 말 그대로 compile하기 전에 필요한 일들을 처리하는 과정이다.

### Compilation

Preprocessing을 거친 코드의 syntax analysis을 수행하고 error가 없으면 기계어로된 파일(*.s)을 생성한다.

### Assembling

object file을 온전히 기계가 이해할 수 있는 binary code로 된 오브젝트 파일(*.o)을 생성한다.

### Linking

오브젝트 파일(*.o)을 모두 연결해 실행 파일을 만드는 과정이다.

