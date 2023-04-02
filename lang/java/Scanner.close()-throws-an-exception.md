# Scanner.close() throws an exception

자바프로그래밍실습에서 input을 받아야 할 부분이 있어서  `java.util.Scanner`를 사용하다가 문제가 생겼다.

## 문제

```java
public int[] inputCoord(String name) {
  int[] coord = { 0, 0 };
  Scanner scn = new Scanner(System.in);

  System.out.println(String.format("input %s x, y (0 ~ 14) :", name));
  coord[0] = scn.nextInt(); // x
  scn.nextLine(); // enter
  coord[1] = scn.nextInt(); // y
  scn.close(); // close scanner
  ...
  return coord;
  }
```

함수를 호출할 때마다 `Scanner`를 생성하고 `close()`를 호출해서 다시 반환하는 식으로 함수를 구현하고 이 함수를 총 4번 정도 호출해야 했다. 그런데 한 번 호출할 때는 정상적으로 입력이 받아졌지만 두 번째부터는 `java.util.NoSuchElementException`이 발생했다.

## 원인

사전에 생성자를 통해 표준 입력인 `System.in`을 사용한다고 정의했다. 그런데 Scanner.close()는 이와 같이 연관된 스트림까지 닫기 때문에 해당 Scanner와 연관된 `System.in`도 닫히게 된다. 그래서 두 번째 호출부터는 `System.in`이 닫혀서 입력을 받을 수 없게 되었기 때문에 Exception이 발생했던 것이다.

## 해결

``` java
public class board {
  Scanner scn = new Scanner(System.in);
  ...
  public int[] inputCoord(String name) {
    int[] coord = { 0, 0 };
    System.out.println(String.format("input %s x, y (0 ~ 14) :", name));
    coord[0] = scn.nextInt(); // x
    scn.nextLine(); // enter
    coord[1] = scn.nextInt(); // y
    ...
    return coord;
  }
}
```

`Scanner`를 클래스의 멤버 변수로 선언하고 나중에 게임이 끝나서 더 이상 System.in을 사용하지 않을 때 `Scanner.close()`를 호출하는 식으로 해결했다.
