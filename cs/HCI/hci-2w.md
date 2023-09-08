# HCI 개론 2주 차

오늘은 인간의 특성에 대해 배웠다.

## Human Characteristics

### Newll's Time Scale of Human Action

| Scale(sec) | Time Units | System         | World(theory)   |
| ---------- | ---------- | -------------- | --------------- |
| 10^7       | Months     |                | Social Band     |
| 10^6       | Weeks      |                | SocialBand      |
| 10^5       | Days       |                | Social Band     |
| 10^4       | Hours      | Task           | Rational Band   |
| 10^3       | 10 min     | Task           | Rational Band   |
| 10^2       | Minutes    | Task           | Rational Band   |
| 10^1       | Seconds    | Unit Task      | Cognitive Band  |
| 10^0       | 1 sec      | Operations     | Cognitive Band  |
| 10^-1      | 100 ms     | Deliberate act | Cognitive Band  |
| 10^-2      | 10 ms      | Neural circuit | Biological Band |
| 10^-3      | 1 ms       | Neuron         | Biological Band |
| 10^-4      | 100 us     | Organelle      | Biological Band |

보통 HCI에서는 Social ~ cognitive band를 다룬다. 먼저 Cognitive Band는 가장 활발히 연구되는 부분으로 선택, 입력등을 다룬다. 그리고 Rational Band는 협업, 웹 서핑 등을 다룬다. 마지막으로 Social Band는 소셜 네트워크, 교육등을 다룬다.

### Human Factors Model

인간과 컴퓨터가 1대1 대응을 한다면 CPU에서 어떠한 것을 출력하면 인간은 감각을 통해 이를 뇌로 전달하고 뇌는 또 어떠한 반응을 하는데 이를 어떠한 장치를 통해 다시 CPU로 전달한다. 이러한 과정을 Human Factors Model이라고 한다.

### Human Factors Model - Sensors

인간의 감각을 의미한다. 인간의 감각은 5가지로 구성되어 있다.

- Eyes(vision): 10,000,000 bps
- Skin(touch): 1,000,000 bps
- Ears(audition): 100,000 bps
- Nose(olfaction): 100,000 bps
- Mouth(gustation): 1,000 bps

시각이 대부분을 차지하고 있다.

#### Light

우리는 가시광선에 해당하는 일부 파장만 볼 수 있다. 이러한 파장을 visible spectrum이라고 한다. 이러한 visible spectrum은 400nm(violet) ~ 700nm(red)이다. single frequency는 monochromatic light(단색광)이라고 한다. 참고로 색상은 wavelength가 아니라 frequency에 의해 결정된다.

#### Hyuman Eye

우리의 눈은 retina(망막)을 통해 빛을 받고 이를 신경 신호로 변환한다. 이러한 retina는 2가지 종류의 cell로 구성되어 있다.

- Rods(간상): low light, no color
- Cones(원추): high light, color

그리고 눈은 2가지 종류의 움직임을 가지고 있다.

- Fixation: 눈을 고정시키는 것
- Saccade: 눈을 움직이는 것

이러한 특성을 활용해 scan path를 만들 수 있다.

#### Hearing (Audition)

청각에는 4가지 물리적 특성이 있다.

- Loudness (세기): 진폭에 비례 (dB)
- Pitch (높낮이): 주파수에 비례 (Hz)
- Timbre (음색): sound's brightness
- Envelope: sound's attack, sustain, decay -> 시간에 따른 소리 변화

#### Touch (Tactition)

- 마우스 클릭감
- 진동

#### Smell (Olfaction)

실질적으로 재현하기 어렵고 지연시간이 길고 적응이 빠르기 때문에 잘 사용하지 않는다.

### Human Factors Model - Responder

인간의 반응에는 Limbs(팔, 다리), Mouth(입), Voice(목소리)가 있다.

#### Limbs

손가락, 손, 팔등 기계를 작동시킬 수 있는 부분이다. Limbs에서 중요한 부분은 Handedness로 왼손잡이, 오른손잡이에 따라서 다르게 설계해야 더 편하게 사용할 수 있다는 부분이다.

또한 proprioception(고유감각)이라는 특성도 조심해야 하는데 이는 눈으로 보지 않고 근육의 위치를 파악하는 것이다.

#### Voice

- 음성 인식
- NVVI
  - Non-Verbal Vocal Input
  - 잘 들리지 않는 환경에서 음성 인식을 위해 사용한다.

#### Eyes

앞서 살펴본 fixation, saccade를 활용하여 responder로써의 역할도 할 수 있다.

### Human Factors Model - Brain

인간의 뇌는 생물학적으로 가장 복잡한 구조체로 알려져 있다. 뇌를 통해 인간은 고려하고, 기억하고, 회상하고, 이유를 찾고, 결정하는 등 다양한 일을 할 수 있다. HCI에서는 Perception, Cognition, Motor response를 다룬다.

#### Perception (지각)

뇌 처리의 첫 번째 단계로 청각, 시각, 후각, 촉각, 미각을 통해 받은 신호를 처리한다. 우리는 이러한 신호들을 통해 차이를 느끼는 정도를 파악하는 JND(Just Noticeable Difference)를 알아봤다.

예를들어 첫번째 소리가 200hz, 두 번째 소리가 220hz인데 피실험자가 차이를 지각했다면 JND는 20hz보다 작다고 볼 수 있다.

또한 이러한 지각의 특성상 모호성과, 착시를 조심해야 한다.

#### Cognition (인지)

인지는 생각하고, 결정하는 등과 같은 지적인 활동을 의미한다. 이러한 인지는 연구하기 매우 어렵다.

특히 결정을 내리는 것을 측정하는 것은 매우 어려운 일인데 우리는 뇌파 분석을 통해 얼마나 인간은 느린지 알 수 있다.

#### Memory

인간의 기억은 2가지로 나눌 수 있는데

- Long-term memory
  - Declarative memory: 사실을 기억하는 것
  - Procedural memory: 기술을 기억하는 것
- Short-term memory: 보통 7개의 chunk를 기억할 수 있다.
  - 인지하기 쉽게 나누어서 기억한다.

### Human Factors Model - Human Performance

인간은 빠르게 할수록 오류를 많이 발생시키는 trade-off가 발생한다. 하지만 skilled behavior를 통해 이러한 trade-off를 어느정도 극복할 수 있다.

또한 이러한 성능에는 attention이라는 특성도 크게 작용하는데 인간은 2개 이상의 일을 동시에 하면 집중하기 어려워 오류가 많이 발생한다. 근데 attention은 단순하지 않다. 예를 들어 문자하면서 운전하는 건 어렵고 걸으면서 말하는 것은 쉽다.

### Human Errors

인간은 실수하기 마련인데 이것은 유저의 문제가 아니라 디자인에 따른 문제 일수도 있는데 이를 design induced error라고 한다.
