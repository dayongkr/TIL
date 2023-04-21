# 자료구조개론 8주 차

## Polynomials

Polynomials에 대한 설명을 이어서 하셨다.

### Memory reuse

linked list를 구현하다보면 malloc을 많이 사용해서 system call을 많이 하는 경우가 생기는데 이는 성능에 좋지 않다. 따라서 malloc을 최소화하기 위해 안 쓰는 memory들을 지우지 않고 memory pool로써 모아두다가 다시 사용하는 방법을 사용한다.

> memory pool 또한 linked list로 구현한다.

구현 방법은 간단하다. 새로운 노드를 얻으려면 avali list가 비어 있지 않으면 맨 앞 노드를 가져오고 avail은 다음 노드를 가리키게 한다. 만약에 비어 있으면 malloc을 사용해서 새로운 노드를 만들고 그 노드를 반환한다. 그리고 다 쓴 노드를 반환하려면 그 노드를 avail list의 맨 앞에 추가하면 된다. 굳이 뒤에 추가하면 노드를 타고 끝까지 가야하는 불필요한 과정이 생기기 때문에 맨 앞에 추가하는 것이다.

### Circular Representation of Polynomials

Circular linked list는 구조상 앞이 어딘지 알 수는 없다. 따라서 head를 가리키는 포인터가 필요하다. 그래서 존재할 수 없는 값을 가진 node를 head와 rear 사이에 두고 head는 그 node를 가리키고 rear는 그 node의 next를 가리키게 한다. 이렇게 하면 head와 rear를 구분할 수 있다.

## Equivalence Classes

Equivalence는 자기 자신과는 항상 Equivalence하고 x와 y가 equivalence하면 y와 x는 equivalence하고 x와 y가 equivalence하고 y와 z가 equivalence하면 x와 z도 equivalence하다.

이는 seq라는 각 요소에 해당하는 list를 만들고 각 요소에 equivalence한 요소들을 linked list로 연결시키는 방법으로 구현할 수 있다. 각 seq 요소에는 해당하는 linked list의 last요소를 가르키고 있다.

### 구현 방법

이를 가지고 equivalence를 출력하는 방법은 일단 해당 seq 요소에 있는 1차적인 linked list의 요소들을 출력하고 stack에 push를 한다. 그리고 stack이 비어 있을 때까지 pop을 하면서 그 pop한 요소의 linked list를 출력하고 그 linked list의 요소들을 stack에 push한다. 이렇게 하면 모든 요소를 출력할 수 있다. 이렇게 하면 중복이 발생할 수 있는데 이는 out이라는 배열을 만들어서 해당 요소가 이미 출력 되어 있는지 확인을 할 수 있게 구현을 하면 된다.
