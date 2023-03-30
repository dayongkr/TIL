# EOF in Python

문제해결 플랫폼에서 몇 개의 줄을 받을지 입력을 받지 않으면 파일의 끝에 도달할 때까지 입력을 받습니다. 이를 위해 EOF를 사용해야 하는데 파이썬에서는 입력 받는 방식에 따라 다르게 처리해야 한다.

## input()

``` python
while True:
    try:
        line = input()
    except EOFError:
        break
    print(line)
```

input 내장 함수는 EOFError를 발생시킨다. 따라서 try except를 사용하여 EOF를 다루게 된다.

## sys.stdin.readline()

``` python
import sys
while True:
    line = sys.stdin.readline()
    if not line:
        break
    print(line)
```

하지만 시간 단축을 위해 보통 prompt 과정이 없는 readline을 사용하는데 이 경우 EOF를 다루는 방법이 다르다. readline은 빈 문자열을 반환하므로 try except가 아닌 조건문을 사용하여 EOF를 처리한다.
