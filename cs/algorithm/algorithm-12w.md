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
