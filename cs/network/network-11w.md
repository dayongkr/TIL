# 네트워크개론 11주 차

## TCP congestion control

TCP는 congestion control을 위해 AIMD(Additive Increase Multiplicative Decrease)를 사용한다. 즉, congestion window를 additive하게 증가시키고 packet loss가 발생하면 congestion window를 multiplicative하게 감소시킨다. 이를 통해 network의 혼잡을 방지한다.

TCP congestion control의 기본 목표 3가지는 다음과 같다

- fairness: 각각의 TCP connection이 공평하게 bandwidth를 나눠쓸 수 있도록 한다.
- full utilization: network의 모든 bandwidth를 사용할 수 있도록 한다.
- congestion control: network의 혼잡을 방지한다.

기본적으로 timeout이 발생하면 심각한 상황이기 때문에 congestion window를 1로 초기화하고 slow start를 한다. 다만 triple duplicate ACK이 발생하면 congestion window를 절반으로 줄이고 congestion avoidance를 한다.

여기서 slow start란 초반에 빠르게 full utilization 하기 위해 매 RTT마다 cwnd를 2배를 하는 것이다. 이를 first loss까지 수행한다. 이후에는 congestion avoidance를 한다. 즉, cwnd를 1씩 증가시킨다. 이는 ssthresh로 구현하는데 ssthresh는 cwnd가 ssthresh보다 작을 때는 slow start를 하고 cwnd가 ssthresh보다 클 때는 congestion avoidance를 한다. ssthresh는 loss가 발생할 떄 cwnd의 절반으로 설정한다.

### Modeling TCP Throughput

TCP throughput을 모델링하기 위해 다음과 같은 변수들을 정의한다.

- p: packet loss rate
- RTT: round trip time
- k: packet size

이 때 throughput은 다음과 같다.

```
throughput = sqrt(3/2) * k / (RTT * sqrt(p))
```

### TCP CUBIC

최근에 제안된 TCP CUBIC은 TCP congestion control의 문제점을 해결하기 위해 제안된 방법이다. TCP CUBIC은 congestion window를 cubic하게 증가시켜 빈공간 낭비를 줄이고 max에 도달하면 천천히 증가시켜 packet loss를 줄인다.

### bottleneck link

bottleneck link란 network에서 가장 좁은 link를 의미한다. 즉, 가장 좁은 link에서 congestion이 발생한다. 따라서 bottleneck link의 bandwidth를 늘리면 network의 throughput을 늘릴 수 있다.

### Delayed-based congestion control

기존의 congestion control을 일단 packet loss가 발생하면 congestion window를 줄이는 방식이었다. 하지만 이는 packet loss가 발생하기 전까지는 network의 혼잡을 방지하지 못한다. 따라서 packet loss가 발생하기 전에 congestion window를 줄이는 방식이 필요하다. 이를 위해 delayed-based congestion control이 제안되었다.

cwnd / RTT를 계산하고 cwnd / minRTT를 계산하여 둘의 차이를 계산한다. 두 값이 가까우면 혼잡이 심하지 않다고 판단하고 cwnd를 증가시키고 두 값이 멀면 혼잡이 심하다고 판단하고 cwnd를 감소시킨다. 이떄 packet loss가 발생한 것은 아니니 linear하게 증가 감소시킨다.

### Explicit Congestion Notification

ECN은 IP header의 ToS field를 사용하여 congestion을 알리는 방법이다. ECN field를 11로 설정하면 congestion이 발생했다는 것을 의미한다. 따라서 router에서 congestion이 발생하면 ECN field를 11로 설정하여 packet을 전송한다. 도착지에서 해당 packet을 받으면 ACK에 ECE field를 1로 설정하여 sender에게 알린다. 이런 방식은 서로 정보를 주고 받지 않는다는 layering의 원칙에 위배ehlsek.

### TCP fairness

TCP fairness란 여러개의 TCP connection이 공평하게 bandwidth를 나눠쓸 수 있도록 하는 것이다. TCP fairness를 위해 다음과 같은 방법이 제안됐다.

- 1 기울기로 증가한다.
- loss가 발생하면 절반으로 줄인다.
