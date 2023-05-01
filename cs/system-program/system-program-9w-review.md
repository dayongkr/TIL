# 시스템 프로그램 9주 차 Review

## Quiz

- stack randomization은 linux에서 standard practice가 되었는데 이는 ()로 알려진 상위 개념 중 하나이다. 이는 여러 데이터들의 주소를 항상 다른 위치에 저장한다.
  - ASLR
- 주소가 0Xffffb754 ~ 0xfffd754를 가진다. 이 때 우리가 256-byte nop sled로 buffer overflow를 수행할 때 최소한 모든 starting address를 test 하기 위해 몇 번을 시도해야 하는가?
  - 범위는 2^13이다.
  - 답은 2^13 / 256(2^8) = 2^5 = 32번이다.
- float data를 long data로 변환해주는 instruction은?
  - vcvtss2siq
- C 코드와 assembly code를 주고 함수의 argument 중 하나의 data type을 구하는 것
  - float
  - 연산을 위해 vcvtsi2ssq로 변환했기 때문에 float이다.
  - 또한 연산에서 vaddss를 사용했기 때문에 float을 확정지음
- assembly code를 주고 c 코드의 빈칸을 채우는 문제
  - 교안에 있던 내용으로 -x이다.
  - FP constant와 XOR 연산을 통해 -x를 구하는 문제

Example은 정리 생략
