# 컴퓨터구조개론 proj1 과제 후기

컴퓨터구조개론 proj1 과제를 수행하면서 겪은 문제들 또는 배운 부분을 정리해보았다. 단 아직 과제 제출 전이라서 아쉽지만, 코드는 미포함하고 최대한 간략하게만 정리했다. 나중에 코드가 궁금하면 지금은 private 상태로 있지만 졸업 후 public으로 돌릴 skku-assignment repo를 참고하면 될 것 같다.

## Assignment description

``` zsh
inst 0: 001230b7 lui x1, 1191936
inst 1: 0007b117 auipc x2, 503808
inst 2: 7f90f1ef jal x3, 65528
inst 3: 12c28267 jalr x4, 300(x5)
```

proj1 과제는 RV32I을 기반으로 된 binary file을 disassemble하여 instruction을 위와 같이 stdout을 하는 과제였다.

언어는 c, c++, python으로 제한되어 있었고 7개의 테스트 케이스가 있고 이에 해당하는 결과들도 text file로 제공되었다.

### How to solve

간단하게 로직을 설명하자면 다음과 같다.

1. binary file을 열고 4 byte씩 읽는다.
2. little endian에 맞게 hex로 변환하고 binary로도 변환한다.
3. opcode로 format을 구분한다.
4. format table을 dicitionary로 만들어서 opcode와 funct로 operand를 구분한다.
5. 흩어진 immediate를 하나로 모으고 MSB에서 sign bit를 가져와 sign extend한다.
6. rd,rs1,rs2도 구한다.
7. format type에 맞게 출력한다.

## proj1 과제를 수행하면서 겪은 문제 및 배운 점

### Python

뭔가 각 잡고 python을 공부한 적도 없고 python을 많이 다룬 적이 없다 보니깐 python의 기본적인 문법이나 내장 함수들을 아직 많이 모르고 있기 때문에 과제를 하면서 많은 부분을 공부할 수 있었다.

#### Open and read binary file

일단 binary file을 열고 읽어야 과제를 시작할 수 있었는데 당연히 파이썬에서 파일을 열고 읽는 방법을 모르고 있었기 때문에 시작부터 막혔다.

파일을 열려면 open 함수를 사용하면 되고, 파일을 읽으려면 read 함수를 사용하면 된다. 그리고 파일을 읽을 때 4 byte(32 bits) 단위로 읽기 위해서 read 함수의 인자로 4를 넣어주었다.

open 함수를 사용하고 나서 다 쓰면 close를 해야 memory leak과 file lock을 방지할 수 있기 때문에 close 함수를 사용하는 게 좋다. 하지만 with as 구문을 사용하면 close를 따로 해주지 않아도 되기 때문에 실수를 방지할 수 있다.

#### Reverse list

``` python
list[::-1]
list[1:3][::-1]
```

python에는 reverse를 할 수 있는 방법이 3가지 있지만 slicing notation을 사용하는 방법이 가장 간단하다. 또한 slicing notation을 두 번 써서 일부만 reverse 할 수도 있다.

#### f-string

``` python
x = 1
y = 2
print(f"x: {x}, y: {y}"); // x: 1, y: 2
```

f-string은 python 3.6부터 지원되는 기능으로 문자열 앞에 f를 붙이고 중괄호 안에 변수를 넣어주면 변수의 값을 문자열에 넣어준다. 기존에는 format 함수를 사용했었는데 f-string을 사용하면 더 간단하게 문자열을 만들 수 있다.

#### CLI argument

``` python
import sys
print(sys.argv)
```

python에서 cli argument를 받아오는 방법은 sys.argv를 사용하면 된다. sys.argv는 list로 되어있고 첫번째 인자는 실행한 파일의 이름이고 두 번째 인자부터는 cli argument가 들어있다. 만약 cli argument가 없다면 sys.argv는 빈 list가 된다.

#### Class

``` python
class A:
    def __init__(self, x):
        self.x = x

    def print(self):
        print(self.x)

a = A(1)
a.print() // 1
```

python에서 class를 사용하는 방법은 위와 같다. __init__ 함수는 생성자로서 class를 생성할 때 호출되는 함수이다. self는 class의 인스턴스를 가리키는데 self.x = x는 class의 x라는 변수에 x라는 값을 넣어주는 것이다. 조심할 점은 class내 모든 함수의 첫번째 인자는 self여야 한다는 것이다.

