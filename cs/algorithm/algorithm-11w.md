# 알고리즘 개론 11주 차

## 그리디 알고리즘

그리디 알고리즘은 local optimum을 선택하여 global optimum을 찾는 알고리즘이다. 즉, 각 단계에서 최적의 선택을 하여 최종적인 해답을 구하는 방법이다. 그리디 알고리즘은 최적의 해를 보장하지 않는다.

### Activity Selection Problem

Activity Selection Problem은 다음과 같은 문제이다.

- n개의 활동이 있다.
- 각 활동은 시작시간과 종료시간이 있다.
- 한 활동을 선택하면 그 활동과 겹치는 활동은 선택할 수 없다.
- 최대한 많은 활동을 선택하고 싶다.
- 최대 몇 개의 활동을 선택할 수 있는가?

이 문제를 그리디 알고리즘으로 해결할 수 있다. 시작시간이 빠른 순서대로 활동을 선택하면 된다. 즉 sorting을 하여 빨리 끝나는 활동을 선택하면 된다. 이 과정에서 priority queue를 사용하면 더욱 효율적으로 구현할 수 있다.

optimal substructure를 만족하는지 확인해보자. optimal substructure는 다음과 같다.

- A가 최적의 해라고 가정하자.
- A에서 마지막으로 선택한 활동을 a라고 하자.
- A에서 a를 제외한 나머지 활동들을 A'라고 하자.
- 만약에 A' 보다 optimal solution B가 존재한다고 가정하자.
- 그러면 B에 a가 포함될 수 있다.
- 따라서 a를 포함한 B는 A보다 optimal solution이다.
- 따라서 a를 포함한 set은 optimal solution이다.

optimal substructure이란 optimal solution을 구하기 위해 필요한 subproblem들이 optimal solution을 구하기 위해 필요한 subproblem들로 구성되어 있다는 것이다.

여기서 greedy choice property를 알아보면 다음과 같다.

- 첫 번째 활동을 포함하지 않는 optimal solution이 있다고 가정하자.
- 해당 optimal solution의 첫 번째 활동과 항상 교체할 수 있다.

즉 첫 번째 활동을 포함하지 않는 optimal solution이 있다면 그것은 첫 번째 활동을 포함하는 optimal solution과 같거나 더 작다는 것이다.

### Huffman Coding

Huffman Coding은 다음과 같은 문제이다.

- n개의 문자가 있다.
- 각 문자는 빈도수를 가지고 있다.
- 각 문자에 대해 binary code를 부여하고 싶다.
- 빈도수가 높은 문자에는 짧은 binary code를 부여하고 싶다.

이는 binary tree로 구현할 수 있는데 현재 빈도수가 가장 작은 두 문자를 선택하여 하나의 노드로 만들고 빈도수를 더한 뒤 다시 빈도수가 가장 작은 두 문자를 선택하여 하나의 노드로 만들고 빈도수를 더하는 과정을 반복하면 된다. 이 과정에서 priority queue를 사용하면 더욱 효율적으로 구현할 수 있다.

huffman code는 prefix code이다. 즉 어떤 문자의 code가 다른 문자의 code의 prefix가 되지 않는다. 따라서 어떤 문자열을 huffman code로 encoding하면 decoding할 때 모호함이 없다. 다만 같은 인풋으로 huffman code를 만들었다고 해도 다른 huffman code가 나올 수 있다.

### Knapsack Problem

0-1과 다르게 fractional knapsack problem은 물건을 쪼갤 수 있다. 따라서 greedy algorithm을 사용하여 해결할 수 있다. 물건을 가격순으로 정렬한 뒤 가격이 높은 물건부터 채워넣으면 된다.

### Minimum Spanning Tree

Minimum Spanning Tree는 다음과 같은 문제이다.

- n개의 노드가 있다.
- 각 노드는 연결되어 있다.
- 각 edge는 weight를 가지고 있다.
- 모든 노드를 연결하는 edge들의 weight의 합이 최소가 되도록 하고 싶다.
- cycle이 존재하면 안된다.
- undirected graph이다.
- 같은 weight을 가지면 추가 조건으로 뽑아 unique하게 만든다.

이 문제는 optimal substructure를 만족한다. 왜냐하면 더 optimal한 solution이 T'1이 있다고 하면 T' = {u,v} + T'1 + T2가 있어야 하는데 이는 우리의 T가 optimal solution이라는 것에 모순이다.

또한 다르게 연결된 부분이 있으면 이를 least weight edge로 대체할 수 있다. 따라서 greedy choice property를 만족한다.

추가로 개념을 정리하면 cut은 노드를 두 개의 그룹으로 나누는 것이다. Red rule은 가장큰 weight은 mst에 포함하지 않고 blue rule은 가장 작은 weight은 mst에 포함한다는 것이다.

#### Prim's Algorithm

Prim's Algorithm은 다음과 같다.

- 임의의 노드를 선택한다.
- 선택한 노드와 연결된 edge들을 priority queue에 넣는다.
- priority queue에서 가장 작은 edge를 선택한다.
- 해당 edge의 끝점이 선택되지 않았다면 선택한다.
- 선택된 edge를 mst에 추가한다.
- 모든 노드가 선택될 때까지 반복한다.
- mst를 반환한다.

시간 복잡도는 O(ElogV)이다.
