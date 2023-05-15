# 시스템프로그램 11주 차 Review

## Weekly Quiz

- 예측하면서 fetching과 decoding 하는 것은?
  - speculative execution
- 앞선 부분으로 code를 움직여서 자주 연산되지 않도록 하는 것은?
  - code motion
- pointer aliasing 문제로 xp와 yp가 같은 값을 때 x의 값은?(swap 함수)
  - 0
- 반복문 조건문 안에 있는 함수가 실행되는 횟수는?
  - 40
- reassociation을 했을 때 multiplication의 CPE는? (문제가 상당히 길음)
  - 2.5

### 3번 문제

```c
// Swap value x at xp with value y at yp
void swap(long *xp, long *yp) {
  *xp = *xp + *yp;
  *yp = *xp - *yp;
  *xp = *xp - *yp;
}
```

위 코드에서 xp와 yp가 같은 것을 가르킨다고 가정하고, x의 값은? (0)
