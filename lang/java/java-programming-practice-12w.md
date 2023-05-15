# 자바프로그래밍 12주 차

## Socket

데이터를 주고 받는 받는 곳이라고 생각하면 된다.

### 네트워크 용어

- TCP (Transmission Control Protocol)
  - 연결 지향적
  - 신뢰성이 높음
  - 속도가 느림
- UDP (User Datagram Protocol)
  - 비연결 지향적
  - 신뢰성이 낮음
  - 속도가 빠름
- Packet
  - 데이터를 전송하는 단위
- ACK(Acknowledgement)
  - 패킷을 받았다는 신호

### Multithread

connection을 기다른 것을 제외하고는 아무것도 못하기 때문에 multithread를 사용한다. 즉 client가 접속하면 thread를 하나 만들어서 그 thread가 client와 통신하게 된다.

### Java TCP Programming

SeverSocket과 Socket을 사용한다. 먼저 ServerSocket을 생성하고 accept()를 호출하면 client가 접속할 때까지 기다린다. 그리고 client가 접속하면 Socket을 생성하고 이를 통해 통신을 한다.
