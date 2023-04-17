# 자바프로그래밍실습 8주 차

## 예외처리 Exception Handling

예외가 발생하면 비정상적으로 중단되기 때문에 이를 처리하는 것이 중요하다. 이를 예외처리라고 한다.

종류는 크게 두 가지로 나뉜다.

- Checked Exception
  - Compile time에 확인할 수 있는 예외
    - FileNotFoundException -> 없는 파일을 열려고 할 때
- Unchecked Exception
  - Runtime에 확인할 수 있는 예외
  - e.g. 배열의 index가 범위를 벗어날 때

> Error는 시스템에 문제가 생겼을 때 발생하는 예외로 예외처리를 하지 않는다.

예외 또한 클래스이기 때문에 상속을 받을 수 있다. 따라서 예외를 처리할 때는 상위 클래스를 사용하면 된다.

### 예외처리 방법

``` java
try {
  // 예외가 발생할 수 있는 코드
} catch(Exception e) {
  // 예외가 발생했을 때 처리하는 코드
} finally {
  // 예외가 발생하든 안하든 무조건 실행되는 코드
}
```

이와 같이 예외처리를 할 수 있고 multiple catch를 통해 여러 예외를 처리할 수 있다.

### Throw

``` java
public static void main(String[] args) {
  try {
    throw new Exception("예외 발생");
  } catch (Exception e) {
    e.printStackTrace();
  }
}
```

예외를 발생시킬 때 사용한다.

### User Defined Exception

``` java
class MyException extends Exception {
  public MyException(String msg) {
    super(msg);
  }
}
```

직접 예외를 정의할 수 있다.

### Try with Resource

``` java
try(FileInputStream fis = new FileInputStream("file.txt")) {
  // ...
} catch (Exception e) {
  // ...
}
```

자동으로 close를 해주는 기능이다.
