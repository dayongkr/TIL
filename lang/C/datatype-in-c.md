# C의 데이터형

C의 `data type`은 크게 3가지로 나뉜다.

- 기본 데이터형
  - 문자형
  - 정수형
  - 실수형
- 파생 데이터형
  - 배열
  - 포인터
- 사용자 정의형
  - 구조체
  - 공용체
  - 열거체

## 기본 데이터형

앞서 말한 것처럼 `primitive data type`에는 문자형, 정수형, 실수형이 있다.

각 `data type`은 담을 수 있는 `data size`가 다르기 때문에 이를 유의해서 프로그래밍을 짜야지 아님 `overflow`가 발생한다.

### 정수형

정수형은 `signed`, `unsigned`라는 개념이 존재하는데 부호 있고 없고 차이이다.

따라서 부호가 없는 것을 뜻하는 `unsignend`를 `data type` 앞에 적게 되면 음수는 포함 안하기 때문에 같은 size라도 약 2배 크기의 숫자를 표현할 수 있다.

부호가 있는 `signed` 같은 경우에는 `most significant bit`(최상위 비트)를 sign bit로 사용해서 2배 차이가 나는 것이다.

> sign bit가 1이면 음수, 0이면 양수



#### Data size

|데이터형|크기|
|-|-|
|char|1byte|
|short|2byte|
|int|4byte|
|long|4byte|
|long long|8byte|

다만 위의 크기는 `Win32` 또는 `Win64` 기준으로 플랫폼에 따라 `size`은 다르지만 크기 차이 순서는 항상 동일하다.

