# 네트워크개론 7주 차

## Principles of reliable data transfer

unreliable channel(lose, corrupt, reorder가 일어남)에서 reliable data transfer를 하는 방법에 대해 알아본다.

> sender, receiver는 서로의 상태를 모른다고 가정한다.

### Reliable data transfer protocol (rdt)

rdt는 아래와 같은 기능을 제공한다.

- rdt_send(): rdt_send()는 상위 레이어에서 받은 메시지를 받아서 아래 레이어로 전송한다.
- udt_send(): udt_send()는 rdt_send()로부터 받은 메시지를 받아서 아래 레이어로 전송한다.
- rdt_rcv(): rdt_rcv()는 아래 레이어로부터 받은 메시지를 상위 레이어로 전송한다.
- deliver_data(): deliver_data()는 rdt_rcv()로부터 받은 메시지를 상위 레이어로 전송한다.

rdt의 버전은 아래와 같다.

- rdt1.0
  - reliable channel에서만 사용할 수 있다.
  - FSM을 분리해서 구현한다.
    - FSM: Finite State Machine
      - 상태를 가지고 있는 기계
- rdt2.0
  - unreliable channel에서도 사용할 수 있다.
  - checksum으로 error을 detect하면 NAK를 보내어 다시 패킷을 보내도록 한다.
    - stop-and-wait protocol
  - ACK/NAK 신호가 corrupt될 수 있다는 결함이 있고 중복 handling이 필요하다.
- rdt2.1
  - ACK/NAK 신호가 corrupt될 수 있다는 결함을 해결한다.
  - ACK/NAK 신호가 중복될 수 있다는 결함이 있다.
    - 이를 위해 sequence number를 사용한다.
    - 중복 확인만 하면 되기 때문에 0, 1로 구분한다.
- rdt2.2
  - NAK-free protocol
  - 이전 패킷에 대한 ACK를 보내는 것으로 NAK를 대체한다.
- rdt3.0
  - New channel assumption
    - data, ACK, NAK이 모두 corrupt될 수 있다.
  - timeout을 사용한다.
    - timeout이 발생하면 패킷을 다시 보낸다.
  - 사용률 = (L / R) / (RTT + L / R)
    - L: 패킷의 길이
    - R: link의 전송 속도
    - RTT: round trip time -> 패킷을 전송하고 ACK를 받는데 걸리는 시간
    - (L / R): 패킷을 전송하는데 걸리는 시간
- pipelining
  - 사용률을 높이기 위해 pipelining을 사용한다.
  - Go-Back-N
    - sender
      - send_base: 현재 보내고 있는 패킷의 sequence number
      - nextseqnum: 다음에 보낼 패킷의 sequence number
      - window_size: window의 크기
      - comulative_ack: ACK를 받은 패킷 중 가장 큰 sequence number
        - ACK(n)을 받으면 ACK(n)보다 작은 모든 패킷을 받았다는 의미로 window를 shift한다.
      - timeout(n): n 뒤에 있는 모든 패킷을 다시 보낸다.
    - receiver
      - rcv_base: 현재 받고 있는 패킷의 sequence number
      - 오직 응답을한 sequence number만 저장한다.
  - Selective Repeat
    - receiver가 버퍼에 패킷을 저장하여 필요한 패킷만 다시 받는다.
      - 앞에 있는 패킷을 받지 못하면 뒤에 있는 패킷은 버퍼에 저장하고 timeout이 발생하면 필요한 패킷만 다시 받고 버퍼에 있는 다른 패킷을 deliver한다.
    - 만약에 ack가 corrupt가 되면 sequential number이 충돌이 날 수 있다.
