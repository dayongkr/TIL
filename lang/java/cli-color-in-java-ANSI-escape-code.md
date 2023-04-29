# CLI에 컬러 입히기 in java - ANSI escape code

이번 자프실 PA2 과제에서 입력은 초록색으로 하고 출력은 검은색으로 하라는 조건이 있었다. 지금까지 CLI에 출력만 해봤지 색을 입힌 적이 없어서 어떻게 해야할지 몰랐다. 그래서 구글링을 해보았다.

## ANSI escape code

ANSI escape code란 터미널에서 색을 입히거나 커서를 이동시키는 등의 작업을 할 수 있게 해주는 코드이다. ANSI escape code는 다음과 같은 형식을 가진다.

```bash
ESC[<code>m
```

여기서 ESC는 escape character를 의미하며, `<code>`는 ANSI escape code를 의미한다. ANSI escape code는 다음과 같은 종류가 있다.

| Code  | Description          |
| ----- | -------------------- |
| 0     | Reset all attributes |
| 1     | Bold or Bright       |
| 2     | Dim                  |
| 3     | Italic               |
| 30-37 | Foreground color     |

우리는 출력을 초록색으로 하고 싶으므로 32를 사용하면 된다. 또한 출력을 검은색으로 하고 싶으므로 30 또는 0을 사용하여 리셋을 시켜주면 된다.

> ref. [ANSI escape code - Wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code)

## Java에서 ANSI escape code 사용하기

Java에서는 ANSI escape code를 사용하기 위해서는 다음과 같은 코드를 사용해야 한다.

```java
System.out.print("\u001B[32m");
System.out.println("Hello, World!"); // green
System.out.print("\u001B[0m");
System.out.println("Hello, World!"); // black
System.out.print("\033[0;32m");
System.out.println("Hello, World!"); // green
System.out.print("\033[0m");
System.out.println("Hello, World!"); // black
```

Java에서 ANSI escape code를 사용하기 위해서는 `\u001B` 또는 `\033`를 사용해야 한다. 그리고 그 뒤에 ANSI escape code를 입력하면 된다.

기본 color는 검정색이므로 굳이 검은색으로 입히지 않고 reset을 시켜주는 식으로 구현했다.
