# HCI 7주 차

## Modeling interaction

실제 상황을 단순화해서 모델링한다. HCI의 대표적인 모델은 Descriptive model, predictive model이 있다.

### Descriptive model

problem space의 일부분으로 나누어 설명하고자 할 때 사용한다.

- KAM(Key Action Model)
  - keyboard의 keys들을 분류해서 설명한다.
  - Symbol key, excuptive key, modifier key
- Model of Bimanual control
  - 두 손을 사용하는 상황을 모델링한다.
  - Non-preferred hand, preferred hand
  - Non dominant hand, dominant hand
- Three-state Model for Graphical Input
  - Out of Range, Tracking, Dragging이 있다.

### Predictive model

사용자의 행동을 예측하고자 할 때 사용한다.

- Variable
  - Dependent variable
    - 예측하고자 하는 변수
  - Independent variable
    - 예측에 사용되는 변수
- Linear regression
  - y = ax + b
  - a: slope
  - b: intercept
  - R^2: coefficient of determination
    - 0 ~ 1
    - 1에 가까울 수록 예측이 잘 된다.
- Fitts's Law
  - Target의 거리 D와 Target의 크기 S를 이용해서 예측한다.
  - T = I \* log2(2D/S)
    - I = -(Tp + Tc + Tm) / log2(e)
  - ID: index of difficulty
    - ID = log2(2D/S) | log2(A/W + 1)
  - D가 작고 S가 크면 ID가 작아져서 좋은 상황이다.
- Hick's Law
  - 선택할 수 있는 대상의 개수 N과 선택하는데 걸리는 시간 T를 이용해서 예측한다.
  - T = a + b \* log2(N + 1)
  - 따라서 선택해야 하는 대상을 그룹으로 묶어서 개수를 줄이는 것이 좋다.
- KLM (Keystroke Level Model)
  - 키보드를 사용하는데 걸리는 시간을 예측한다.
  - T = K + P + H + M + R + D
    - K: key press
    - P: pointing
    - H: home | keyboard와 mouse를 바꾸는데 걸리는 시간
    - M: mental preparation
    - R: system response
    - D: draw
  - 계산 방법
    - R 다음에 M이 오면 R과 M을 합친다.
    - string이 parameter이 아닐 경우에는 중간에 있는 M은 무시한다.
- Skill Acquisition
  - Tn = T1 \* n^(-a)
    - Tn: nth trial time
    - T1: first trial time
    - n: number of trials
    - a: constant (0.2 ~ 0.6)
  - a를 역수로 하면 speed도 예측할 수 있다.
