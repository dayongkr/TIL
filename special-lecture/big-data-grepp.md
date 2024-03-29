# grepp cto 환기용 님의 빅데이터 강연

## Introduction

서울대 학사와 석사 과정을 마치고 삼성전자로 경력을 쌓다가 미국으로 넘어가서 일하다가 데이터 도메인 쪽으로 넘어갔다.

### 커리어는 정글짐

요즘에는 커리어 사다리라는 말이 없고 커리어 정글짐으로 바뀌었기 때문에 다양한 회사에서 다양한 경험을 쌓아야 한다. 또한 항상 급여가 오르는 거만 생각하는 게 아니라 성장할 수 있어야 한다.

모든지 선택할 때 길게 보는 게 좋다.

### 결과를 내는 데 집중하기

- 성취하는 경험
- 기술 중심으로 경력을 쌓는 것이 아니라 결과를 내는 것에 집중하기
- 의사소통을 잘하는 것이 중요하다. (질문 잘하기)
  - 면접에서도 질문을 했는데 잘 대답해주면 좋은 회사라 볼 수도 있다.

### 나의 성장을 저해하는 요소

- 나이 혹은 남과의 비교
- 한계를 정하지 말자
- 과거의 상처

### 복리가 있는 일 하기

- 시작이 반
- Practice Makes Perfect
  - 최소 6개월은 full time으로 해보기
- 복리가 있는 일
  - 운동
  - 배움/학습
  - 네트워킹 (사람 만나기)
    - 첫인상으로 판단하지 말고 이야기 많이 해보기
  - 책읽기/글쓰기

### 사기 증후군 극복

- 어제의 나와 오늘의 나를 비교하기
- 자신감 느끼기
  - 영어를 잘 못했지만 잘했다.
  - 결국 결과를 잘 내면 된다.
  - 작은 성취를 계속 쌓아 올려서 자신감 느끼기

## 빅데이터

### Data Flow

data가 중앙에 모이면 data engineer가 data를 가공하면 data analytics가 분석하고 insight를 얻고 data scientist가 insight를 가지고 머신러닝
을 하고 결과를 내는 것이다.

이를 통해 회사가 앞으로 갈 길을 정하고 미래를 예측할 수 있다.

- Data scientist
  - 사용자 경험을 알고리즘으로 향상하는 사람으로 통계적 지식이 있는 것이 좋다.
- Data analytics
  - 모든 사람이 해야만 하는 직군이 되고 있다.
  - 예를 들어 엑셀이 모든 사무직이 배우고 있는 것과 같다.
- Data engineer
  - ETL, Data warehouse를 관리하는 사람

### Big data 정의

- 한 서버에 저장할 수 없는 데이터
- 기존의 소프트웨어로는 분석하기 어려운 데이터
  - 기존 RDBMS는 분산 환경을 염두에 두지 않고 Scale-up 접근 방식이 하드웨어를 확장하는 방식이다.

### Big data 처리의 특징

- data이 대부분 비구조화 형태이기 때문에 데이터를 분석하기 위해서는 데이터를 구조화해야 한다.
- 큰 데이터를 손실 없이 보관할 방법이 필요
- 병렬 처리할 수 있는 분산 컴퓨팅 시스템이 필요

#### 대용량 분산 시스템이 가지고, 있어야 할 특징

- 분산 환경 기반
- Fault Tolerance
- 확장 용이

### Hadoop

구글랩 발표 논문들에 기반해 만든 오픈소스 프로젝트이다. 파일을 다수의 컴퓨터로 분산해서 저장하는 것을 HDFS라고 하며 MapReduce를 통해 분산 처리를 한다.

### Spark

Hadoop의 MapReduce를 대체하기 위해 만들어진 오픈소스 프로젝트이다. Hadoop의 MapReduce는 데이터를 읽고 쓰는 과정에서 많은 디스크 I/O가 발생하기 때문에 Spark는 메모리에 데이터를 저장하고 처리하는 방식을 사용한다.

SQL을 사용해서 다루는 게 제일 좋다.

## 데이터와 관련된 다양한 직군

python, sql, 의사소통 능력과 같은 기본에 충실하고 copilot, chat gpt를 잘 활용해서 생산성을 늘리는 것도 중요하다. 혼자서 공부하려고 하지 말고 빠르게 인턴이나 면접을 봐서 실무를 경험하는 것이 중요하다.
