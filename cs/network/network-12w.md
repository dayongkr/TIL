# 네트워크개론 12주 차

## 네트워크 계층: Data Plane

네트워크 계층은 Data Plane과 Control Plane으로 나뉘어진다. Data Plane은 데이터를 전송하는 역할(Forwarding)을 하고 Control Plane은 데이터를 전송하기 위한 경로를 설정하는 역할(Routing)을 한다. 이번에는 Data Plane에 대해서 알아보자.

참고로 control plane은 per-router와 software-defined networking으로 나뉜다. per-router는 각 라우터가 자신의 경로를 계산하는 방식이고 software-defined networking은 중앙집중식으로 경로를 계산하는 방식이다. 즉 라우터는 switch 역할만 하고 경로 계산은 중앙에서 한다.

### Network Service Model

Network service model은 예를 들어 각 datagrams을 특정 delay 안에 전달하는 것을 보장, datagrams의 최소 bandwidth를 보장, packet간의 spacing을 보장 그리고 마지막으로 datagrams의 순서를 보장해야 한다는 것이 있다. 하지만 우리가 다루는 network service model은 best-effort service model이다. 즉 datagrams을 전달하는 것을 보장하지 않는다.

### Data Plane

Router의 구조는 input port, output port, switch fabric, routing processor로 나뉜다. input port에는 line termination, link layer protocol, lookup, forwarding이 있다. line termination는 physical layer를 의미하고 link layer protocol은 link layer로 내 패킷인지 확인한다. lookup은 forwarding table을 참조하여 output port를 결정하고 forwarding은 output port로 패킷을 전송한다. forwarding 방식은 destination-based forwarding와 다른 필드도 확인하는 general forwarding이 있다.

#### Destination-Based Forwarding

일반적인 destination-based forwarding은 link interface로 matching rule을 만들어서 forwarding table을 만든다. 이때 matching rule은 prefix matching을 사용한다. 예를 들어서 110\*이면 110으로 시작하는 모든 패킷을 의미한다. 이때 forwarding table은 prefix matching을 사용하기 때문에 가장 긴 prefix를 가진 rule을 사용한다. 이를 longest prefix matching이라고 한다.

#### Switching Fabrics

Switching fabrics은 input port에서 output port로 패킷을 전송하는 역할을 한다. 이때 switching fabrics은 memory, bus, crossbar switch로 나뉜다. memory는 input port에서 output port로 패킷을 복사하는 방식으로 속도가 느리다. bus는 input port에서 output port로 패킷을 전송하는 방식으로 속도가 빠르다. 하지만 bus는 한번에 하나의 패킷만 전송할 수 있다. crossbar switch는 input port와 output port를 1:1로 연결하는 방식으로 속도가 빠르다. 이는 실제로는 multi-stage switch로 구현되어 datagram을 쪼개어 parallel하게 전송한다.

#### Port Queueing

먼저 Input port 같은 경우에는 앞에 있는 다른 datagram에 의해 갈 수 있지만 block이 되는 HOL blocking이 발생할 수 있다. Output port 같은 경우에는 link transmission rate보다 input port에서 들어오는 datagram의 rate가 더 빠르면 queueing이 발생한다. 이떄 Drop policy와 scheduling policy가 필요하다. Drop policy는 queue가 꽉 찼을 때 어떤 datagram을 drop할지를 결정하는 것이고 scheduling policy는 어떤 datagram을 먼저 전송할지를 결정하는 것이다.

> 추가로 버퍼를 너무 많이 키우면 queueing delay가 발생하고 너무 적게 키우면 drop이 발생하기 때문에 보통 RTT \* link transmission rate / sqrt(N)으로 설정한다. 여기서 N은 flow로 tcp connection을 의미한다.

- Drop policy
  - Tail drop: queue가 꽉 찼을 때 새로운 datagram을 drop한다.
  - Priority drop: queue가 꽉 찼을 때 우선순위가 낮은 datagram을 drop한다.
  - Random drop: queue가 꽉 찼을 때 random하게 datagram을 drop한다.
  - 추가로 꽉 찼을 때 Drop하는 것이 아닌 marking을 통해 congestion을 알리는 방법도 있다.
    - Explicit Congestion Notification(ECN): IP header의 ECN bit를 1로 설정한다.
    - Random Early Detection(RED): queue의 길이가 threshold보다 길어지면 random하게 datagram을 drop한다.
- Scheduling policy
  - FIFO: First In First Out
  - Priority: 우선순위가 높은 queue를 먼저 전송한다.
  - Round Robin: 각 queue에 돌아가면서 전송한다.
