# 자료구조개론 12주 차

## Graph

networks, computer systems등 다양한 곳에서 사용되고 있는 자료구조이다. 그래프는 정점과 간선으로 이루어져 있는데 최소한 정점은 하나라도 존재해야 한다. graph는 같은 edge를 여러개 가질 수 없다. 또한 edge는 방향성이 있을 수도 있고 없을 수도 있다. 방향성이 없는 경우는 undirected graph라고 하고 방향성이 있는 경우는 directed graph라고 한다. 보통 tree를 graph의 일종으로 본다.

### Complete Graph, Multi Graph

complete graph는 모든 정점이 서로 연결되어 있는 graph이다. 즉 undirected graph에서는 edges가 n(n-1)/2개, directed graph에서는 n(n-1)개이다.

multi graph는 같은 edge를 여러개 가질 수 있는 graph이다. 같은 곳으로 가는 경우가 여러 개인 경우에 사용할 수 있다.

### Graph Terminology

- adjacent: 두 정점이 edge로 연결되어 있는 경우
  - directed graph에서는 to, from으로 구분한다.
- incident: 정점과 edge가 연결되어 있는 경우
- subgraph: graph의 일부분
- path: 정점들이 edge로 연결되어 있는 경우
  - simple path: 같은 정점을 두 번 이상 방문하지 않는 path
  - cycle: 시작 정점과 끝 정점이 같은 path
- connected component: 연결되어있는 모든 정점들의 집합
- strongly connected component: 모든 정점에서 모든 정점으로 이동할 수 있는 경우
- degree: 정점에 연결된 edge의 수
  - in-degree: 정점으로 들어오는 edge의 수
  - out-degree: 정점에서 나가는 edge의 수
- weighted graph: edge에 가중치가 있는 graph

### Graph Representation

- Adjacency Matrix
  - 2차원 배열로 표현한다.
  - undirected graph에서는 대각선을 기준으로 대칭이다.
  - directed graph에서는 대칭이 아니다.
  - edge가 존재하면 1, 존재하지 않으면 0으로 표현한다.
  - row sum은 out-degree, column sum은 in-degree이다.
- Adjacency List
  - 각 정점마다 연결된 정점들을 linked list로 표현한다.
  - out-degree 또는 in-degree 둘중에 하나로만 구현이 가능해 반대를 구하려면 모든 정점을 순회해야 한다.
- Orthogonal Representation
  - linked list를 두 개 사용하여 각 정점의 out-degree와 in-degree를 모두 구현한다.
- Seuqence Representation
  - 앞 부분은 각 정점이 위치한 node의 index를 저장하고 뒷 부분은 각 정점의 out-degree를 저장한다.
- Adjacency Multi List
  - edge를 기준으로 표현한다.
  - edge가 연결하는 2 vertex와 연결된 경로를 저장한다.
  - adjacency list는 각 처음으로 자기 자신 등장하는 edge list를 가르키고 path를 통해 나머지 길을 찾는다.
