# 알고리즘개론 12주 차

## Kruskal's Algorithm

Kruskal's Algorithm은 Minimum Spanning Tree를 찾는 알고리즘으로 edge를 가중치의 오름차순으로 정렬한 후, 가중치가 가장 작은 edge부터 선택하면서 disjoint set을 이용하여 cycle이 생기지 않도록 하는 edge를 선택한다. 따라서 disjoint set을 어떻게 구현하느냐에 따라서 시간복잡도가 달라진다.

### Disjoint Set

Disjoint Set은 서로 중복되지 않는 부분집합들로 나누어진 원소들에 대한 정보를 저장하고 조작하는 자료구조이다. 우리는 kruskal's algorithm에서 find와 union 그리고 make set을 사용한다. find는 어떤 원소가 어떤 집합에 속해있는지를 찾는 연산으로 pointer를 사용하면 O(1)의 시간복잡도를 가진다. make set은 원소 하나를 집합으로 만드는 연산으로 O(1)의 시간복잡도를 가진다. union은 두 집합을 합치는 연산이므로 set A,B가 있으면 시간 복잡도는 O(A) 또는 O(B)가 된다.

kruskal에서 union은 총 n-1번 호출되는데 작은 쪽에서 큰쪽으로 union을 하면 union이 2배씩 증가하므로 시간복잡도는 O(nlogn)이 된다. 이를 amortized analysis를 통해 분석하면 Union operation은 O(logn)의 시간복잡도를 가진다.

### Amortized Analysis

Amortize란 상환을 의미하며, amortized analysis는 한 동작이 최악의 경우에는 비싸지만 평균적으로는 싸다는 것을 보이는 분석 기법이다. 이를 분석하는 방법은 크게 3가지가 있다.

#### Aggregate Method

단순히 전체를 보고 평균을 내는 방법이다. 예를 들어서 스택의 동작을 생각해보자. 스택은 push, pop, multi-pop이 있다. push는 O(1)의 시간복잡도를 가지고 pop은 O(1)의 시간복잡도를 가진다. multi-pop은 k개의 원소를 pop하는 연산으로 O(k)의 시간복잡도를 가진다. 이때 multi-pop의 평균 시간복잡도를 구해보자. multi-pop은 k번의 pop을 수행하므로 k번의 pop에 대한 시간복잡도를 구하고 k로 나누면 된다. 따라서 평균 시간복잡도는 O(1)이 된다.

#### Accounting Method

미리 비용을 지불하고 분석하는 것으로 총 amortized cost는 총 actual cost보다 상한에 있어야 한다. 예를들어 PUSH를 하는 Actual Cost는 1이지만 Assigned Amortized Cost는 POP 할 것을 미리 계산해서 2로 지정한다. 그러면 나머지 연산은 0이 된다. 따라서 평균적으로 1이 된다.

#### Potential Method

위치에너지 컨셉을 가지는 방법으로 actual cost + potential i번째 연산을 수행한 자료구조 - potential i-1번째 연산을 수행한 자료구조로 계산한다. 예를들어 stack에서는 potential을 stack에 남아있는 원소의 개수로 정의한다.

## Graph

Graph란 Vertex와 Edge로 이루어진 nodes들의 set이다. 보통 E = O(V^2)이다.

- undirected graph
  - edge가 방향성이 없는 그래프
- directed graph
  - edge가 방향성이 있는 그래프
- connected graph
  - 모든 vertex가 서로 연결되어 있는 그래프
- unconnected graph
  - 모든 vertex가 서로 연결되어 있지 않은 그래프
- bipartite graph
  - vertex를 두 개의 그룹으로 나눌 수 있는 그래프
  - 그룹 내의 vertex들은 서로 연결되어 있지 않고 다른 그룹의 vertex들과만 연결되어 있다.
- Acyclic graph
  - cycle이 없는 그래프
- multigraph
  - 두 vertex 사이에 여러 개의 edge가 존재할 수 있는 그래프
- graph가 spase하면 adjacency list를 사용하고 dense하면 adjacency matrix를 사용한다.
  - sparse: E = O(V)
  - dense: E = O(V^2)
- adjecny matrix로 undirected graph를 표현하면 대각선은 필요없고 대칭이기 때문에 절반만 저장하면 된다.
- adjency list는 O(V+E)의 공간복잡도를 가진다.
  - V = head node
  - E = linked list

### BFS

방문하지 않은 Edge들을 Queue에 넣고 방문한 Edge들을 visited에 넣는다. 이를 반복하면 BFS가 된다. BFS는 O(V+E)의 시간복잡도를 가진다. 교안에서는 방문 안한 Edge를 white, 방문한 Edge를 black, 방문한 Edge를 queue에 넣은 Edge를 gray로 표현한다.

방문하면서 count를 세면 한 노드에서 다른 노드로 가는 최단 경로를 구할 수 있다.

### DFS

DFS는 깊이 우선으로 보통 재귀를 이용해서 구현한다 즉 방문 가능한 Edge를 찾으면 바로 방문하고 더이상 방문할 수 없으면 다시 돌아와서 다른 Edge를 찾는다. 이를 반복하면 DFS가 된다. DFS는 O(V+E)의 시간복잡도를 가진다.

- Tree edge
  - 새로운 vertex를 방문하는 edge
- Back edge
  - 현재 vertex의 ancestor로 가는 edge
- Forward edge
  - 현재 vertex의 descendant로 가는 edge
  - tree edge가 아닌
- Cross edge
  - 현재 vertex의 descendant가 아닌 다른 vertex로 가는 edge

Back edge가 존재하면 cycle이 존재한다. 또한 cycle이 존재하지 않다면 back edge가 존재하지 않는다.

DFS 코드에서 인접한 vertex가 gray이면 cycle이 존재한다고 판단할 수 있다. undirected acyclic forest(E<=V-1)에서는 O(V)만에 cycle을 찾을 수 있다.

- DAG
  - directed acyclic graph
  - cycle이 없는 directed graph
- Forward
  - 만약에 Graph가 acyclic이면 back edge가 존재하지 않는다.
- Backward
  - 만약에 back edge가 존재하면 cycle이 존재한다.
  - contrapostive: G가 cycle이 있다고 가정한다.
    - v가 제일 먼저 방문되는 vertex라고 가정한다.
    - u는 v의 predecessor이다.
    - v가 방문하면 모든 cycle은 white가 된다.
    - 모든 인접한 vertex를 방문한다.
    - 때문에 u->v는 grey to grey가 되므로 back edge가 된다.
    - 따라서 cycle이 존재하면 back edge가 존재한다.
