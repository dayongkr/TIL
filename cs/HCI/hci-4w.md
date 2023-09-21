# HCI 개론 4주 차

## Interaction Elements

HCI의 요소인 controls, mapping, degree of freedom (DoF), conceptual model등을 다룬다.

### Controls

사용자가 시스템과 상호작용하는 방법이다. 이는 아래와 같이 분류할 수 있다.

- Hard controls
  - physical control
  - 한 번 만들어지면 바꿀 수 없는데 피드백이 잘 되어있다.
  - joystick, keyboard, etc
- Soft controls
  - virtual control
  - 유연하게 바꿀 수 있지만 피드백이 잘 되어있지 않다.
  - display, software, etc
- Control-Display relationship
  - control이 display와 어떻게 연결되어 있는지
  - 마우스를 왼쪽으로 움직이면 커서가 왼쪽으로 움직인다.
- Spatial relationship
  - control이 어떻게 배치되어 있는지
  - 마우스를 오른쪽으로 움직이면 커서가 오른쪽으로 움직이는데 마우스를 앞으로 움직이면 커서는 위로 움직인다.
    - 즉 다르게 매핑되어 있다.
    - 학습에 의해 익숙해지면 사용하기 쉽다.
  - DoF(Degree of Freedom) 즉 자유도는 조작할 수 있는 것들의 갯수이다.
    - x,y,z,roll,pitch,yaw 등이 있다.
    - 마우스 -> 2
- Control-Display Gain
  - control을 얼마나 움직여야 display가 얼마나 움직이는지
- Property Sensed
  - 어떠한 것을 감지하는지
  - 터치스크린 -> 손가락의 위치
  - 마우스 -> 움직임의 변화
  - touchpad -> 손가락의 위치
  - 즉 positon,displacement,force
- Order of Control
  - position control
    - 물체의 위치를 조절하는 것
  - velocity control
    - 물체의 속도를 조절하는 것
- Natural, Learned
  - 자연스러운 것과 학습을 통해 익숙해진 것
  - 다이얼을 오른쪽으로 돌리면 증가하는 것은 학습을 통해 익숙해진 것이고 마우스를 오른쪽으로 움직이면 커서가 오른쪽으로 움직이는 것은 자연스러운 것이다.
  - 문화에 따라 다르다.

### Mapping

## Fundamental Design Goals

- 좋은 mapping을 제공하기
  - 어떻게 control이 display와 연결되어 있는지를 나타낸다. 이는 라벨링이 잘 되어있어야 한다.
- 좋은 affordance을 제공하기
  - Affordance: 객체의 특성을 보고 어떻게 사용할 수 있는지 알 수 있는 것
    - 버튼은 누를 수 있다.
- Constraints를 사용하여 오류를 방지하기
  - Physical constraints
    - 물리적인 제약
    - 키보드의 키는 누를 수 있는데 누르지 않으면 눌리지 않는다.
  - Semantic constraints
    - 의미적인 제약
    - 키보드의 키는 누를 수 있는데 경험적으로 누르지 않는다.
  - Cultural constraints
    - 문화적인 제약
    - 문화에 따라 다르다.
  - Logical constraints
    - 논리적인 제약
- Metaphors를 사용하기
  - Metaphors: 사용자의 기존 경험을 통해 새로운 것을 이해하는 것을 도와주는 것
    - 너무 많이 사용하면 혼란을 줄 수
- 사용자가 올바른 conceptual model을 가지도록 하기
  - mental model: 사용자가 시스템에 대해 가지고 있는 모델
  - conceptual model: mental model 중 작동원리에 대한 모델
  - 예를들어 가위는 작은 구멍과 큰 구멍을 사용해서 손가락을 몇 개 넣어야 하는지 알 수 있도록 잘 매핑했고 2 개의 구멍만 있어서 동의 제약을 뒀고 날카로운 칼날, 잡을 수 있는 구멍들을 통해 어떠한 동작을 해야 하는지 알 수 있도록 했다. 즉 좋은 conceptual model을 가지고 있다.
- 생각과 시스템의 시스템의 작동이 잘 맞도록 하기, 볼 수 있도록 하기
  - Gulf of Execution
    - 어떠한 목적을 위해 얼마나 많은 동작을 해야 하는지
  - Gulf of Evaluation
    - 얼마나 잘 표현되어 있는지
