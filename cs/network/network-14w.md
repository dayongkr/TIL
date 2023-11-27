# 네트워크개론 14주 차

## Control Plane

Network Layer에서 routing 부분을 Control Plane이라고 한다.

### Per-router Control Plane

- link state
  - 모든 라우터가 link cost info를 완벽하게 알고 있다.
  - Dijkstra's algorithm을 사용한다.
  - forwarding table에는 도착지로 가기 위한 다음 hop만 저장한다.
  - broadcast로 link cost info를 전송한다.
    - O(n^2)의 overhead가 발생한다.
  - oscillation이 발생할 수 있다.
    - link cost에 의존하기 때문에 link cost가 바뀌면 다시 계산해야 하는데 이 때 계산이 무한히 반복될 수 있다.
- distance vector
  - 이웃한 라우터에게 link cost info를 전송한다.
  - Bellman-Ford algorithm을 사용한다.
  - DV + 인접 link cost의 최소값을 저장하는데 변화가 발생하면 계속 이웃한 라우터에게 전송한다.
  - bad news travels slowly
    - 간혹 업데이트가 전파가 잘 되어 있지 않으면 무한히 계산이 반복될 수 있다.
  - 어떠한 router가 매우 작은 cost를 가지고 있다고 거짓 정보를 퍼트리면 black holing 문제가 발생한다.
    - 때문에 robust하지 않다.

### Intra-ISP, Inter-ISP

- Intra-ISP
  - AS 내부에서 routing을 수행한다.
  - RIP
    - distance vector
  - OSPF
    - link state
  - EIGRP
    - distance vector
    - Cisco proprietary
  - performance가 policy보다 우선순위가 높다.
- Inter-ISP
  - AS 간에 routing을 수행한다.
  - 어떤 AS에 연결되어 있는지 내부에 전파한다.
  - policy가 performance보다 우선순위가 높다.

### BGP | Border Gateway Protocol

- Inter-AS routing protocol
- eBGP: 이웃한 AS으로부터 접근 가능한 정보를 얻는다.
- iBGP: 접근 가능한 전부를 모든 내부 라우터에게 전파한다.
- BGP session: peer간 BGP message를 교환하기 위한 TCP connection
- AS-PATH: AS들의 sequence
- NEXT-HOP: 다음 AS에 이웃한 Internal router
- Hot Potato Routing: 최대한 빨리 다음 AS로 보내는 것
