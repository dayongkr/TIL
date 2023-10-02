# 네트워크개론 6주 차

## transport layer

transport layer는 프로세스간의 통신을 담당한다. sender는 segments를 만들어서 network layer에게 전달하고, receiver는 segments를 받아서 application layer에게 전달한다.

대표적인 transport layer 프로토콜로는 TCP와 UDP가 있다. TCP는 reliable한 프로토콜이고, UDP는 unreliable한 프로토콜이다. 둘 다 delay, bandwidth는 고려하지 않는다.

### multiplexing/demultiplexing

multiplexing은 transport layer에서 여러 개의 프로세스가 하나의 네트워크를 공유할 때, 각각의 프로세스가 전송한 데이터를 구분할 수 있도록 하는 것이다. demultiplexing은 반대로, 네트워크로부터 받은 데이터를 각각의 프로세스에게 전달하는 것이다.

자세한 내용은 socket을 공부할 때 공부한다고 하셨다.

### UDP

- unreliable
- best effort
  - out of order
  - lost
- connectionless
  - call setup이 없다.
- use
  - DNS, streaming multimedia, SNMP, HTTP/3
- header
  - source port number
  - destination port number
  - length
  - checksum
  - application data (payload)
  - 각 field는 2byte씩이다.
    - application data는 예외

#### UDP checksum

UDP checksum은 error(flipped bits) detection을 위해 사용되는데 예를들어 16-bit integers씩 나눠서 더하고, overflow가 발생하면 wrap around를 해서 더한다. 그리고 1의 보수를 취한다. 그리고 이 값을 checksum으로 사용한다.
