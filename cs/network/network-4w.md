# 네트워크개론 4주 차

## web cache

http request에 대한 response를 저장하는 것이다. response header에 있는 cache-control을 보고 cache를 사용할지 말지 결정한다. caching을 통해 network traffic을 줄일 수 있다.

### caching example

보통의 경우에 public internet과 연결되는 부분의 access link는 bottleneck이다. 따라서 end-end delay에서 access delay가 가장 큰 부분이다. 이를 줄이기 위해 access link rate을 높여도 되는데 이는 비용이 많이 든다. 따라서 caching을 통해 access link utilization을 줄이면 비용적으로 효율적이다.

### conditional GET

cache에 있는 response가 stale하다면 origin server에 있는 response를 받아와 cache를 update한다. 이때 origin server에 있는 response가 바뀌지 않았다면 origin server는 response를 보내지 않고 304 Not Modified를 보낸다.

## http1.1 vs http2.0

http1.1은 persistent connection과 response를 기다리지 않고 여러 개의 request를 보내는 pipelining을 지원한다. 하지만 pipelining은 head-of-line blocking이 발생할 수 있다. head-of-line blocking은 앞에 있는 request가 끝나지 않으면 뒤에 있는 request가 끝나지 않는 것이다.

http2.0은 하나의 object를 여러개의 frame으로 나누어 보내기 떄문에 하나의 연결에 대해 여러개의 object를 보낼 수 있다. 따라서 head-of-line blocking이 발생하지 않는다. 그리고 object prioritization을 지원하기 때문에 중요한 object를 먼저 보낼 수 있다. 그리고 요청하지 않은 object를 보내는 server push를 지원한다.

하지만 둘다 packet loss가 발생하면 모든 object를 다시 보내야 한다.

### http3.0

http3.0은 UDP를 사용한다. UDP는 connectionless이기 때문에 connection을 맺는 과정이 없다. 따라서 connection을 맺는 과정에서 발생하는 delay가 없다. 또한 패킷별로 암호화를 하기 때문에 보안적으로도 좋다.

## DNS

DNS(Domain Name System)는 domain name을 IP address로 변환하는 역할을 한다.

- distributed database
  - hierarchy of name servers
- application-layer protocol

DNS는 워낙 많은 traffic이 발생해서 중앙화 되어 있지 않고 ICANN(Internet Corporation for Assigned Names and Numbers)에 의해 Root DNS server가 관리되고 그 아래로 TLD(Top-Level Domain) DNS server가 관리되고 그 아래로 Authoritative DNS server가 관리된다.

즉 맨 처음에 Root DNS server에 domain name을 보내면 Root DNS server는 TLD DNS server에게 domain name을 보내고 TLD DNS server는 Authoritative DNS server에게 domain name을 보낸다. 이러한 방식은 recursive query이다. Iterative query는 DNS server을 여러번 거쳐서 IP address를 찾는 방식이다.

참고로 DNS server는 best effort service이다. 즉 DNS server가 주는 IP address가 잘못되어 있을 수 있다.

> cached entries가 out-of-date일 수 있다.

### DNS records

distributed database에 저장되는 정보를 DNS records라고 한다. RR format은 다음과 같다.

```
(name, value, type, ttl)
```

- name: domain name
- value: IP address
- type: A, NS, CNAME, MX, AAAA, ...
  - A: name is hostname, value is IP address
  - NS: name is domain, value is hostname of authoritative DNS server
  - CNAME: name is alias name for some canonical(real) name, value is canonical name
  - MX: value is name of mailserver associated with name
- ttl: time to live

### DNS protocol

각 2bytes씩 차지 하고 있다.

- identification: query와 reply를 매칭시키기 위한 것이다.
- flags: query인지 reply인지, query type은 iterative인지 recursive인지등을 나타낸다.
- question count: query의 개수
- answer RR count: answer의 개수
- authority RR count: authority의 개수
- additional RR count: additional의 개수
- 그 밑으로는 실제 데이터가 들어간다.

### DNS security

DDoS Attack은 실질적으로 힘들고 Spoofing attack도 RFC 4033 DNSSEC(DNS Security Extensions)을 통해 막을 수 있다.
