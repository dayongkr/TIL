# 시스템프로그램 3주 차 Review

## Quiz

- 8-bit FP로 (exp 4-bit, frac 3-bit) 1.0을 binary로 표현하면?
  - 00111000
  - 1.xx 뒤에 다 0이므로 frac는 다 0이고 실제 지숫값은 0이어야 하므로 exp는 0 + bias(7) = 7(0111b)이다.
- 위와 같은 환경에서 00111110을 decimal value로 나타내면?
  - 8/8 + 6/8 = 7/4
- ❌ 32-bit single precision FP 표현의 the smallest positive normalized value는?
  - 1.0 x 2^-126
  - exp = 2^-126, frac = 0..00
- FP의 성질 중 사실인 것은
  - FP addition은 monotonicity를 만족한다.
  - NaN 제외
  - addition, multiplication은 associate 하지 않고 multiplication은 distribute over addition 하지 않는다.
- FP rounding modes 중 양수는 아래로 음수는 위로 round 하는 mode는?(|X'| <= |X|)
  - round-toward-zero

Review는 생략
