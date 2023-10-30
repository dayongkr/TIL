# 네트워크개론 10주 차

## Socket programming

Socket이란 응용계층과 전송계층 사이의 인터페이스 공간으로 메모리 영역이라고 생각하면 된다.

교제에서는 Python에서 socket을 사용하는 방법을 설명하고 있다.

### UDP

```python
# client
from socket import *

serverName = 'hostname'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM) # AF_INET은 IPv4, SOCK_DGRAM은 UDP
message = raw_input('Input lowercase sentence: ')
clientSocket.sendto(message, (serverName, serverPort)) # serverName, serverPort로 message를 보낸다.
modifiedMessage, serverAddress = clientSocket.recvfrom(2048) # 2048은 buffer size
print modifiedMessage # server로부터 받은 message를 출력한다.
clientSocket.close() # socket을 닫는다.
```

```python
# server
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort)) # serverPort로 binding한다.
print "The server is ready to receive"
while 1: # 무한 루프
    message, clientAddress = serverSocket.recvfrom(2048) # client로부터 message를 받는다.
    modifiedMessage = message.upper()
    serverSocket.sendto(modifiedMessage, clientAddress)
```

UDP는 하나의 socket으로 여러 client와 통신한다. 간혹 message를 보낼 때 encoding을 해야 하는 경우가 있는데 이 때는 `message.encode()`를 사용하면 된다.

### TCP

```python
# client
from socket import *

serverName = 'hostname'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM) # AF_INET은 IPv4, SOCK_STREAM은 TCP
clientSocket.connect((serverName, serverPort)) # serverName, serverPort로 연결한다.
sentence = raw_input('Input lowercase sentence: ')
clientSocket.send(sentence) # server로 message를 보낸다.
modifiedSentence = clientSocket.recv(1024) # server로부터 message를 받는다.
print 'From Server: ', modifiedSentence
clientSocket.close() # socket을 닫는다.
```

```python
# server
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort)) # serverPort로 binding한다.
serverSocket.listen(1) # 최대 1개의 client를 받는다.
print "The server is ready to receive"

while 1: # 무한 루프
    connectionSocket, addr = serverSocket.accept() # client로부터 연결을 받는다. -> client 별로 socket을 생성한다.
    sentence = connectionSocket.recv(1024) # client로부터 message를 받는다.
    capitalizedSentence = sentence.upper()
    connectionSocket.send(capitalizedSentence) # client로 message를 보낸다.
    connectionSocket.close() # socket을 닫는다.
```

TCP는 일단 연결을 담당하는 socket을 하나 만들고, client가 연결을 요청하면 accept를 통해 새로운 socket을 만들어서 통신한다.

## Principles of congestion control

network가 다룰 수 있는 traffic 보다 더 많은 source가 들어오면 congestion이 발생한다. 이를 방지하기 위해 congestion control이 필요하다.

이러한 congestion은 4가지 상황이 있다.

- 하나의 router, 무한한 buffer
  - 모든 packet을 저장할 수 있기 때문에 packet loss가 발생하지는 않지만 exponential한 delay가 발생한다.
- 하나의 router, 유한한 buffer
  - 네트워크 상태를 모두 아는 상태 (perfect knowledge)
    - packet loss가 발생하지 않는다.
  - packet drop으로 congestion을 알 수 있는 상태 (some perfect knowledge)
    - packet loss로 인한 retransmission이 발생해서 delay가 발생한다. throughput이 떨어진다.
  - timeout으로 congestion을 알 수 있는 상태 (unneededd duplication)
    - premature timeout이 발생할 수 있기 때문에 중복이 발생한다.
    - 따라서 위 경우보다 throughput이 더 떨어진다.

결국 이러한 congestion control은 전송계층 프로토콜인 TCP에서 이루워지기 때문에 네트워크의 상태를 모르는 상태에서 congestion control을 할 수 밖에 없다. 다만 TCP ECN과 같은 프로토콜과 같이 network의 지원을 받아 congestion control을 할 수도 있다.
