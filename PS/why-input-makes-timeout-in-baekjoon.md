# input은 왜 백준에서 시간초과를 일으킬까?

파이썬 공식 문서에서 [input](https://docs.python.org/3/library/functions.html#input) 부분을 보면 그 이유를 알 수 있다.

input 같은 경우에는 parameter로 prompt message를 받고 이를 출력하는 과정이 포함되어 있다. parameter로 아무것도 안 주더라도 어쨌든 출력하는 과정도 포함되는 것이다.

input을 많이 호출하지 않으면 그다지 신경쓸 필요 없는 정도의 성능 이슈이겠지만 반복문을 사용해서 input을 많이 호출하는 경우에는 시간초과를 일으킬 것이다.

``` python
import sys
input = sys.stdin.readline
```

때문에 위와 같이 prompt message를 사용할 필요가 없을 때는 그냥 sys 모듈을 import 해서 sys.stdin.readline이라는 메소드를 input에 대입해서 사용하도록 하자.

readline 메소드 같은 경우에는 prompt message를 출력하는 과정이 없기 때문에 prompt message로 인한 시간초과 문제를 해결할 수 있을 것이다. 다만 input과 달리 개행 문자를 제거해주는 과정이 없기 때문에 문자열 그대로를 사용할 예정이라면 rstrip 메소드를 사용해서 맨 오른쪽에 있는 개행 문자를 제거해주자
