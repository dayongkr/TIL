# 네트워크개론 2주 차

오늘은 internet structure, 성능, 보안, 프로토콜 계층에 대해 배웠다.

## Internet Structure

internet은 네트워크들의 네트워크이다. 이러한 네트워크들은 ISP(Internet Service Provider)를 통해 서로 연결이 된다.

### 연결되는 방법

1. 각 네트워크를 서로 연결한다.
   1. scable하지 않다.
2. global ISP를 통해 연결한다.
   1. global ISP가 down되면 모든 네트워크가 down된다.
3. 여러 ISP를 통해 연결한다.
   1. ISP가 독점적이지 않기 때문에 다양한 경쟁자가 생기기 때문에 현재는 이 방법을 사용한다.
   2. IXP(Internet Exchange Point)를 통해 연결한다.

그래서 현재는 Tier 1 ISP, Content Provider이 제일 상위에 위치해 있고 그 아래에는 IXP, Regional ISP, Access ISP가 위치해 있다.

> Content Provider: Google, Facebook, Netflix 등 대규모 서비스를 제공하는 업체가 직접 ISP를 운영하는 경우가 있다.

## Performance

패킷이 router buffer에 들어가 있으면 delay가 발생하고 더이상 패킷을 받을 수 있는 free buffer가 없으면 패킷을 drop한다.

### Delay

- Processing delay: router가 패킷을 처리하는데 걸리는 시간
  - 다음 router로 전송하기 위해 패킷을 검사하는 시간
  - 다음 router를 찾는 시간
- Queuing delay: router buffer에 들어가 있는 패킷이 다음 router로 전송되기 위해 기다리는 시간
- Transmission delay: 패킷이 link를 통해 전송을 시작하는데 걸리는 시간
- Propagation delay: 패킷이 link를 통해 전송되는데 걸리는 시간

주로 processing delay와 queuing delay가 가장 크다.

### Carvan analogy

- 10개의 차가 있다
- toll booth에서 12초가 걸린다
- 100km/h로 달린다
- toll booth 간격은 100km이다

이러한 상황에서 10개의 차가 첫 번째 booth를 통과해서 두 번째 booth에 도착하는데 걸리는 시간은?

- 10개의 차가 12초씩 걸리니까 120초가 걸린다
- 100km/h로 달리니까 1시간이 걸린다
- 즉 120초 + 1시간 = 1시간 2분이 걸린다

### Traffic intensity

- a: average packet arrival rate
- L: packet length
- R: link bandwidth (bit transmission rate)

L \* a / R = traffic intensity

- traffic intensity ~ 0: delay가 거의 없다
- traffic intensity -> 1: delay가 크다
- traffic intensity > 1: delay가 무한대로 가버린다

### delay and routes 측정

보통 traceroute program을 통해 delay와 routes를 측정한다. 측정할 때 time-to-live(TTL)을 이용한다. TTL은 패킷이 router를 지날 때마다 1씩 감소한다. TTL이 0이 되면 패킷은 drop이되고 보통 router가 sender에게 관련된 정보를 담아 message를 보내는데 이를 이용해서 delay와 routes를 측정한다. 즉 TTL을 값을 1에서부터 늘려가면서 패킷을 보내며 측정한다.

### Throughput

Throughput은 sender가 receiver에게 정해진 시간에 얼마나 많은 양의 데이터를 전송하는지를 나타낸다. throughput에는 병목 현상이 발생할 수 있다. 이와 같은 병목 현상은 중간에 있는 특정한 link가 다른 link에 비해 bandwidth가 작기 때문에 발생한다. 즉 throughput은 가장 작은 link의 bandwidth에 의해 결정된다.

## security

인터넷은 초기에 보안에 대해 생각해서 설계한 것이 아니기 때문에 다양한 취약점이 존재한다.

### Bad guys

- sniffing: 패킷을 가로채서 정보를 얻는 것
  - wireshark을 통해 패킷을 가로챌 수 있다.
  - promiscuous mode를 통해 모든 패킷을 가로챌 수 있다.
  - 한 회선을 공유하는 모든 컴퓨터는 모든 패킷을 볼 수 있다.
- spoofing: 패킷의 source address를 바꿔서 보내는 것
- DoS - Denial of Service: 서버에 과부하를 주어 서비스를 못하게 하는 것

### Lines of defense

- authentication: 패킷의 source를 확인하는 것
- confidentiality: 패킷의 내용을 암호화하는 것
- integrity: 패킷의 내용이 변조되지 않았는지 확인하는 것
- access restriction: 특정한 사용자만 서비스를 사용할 수 있도록 하는 것
- firewalls: 특정한 패킷을 막는 것

## Protocol Layering

복잡한 시스템을 단순화하기 위해 layer를 나누어서 설계한다. layer를 나누면 각 layer는 서로 독립적이기 때문에 각 layer를 독립적으로 설계할 수 있다. 또한 layer를 나누면 각 layer의 기능을 바꾸어도 다른 layer에 영향을 주지 않는다.

- application layer: 사용자와 직접적으로 상호작용하는 layer (message)
- transport layer: end-to-end communication을 담당하는 layer (segment)
- network layer: router 간의 communication을 담당하는 layer (datagram) => 여기서 부턴 조각으로 생각하지 않고 전송해야될 하나의 독립적인 데이터로 생각한다.
- link layer: link 간의 communication을 담당하는 layer (frame)
- physical layer: bit를 전송하는 layer
