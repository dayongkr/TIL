# 네트워크개론 1주 차

## 소개

- Internet: 네트워크의 네트워크
- Internet standards
  - RFC: Request for Comments
  - IETF: Internet Engineering Task Force

## 로드맵

- Network edge
  - 단말기 간 통신 (Access network)
  - 유선
    - cable-based access
      - FDM (Frequency Division Multiplexing)으로 다중화
      - 여러 집이 하나의 케이블을 공유
      - 주로 미국에서 사용
    - DSL (Digital Subscriber Line)
      - 전화선을 사용
      - 국내에서 많이 사용
      - 각자의 전화선을 사용
      - DSLAM (DSL Access Multiplexer)을 사용하여 다중화
  - 무선
    - WLANs (Wireless LANs)
      - WiFi
      - IEEE 802.11
    - Wide-area cellular access
      - 3G, 4G
      - LTE
  - modem
    - modulator + demodulator
  - packet
    - 보내고자 하는 데이터를 작은 chunk로 나눈 것
    - link bandwidth / link transmission rate(R)
      - link가 전송할 수 있는 데이터의 양
    - packet transmission delay = L / R
  - links
    - guided media
      - copper
      - fiber
    - unguided media
      - radio
      - satellite
- Network core
  - 라우터간 통신 (Packet switching, Circuit switching)
  - forwarding
    - 라우터가 패킷을 받아서 다음 라우터로 전송
  - routing
    - 라우터가 패킷을 받아서 어디로 보낼지 결정
    - global action으로 볼 수 있음
  - packet-switching
    - store-and-forward transmission
      - 전송할 데이터를 모두 받은 후에 전송
    - queueing이 발생하고 넘치면 drop하여 packet loss가 발생
  - circuit-switching
    - 전화망
    - 회선을 예약하여 사용
  - packet vs circuit
    - bursty data에선 packet-switching이 유리
