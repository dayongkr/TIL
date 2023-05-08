# 시스템프로그램 10주 차 Review

Assignment 02에 대한 리뷰를 진행하셨다. 하지만 이미 구글에 Solution이 많아서 일단 정리는 생략한다.

## Review

### Canary Value

Canary Value 있게 compile을 하면 처음에 stack을 기존보다 더 많이 잡은 후 밑에서 부터 buffer을 저장하고 그 위에 canary value를 집어 넣는다. 그 후 instruction에는 canary value를 확인하는 코드를 추가한다. 이렇게 하면 buffer overflow가 발생하면 canary value가 변하게 되고 이를 확인해서 buffer overflow를 감지할 수 있다.

### FP Operations

float -> double, double -> float로 바꿀 때 2 쌍의 instruction을 사용해서 바꾼다는 사실을 알아두는 것이 좋다.

double 및 float과 같은 실수를 return 할 때에는 %xmm0을 사용하는데 첫 번째 인자도 %xmm0을 사용하기 때문에 만약에 첫 번째 인자가 있다면 다른 xmm register에 copy해서 사용해야한다.

#### FP convert

일단 기본적으로 vcvt prefix 다음에 si, ss, sd이 나오고 2 다음에도 si, sd, ss, siq이 나온다. 이때 첫 번째 인자는 source, 두 번째 인자는 destination이다.

### Optimization

지금까지 이 단원읇 배우기 위해 공부한 것으로 매우 중요한 단원이라고 볼 수 있다.

Optimization은 여러 시도를 통해 진행하게 된다. 이 과정에서 생각처럼 optimization이 안될 수 있고 이는 data path를 그려보면서 뭐가 문제인지 찾아야 한다.
