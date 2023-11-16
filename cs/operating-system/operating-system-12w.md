# 운영체제개론 12주 차

## Replacement Algorithms

- FA
  - FIFO
    - 가장 오래된 페이지를 교체한다.
    - Belady's anomaly
      - frame을 늘리는데 page fault가 늘어나는 경우가 있다.
    - Timestamping이 필요하다
  - LRU
    - 가장 오래 전에 사용된 페이지를 교체한다.
    - page reference time을 기록해야 한다.
    - locality를 이용한다.
    - loop에서 급격히 page fault가 많이 발생하는 경우가 있다.
  - LFU
    - 가장 적게 사용된 페이지를 교체한다.
    - page reference count를 기록해야 한다.
    - LRU 보다는 overhead가 적다
    - 가장 최근에 로드된 page가 대체될 가능성이 높다
  - NUR
    - Not Used Recently
    - bit vectors 즉 reference bit과 update bit을 사용한다.
    - (reference bit, update bit) = (0, 0) -> (0, 1) -> (1, 0) -> (1, 1) 순으로 교체한다.
  - clock
    - NUR의 단점을 보완한 알고리즘이다.
    - reference bit이 1이면 0으로 바꾸고, 0이면 교체한다.
    - reference bit이 1인 page가 없을 때까지 반복한다.
    - Enhanced second chance algorithm
      - (0,0)이면 교체한다.
      - (0,1)이면 (0,0)으로 바꾸고 write back한다.
      - (1,0)이면 (0,0)으로 바꾸고 앞으로 전진한다.
      - (1,1)이면 (0,1)로 바꾸고 앞으로 전진한다.
    - MRU, MFU는 LRU, LFU의 반대 개념이다.
  - VA
    - Working set
      - 현재 시점부터 과거 특정 시간 동안 사용된 page들의 집합
      - 즉 window size가 중요하다.
      - working set이 바뀌는 구간을 transition point라고 한다.
      - 공간이 더 필요하면 frame을 늘리고 공간이 덜 필요하면 frame을 줄인다.
      - working set동안 사용한 page들을 frame에 유지한다.
      - 성능을 측정할 땐 page fault 발생 수와 mean number of frames를 측정한다.

이러한 알고리즘을 locality와 overhead를 고려하여 선택해야 한다.

## Other Considerations

- Page size
  - 요즘은 키우는 추세이다.
  - page size가 작으면 internal fragmentation이 적다.
  - 다만 I/O 횟수가 많아지는데 근데 또 시간은 줄어든다.
  - page fault가 많아진다.
- Program restructuring
  - locality를 잘 신경써서 프로그램을 작성해야 한다.
  - 예를 들어 2차원 배열을 사용할 때 row major로 사용하면 locality가 좋다.
- TLB Reach
  - entry \* page size = TLB reach이다
  - number을 올리는 것은 비싸기 때문에 page size를 키우거나 page size를 여러 개로 나누는 방법을 사용한다.
