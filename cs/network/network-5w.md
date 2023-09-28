# 네트워크개론 5주 차

## P2P

- 새로운 peer가 들어오면 새로운 service capaity가 되기 때문에 self scalability가 된다.
- client-server 같은 경우에는 최대 다운로드 속도가 server의 upload 속도 또는 client의 download의 최대 속도로 제한되지만 p2p는 peer들의 upload 속도의 합도 추가돼서 더 빠른 속도로 다운로드를 할 수 있다.

### BitTorrent

- file을 256kb 단위로 나눈다.
- tracker: peer들의 정보를 가지고 있는 server
- torrent: peer들의 그룹
- peer가 torrent에 들어오면 tracker로 peer의 정보들을 받기 위해 등록하고 다운로드 하는 동안 업로드도 수행한다.
- tit-for-tat
  - 높은 비율로 4개의 peer로 chunk를 보냄
  - 매 30초마다 랜덤하게 또 다른 peer을 선택한다.

## Video streaming and content distribution networks

ISP traffic의 80%가 streaming service에서 발생하기 때문에 이러한 bandwidth 문제와 다양한 기기, 인터넷 환경를 지원할 수 있는지에 대한 heterogeneity 문제를 해결할 필요가 있다.

### Encoding

동영상의 크기가 크기 때문에 압축을할 필요가 있다. 이때 사용하는 방법은 2가지가 있다.

- spatial
  - 공간을 압축하는 방식 (다른 프레임에 영향을 받지 않음)
  - run length coding이라는 기법으로 색상이 연속으로 이어져있으면 색상 + 갯수로 픽셀을 표현한다.
- temporal
  - 변화에 대한 내용만 보낸다
  - 양 쪽 프레임에 영향을 받음
- CBR: video encodign rate fixed
- VBR: spatial, temporal coding에 따라 비율이 변한 것
- MPEG
  - IBP Frame으로 이루어짐
  - I: independent frame으로 spatial 이용
  - B: bidirectional frame으로 양 쪽 프레임 이용
  - P: previous frame으로 이전 프레임 이용

### Playout delay

- jitter: network delay
- playout 처리가 늦어지면 client 측에서 play하는 제약이 생기기 때문에 일단 delay 시키고 저장된 것들을 play하는 buffering을 사용한다.

### Content distribution network

- DASH: Dynamic, Adaptive, Streaming over HTTP
  - video file을 여러 chunk로 나누는데 여러 rate로 encode하고 manifest file로 chunk 별 URL을 제공한다.
  - client는 network condition에 따라서 rate를 선택한다.
- CDN: Content Distribution Network
  - client와 가까운 곳에 cache server를 두어서 client의 요청을 처리한다.
  - enter deep
    - access network 내부에 server을 설치
  - bring home
    - access network 근처에 큰 server을 설치