> class 명을 정할 때는 대문자로 시작하는 것이 관례이다.

#### Destructuring assignment

``` python
a, b = [1, 2]
print(a) // 1
print(b) // 2
```

python에서 destructuring assignment를 사용하면 list나 tuple의 값을 각각의 변수에 할당할 수 있다. 위의 예시에서는 list의 첫번째 값이 a에, 두 번째 값이 b에 할당된다.

> js에서도 destructuring assignment이 있기 때문에 이해하기 편했다.

#### Conditional expressions aka Ternary Operator

``` python
a = 1 if True else 2
print(a) // 1
```

Python에도 삼항 연산자가 있다. if 뒤에 있는 부분이 조건을 적는 부분인데 해당 조건이 참일 경우 앞에 있는 값이 할당되고 거짓일 경우 뒤에 있는 값이 할당된다.

#### List multiplication

``` python
a = [0] * 4
print(a) // [0, 0, 0, 0]
```

python에서 list를 초기화 할 때 list comprehension을 사용하는 방법도 있지만 위와 같이 list를 곱하는 방법도 있다. 다만 list multiplication는 single element만을 가진 list에만 사용할 수 있다.

#### isinstance

``` python
a = []
print(isinstance(a, list)) // True
```

python에서 isinstance 함수를 사용하면 해당 변수가 해당 타입인지 확인할 수 있다. 위의 예시에서는 a가 list인지 확인하고 있다.

### Linux cli

테스트 케이스부터 과제 제출까지 인의예지 linux 서버로 과제를 진행했기 때문에 linux cli를 사용해야 했다. linux cli를 사용하면서 알게된 명령어들을 정리해보았다.

#### scp

``` bash
sudo scp -P {port} {file path} {user}@{ip}:{file path} # upload
sudo scp -P {port} {user}@{ip}:{file path} {file path} # download
```

scp는 secure copy의 줄임말로 ssh를 사용해서 호스트간 파일을 주고 받기 위해 사용하는 명령어이다.

#### ssh

``` bash
ssh -p {port} {user}@{ip}
```

ssh는 secure shell의 줄임말로 원격 호스트에 접속하기 위해 사용하는 명령어이다.

#### xxd

``` bash
xxd {file path} # binary to hex
xxd -r {file path} # hex to binary
xxd -p {file path} # hex to ascii
```

xxd는 hexdump의 줄임말로 파일을 hex 형태로 보여주는 명령어이다. -r 옵션을 사용하면 hex를 binary로 변환해준다. -p 옵션을 사용하면 hex를 ascii로 변환해준다.

### 겪은 문제점

#### Little endian

RISC-V는 little endian으로 memory에 저장하므로 binary file을 읽어서 instruction을 disassemble 할 때 little endian으로 읽어야 한다. 그래서 처음에는 big endian으로 읽어서 instruction을 disassemble 하려고 했는데 이렇게 하면 instruction이 제대로 disassemble 되지 않았다.

하지만 처음에는 이게 little endian 문제인지 모르고 계속 삽질하다가 hex 값을 비교해보니 2 bytes 씩 뒤집으면 기댓값과 일치하는 것을 확인할 수 있었다.

#### 32 bits

결국 binary로 변환해야 어떤 instruction인지 확인할 수 있다 보니 위 little endian을 거치고 난 hex 문자열을 int 내장 함수로 decimal 정수로 바꾸고 bin 내장함수로 binary로 바꿨다.

bin 내장함수는 0b로 시작하는 binary string을 반환하는데 이때 0b를 제거해주기 위해 [2:]를 붙여주었다. 또한 bin 내장함수는 유효한 bit만 반환하기 때문에 32 bits로 맞춰주기 위해 앞에 0을 채워 주어야 했다. 이를 위해 string 내장 함수인 zfill를 사용했다.

## 마치며

Class를 사용하고자 Class로도 만들다가 정상적으로 돌아가는 코드를 굳이 Class로 만들 필요가 없다고 생각해서 중간에 중단해서 의미 없이 Class를 사용해서 객체지향 개념을 좀 더 공부해서 의미있는 코드를 작성해야겠다.

또한 구현에 급급해서 만들다보니 불필요한 코드들이 보여서 최대한 불필요한 코드를 줄이고 의미있는 코드를 작성하려고 노력했다.

앞으로 코드 스타일에 대한 공부를 해서 좀 더 깔끔하고 읽기 쉬운 코드를 작성할 수 있도록 노력해야겠다.
