# 시스템프로그램 8주 차 Review

## Weekly Quiz-6

- short A\[5][3] 시작 주소가 x에 있을 때 A[i]는?
  - x + 6i
- long integer A, index i 가 %rdx, %rcx에 있을 때 P + 4 + i를 계산하는 명령어는?
  - leaq 32(%rdx, %rcx, 8), %rax
- int B\[5][3]의 시작 주소가 600일 때 B\[3][1]의 주소는?
  - 640
- struct {char a; int b; short c; short \*d} rec4에서 d의 offset은? data alignment을 고려해야 함
  - 16 bytes
- struct {char a; int b; short \*d; short e;}rec5; 에서 struct의 전체 size는? data alignment을 고려해야 함
  - 24 bytes

## Mid-term Test Review

1번 문제는 기존에 PA1에서 나왔던 sign, unsigned integer 간의 type casting의 문제로 이를 decimal, binary value로 표현하는 문제였다. signed와 unsigned 연산을 하면 값은 unsigned로 나오는데 이를 놓친 것 같다.

2번 문제는 여러 표현식을 bit level로 표현되어 있는 표현식과 연결하는 문제였다.

3번 문제도 PA1에서 나왔던 FPN 문제인데 먼저 Format A로 Whole number을 구하고 이를 Format B으로 최대한 표현을 하고 표현이 되지 않으면 round to +inf로 표현하는 문제였다.

4번 문제는 swap하는 코드를 assembly code로 주고 이를 c언어 표현식으로 변환하는 문제였다. 포인터 변수인데 모르고 포인터 표현식으로 안 나타낸 것 같다.

5번 문제는 while loop을 assembly code로 주고 이를 c언어 표현식으로 변환하는 문제였다.

6번 문제는 structure의 data alignment을 고려해서 A,B가 가능한 값을 구하는 문제였다.
