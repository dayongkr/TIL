# 네트워크 개론 3주 차

## 응용 계층 (Application Layer)

소프트웨어 프로세스 간의 통신을 위한 인터페이스를 제공한다.

### Paradigm

- Client-Server
  - server
    - 항상 켜져있는 host
    - 고정 IP 주소를 가지고 있음
  - client
    - 서비스를 요청하는 host
    - 간헐적으로 연결됨
    - IP 주소가 변할 수 있음
    - client끼리는 직접 통신하지 않음
- Peer-to-Peer (P2P)
  - 항상 켜져있는 host가 없음
  - 서로 간의 간헐적인 연결로 통신
  - IP 주소가 변할 수 있음
- IPC
  - Inter-Process Communication
  - 같은 host 내의 프로세스 간의 통신
  - process간 역할에 따라 client와 server로 구분됨

### Socket

응용계층과 전송계층 사이의 인터페이스으로 데이터를 주고 받을 때 사용되는 메모리 및 변수와 같은 존재이다. 현실 세계로 비유하자면 문이라고 보면 된다.

### Addressing process

IP주소는 host device별로 할당되기 때문에 process를 구분하기 위해서는 port number가 필요하다. 예를들어 HTTP는 80번 포트를 사용한다.

### define and needs

- defines

  - types of messages exchanged
    - request, response
  - message syntax
    - 메시지에 있는 fields가 무엇이고 어떻게 해석해야 하는지
  - message semantics
    - fields 값이 어떤 의미를 가지는지

- needs
  - data integrity
    - 데이터가 손상되지 않고 전달되는지
    - reliability
  - timing
    - 데이터가 언제 전달되는지
    - latency
  - throughput
    - 단위 시간당 전달되는 데이터의 양
  - security
    - 데이터가 암호화되어 있는지

### Transport Service

- TCP
  - reliable transport
  - flow control
    - 송신자가 수신자의 처리 속도를 초과하지 않도록 제어
  - congestion control
    - 네트워크 내의 혼잡을 방지하기 위한 제어
  - connection-oriented
  - does not provide: timing, minimum throughput guarantee, security
- UDP
  - unreliable transport
  - does not provide: reliability, flow control, congestion control, timing, throughput guarantee, security

voip와 같이 신뢰성이 중요하지 않은 서비스에서는 UDP를 사용한다.

### HTTP

HTTP는 hypertext transfer protocol으로 client/server model을 사용하는 웹애플리케이션계층 프로토콜이다. HTTP는 TCP를 사용하며 기존 요청에 대한 정보를 저장하지 않는 stateless protocol이다.

때문에 cookie를 사용하는데 http response header에 Set-Cookie를 사용해서 client에게 cookie를 전달하고 client는 이를 저장해두었다가 다음 request에 Cookie를 사용해서 server에게 전달한다. 이를 통해 인증, 세션등을 구현할 수 있는데 다른 사이트에서 이를 사용할 수 있어서 보안에 취약하다.

HTTP는 Persistent HTTP와 Non-persistent HTTP로 나뉜다. Non-persistent HTTP는 한 번의 TCP connection으로 하나의 object만 전송하는 반면 Persistent HTTP는 한 번의 TCP connection으로 여러 개의 object를 전송한다. 이를 통해 RTT를 줄일 수 있다.

> RTT: Round Trip Time으로 데이터를 전송하고 응답을 받는데 걸리는 시간이다.
