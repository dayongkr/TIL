# 네트워크개론 13주 차

## IP | Internet Protocol

### IP Datagram Format (IPv4)

- ver: IP protocol version
- head.len: header length
- tos: type of service
  - 실제로는 ECN만 사용한다.
- total.len: total length
- 16-bit identifier, flags, fragment offset
  - MTU보다 큰 packet을 보낼 때, fragment로 나눠서 보내는데 이를 reassemble하기 위해 사용한다.
  - fragment offset: fragment의 시작 위치
- ttl: time to live
  - router를 몇 번 거쳐서 갈 수 있는지를 나타낸다.
  - 0이 되면 버린다.
- upper layer protocol
  - TCP, UDP, ICMP, IGMP 등
- header checksum
  - header의 오류를 검사한다.
- source IP address, destination IP address -> End-to-End Address
- options
  - timestamp, security, record route 등
  - 거의 사용하지 않는다.

### IP Address

- 32-bit address
- Net | Host
  - Net: network address
  - Host: host address
- Subnetting
  - Net | Subnet | Host
  - Subnet: subnet address
  - Intervening router을 거치지 않고도 subnet 내에서 통신할 수 있다.
- CIDR: Classless InterDomain Routing
  - 주소 뒤에 /n을 붙여서 subnet mask를 표현한다.
  - 이를 통해 class를 나누지 않고도 subnet을 나눌 수 있다.

### DHCP | Dynamic Host Configuration Protocol

- 동적으로 IP address를 할당한다.
- Operation
  - host가 broadcast로 DHCP server를 찾는다.
  - DHCP server가 offer를 보낸다.
  - host가 DHCP server에게 request를 보낸다.
  - DHCP server가 ACK를 보낸다.
  - host가 ACK를 받으면 IP address를 사용한다.
- default gateway: router의 IP address
- UDP를 사용한다.
- ISP의 block당 8개의 IP address를 할당받는다.
- ICANN이 address의 block을 관리한다.

### NAT | Network Address Translation

- 하나의 IPv4 address를 여러 개의 host가 사용할 수 있게 한다.
- NAT router가 private address를 public address로 바꾼다.
- Operation:
  - outgoing packet: source IP address를 NAT router의 public address로 바꾼다.
  - remember in NAT translation table
  - incoming packet: destination IP address를 NAT router의 private address로 바꾼다.
  - 포트 또한 바꾼다.
- 포트도 수정하기 때문에 layer 3까지 수정해야 하는 원칙에 위배된다.
- IPv6에서 주소 부족 문제를 해결했기 때문에 IPv4에서만 사용한다.
- End to End Principle을 위배한다.
- 외부에서 먼저 연결을 시도하면 연결할 수 없다. 다만 포트포워딩을 통해 해결할 수 있다.

### IPv6

- 128-bit address
- Datagram Format
  - ver: IP protocol version
  - priority, flow label: QoS
  - payload length
  - next header: for upper layer protocol
  - hop limit: TTL
  - source IP address, destination IP address
  - payload
- address가 차지하는 크기는 4배가 됐지만 checksum, fragmentation, options를 제거했기 때문에 전체적으로는 2배가 된다.
- Tunneling
  - 모든 router가 IPv6을 지원하지 않기 때문에 이러한 router을 뚫기 위해 IPv4를 IPv6로 감싼다.
  - 따라서 IPv4의 address에는 IPv4 router와 인접한 IPv6 router의 address가 들어간다.
