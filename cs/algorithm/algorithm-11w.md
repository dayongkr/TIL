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
