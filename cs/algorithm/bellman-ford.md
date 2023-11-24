# Bellman-Ford

## Warmups

undirected graph 같은 경우에는 뒤로 다시 돌아올 수 있으므로 directed graph로 제한하여 수업에서 다루었다.

SSSP algorithm이 O(V(V+E))인데 이를 어떻게 O(VE)로 줄일 수 있을까?

- BFS, DFS로 s에서 reachable한 모든 vertex를 찾으면 된다.
  - reachable한 모든 vertex를 찾는데 O(V+E)이다.
  - reachable한 모든 vertex를 포함하는 그래프 대상으로 SSSP를 수행하면 된다.
  - 이러면 V' = O(E') = O(E))이므로 O(VE)가 된다.

## Simple Shortest Path

Simple shortest path는 한 vertex를 한 번만 지나는 path를 의미한다.

- Claim 1: 만약에 유한한 shortest path가 존재한다면, 그 path는 simple하다.
  - Proof: By contradiction
    - 만약에 shortest path가 simple하지 않다면, cycle이 존재한다.
    - cycle을 제거하면 더 짧은 path가 존재하게 되므로 shortest path가 아니다.
    - 따라서 shortest path는 simple하다.

## Negative Cycle Witness

Witness는 cycle을 구성하는 edge들 중에서 negative cycle을 구성하는 edge를 의미한다.

- k-Edge Distance: k개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight
- Idea! V-1개 이하와 V개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight를 구하자
  - 만약에 shroteest path != - Infinity라면 V-1개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight는 V개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight와 같다. 따라서 shortest path는 simple하다.
  - 만약에 shortest path < V-1개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight라면
    - 나머지 edge가 -Infinity인 거고 이는 negative cycle을 의미한다.
- Claim 2: 만약에 shortest path가 -Infinity라면 v는 witness에서 reachable하다.
  - Proof: s으로부터 reachable한 모든 negative-weight cycle은 witness를 포함한다는 것을 보이면 된다.
  - 만약에 C가 witness를 포함하지 않는다면, V-1개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight는 V개 이하의 edge를 사용하여 구성할 수 있는 path의 최소 weight보다 작을 수 있기 때문에 shortest path가 -Infinity가 될 수 없다.

## Bellman-Ford Algorithm

- Vertex + 1의 Level로 graph duplication을 수행한다.
- 각 Edge는 다음 level의 vertex로 연결한다.
- 각 vertex의 distance는 0 level의 source vertex로부터의 shortest path distance이다.

실제에서는 매 단계마다 모든 간선을 순회하면서 모든 vertex의 distance를 업데이트한다. 업데이트 과정을 한 번 더 반복하면 negative cycle을 찾을 수 있다.

## Correctness

- Claim 3: shortest path(s0, vk) = shortest path|k|(s,v)
- Proof: By induction on k

  - Base case: k = 0
  - Inductive step: k' > k

- Claim 4: Bellman-Ford algorithm이 종료되면 shortest path가 존재한다.
  - Claim 3에 의해 shortest path가 존재한다.

## Running Time

- Bellman-Ford algorithm은 O(VE)이다.
  - 각 level에서 모든 edge를 순회하므로 O(E)
  - 각 level에서 모든 vertex의 distance를 업데이트하므로 O(V)
  - 총 O(VE)
