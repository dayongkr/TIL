# 네트워크개론 9주 차

## TCP

### TCP의 특징

- full duplex
  - 동시에는 아니지만 양방향으로 데이터를 전송할 수 있다.
  - 반대는 simplex
- connection-oriented
  - 연결지향형
  - 연결을 맺고 데이터를 전송하고 연결을 끊는다.
- comulative ACKs and pipelining
  - congestion과 flow control을 위해 사용
- byte-stream
- reliable
  - 데이터의 손실이나 순서의 변경이 없다.

### TCP segment structure

- header
  - 보통 20 bytes
    - 2byte씩 10개
  - sequence number
    - 보내는 데이터의 순서를 나타낸다.
    - segment's data의 첫 번째 byte
  - acknowledgement number
    - 받을 데이터의 순서를 나타낸다.
    - 다른 쪽으로부터 받을 데이터의 첫 번째 byte
  - flag
    - URG
      - urgent data가 있다.
      - 1이면 Urg data pointer가 유효하다.
    - PSH
      - 데이터 전체를 우선적으로 전송한다.
    - RST, SYN, FIN
      - 연결을 맺고 끊을 때 사용한다.
    - ACK
      - acknowledgement number가 유효하다.
      - 즉 ACK를 보낼 때

### TCP round trip time and timeout

너무 짧거나 길면 안 되기 때문에 SampleRTT와 EstimatedRTT를 이용해서 계산한다.

- SampleRTT
  - segment를 보낸 후에 ACK를 받을 때까지 걸린 시간
  - 재전송은 고려하지 않는다.
- EstimatedRTT (Expotential Weighted Moving Average(EMWA))
  - SampleRTT를 이용해서 계산한다.
  - EstimatedRTT = (1 - a) \* EstimatedRTT + a \* SampleRTT
    - a: 0.125

실제 TimeoutInterval은 safety margin을 더하는데 `EstimatedRTT + 4 * DevRTT`이다.

> DevRTT = (1 - b) \* DevRTT + b \* |SampleRTT - EstimatedRTT|
> (b: 0.25)

### ACK generation

- 순서대로 받으면 cumulative ACK를 위해 500ms를 기다린다.
- 하나의 ACK가 pending일 때는 즉시 ACK를 보낸다.
- out of order일 때에는 즉시 duplicate ACK를 보낸다.
- gap이 채워지면 즉시 ACK를 보낸다.

> 추가로 3개의 duplicate ACK를 받으면 fast retransmit을 한다.
> fast retransmit은 timeout보다 빠르게 재전송을 한다.

### TCP flow control

socekt buffer보다 많은 데이터를 보내면 overflow가 발생한다. 따라서 rwnd field에 free buffer size를 넣어 보내어 flow control을 한다.

### TCP connection management

해킹 방지를 위해 sequence number를 random하게 생성하는데 이는 connection을 establish할 때 서로 주고 받는다. 주고 받는 방법은 다음과 같다.

- 2-way handshake
  - client가 server에게 SYN을 보내고 server가 client에게 ACK를 보낸다.
  - 중간에 packet loss가 발생하면 half open connection이 발생한다.
- 3-way handshake
  - client가 server에게 SYN을 보내고 server가 client에게 SYN과 ACK를 보낸다. 마지막으로 client가 server에게 ACK를 보낸다.
  - 끝까지 도달하면 그때서야 connection이 establish된다.
  - SYN은 보통 client가 보내는데 FIN은 누가 먼저 보내도 상관없다.
