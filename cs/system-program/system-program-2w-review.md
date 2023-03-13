# 시스템 프로그램 2주 차 Review

## 퀴즈

- 98을 8bit binary number로 변환하라
  - 01100010 간단한 이진 변환
  - 2^6 + 2^5 + 2
- 100을 8-bit 2's complement binary number로 변환하고 hex로도 보여라
  - 10011100, 0x9C
  - MSB는 -로 생각하고 다 더하면 변환하기 쉬움
- 10bit signed integer에서 2's complement로 encoding 한 negative integers의 최솟값은?
  - -512
- 6bit 머신에서 2's complement를 사용하는데 ux 변수의 최종 결과는?
  - int x = -14; unsigned ux = x;
  - ux == 50
- 5bit 머신에서 2's complement를 사용하는데 sum 변수의 최종 결과는?
  - int x = 8, y= 12, sum; sum = x + y;
  - 01000 + 01100 ==  10100 == -16 + 4 == -12
  - sign bit을 햇갈려서 틀림

## Review

- 한글은 어떻게 표현하나?
  - 예전에는 조합형, 완성형 등이 있었으나 현재는 전 세계 언어들을 표준코드로 표준화한 UNICODE(UTF-8)를 사용해서 표현하기 때문에 3 bytes(24 bits)로 표현하게 되었다. 다만 문자별로 가변으로 byte를 사용한다.
  - e.g. a => 1byte, 가 => 3byte
- Early Evaluation을 한 번 더 짚고 넘어가심
  - e.g. p && *p++: p가 NULL이면 오른쪽은 연산하지 않기 때문에 작동한다
- 오른쪽으로 shift 하면 숫자는 절반이 됨(소수점은 버림)
- 요즘은 2's complement를 사용하므로 이것만은 꼭 기억
- 2진수 <-> 10진수, Signed <-> Unsigned, Expansion/truncation 예제를 같이 품!
  - unsigned char c = 500; unsigned short s = c; unsigned short는 255까지 표현할 수 있으므로 제일 큰 비트 256이 날아가므로 s는 244이다.
