# 자료구조개론 9주 차

## Trees Pt.1

일차원적, sequential 하게 저장하는 것이 효율적이지 않을 떄 사용하는 자료구조이다.

Tree란 하나 또는 그 이상의 노드들의 유한한 집합이다. node들은 n >=0 개의 disjoint sets로 나뉘어진다.

> disjoint set이란 서로소 집합으로 공통 원소가 없는 두 집합이다.

### Tree Terminology

- Subtree
  - 노드와 그 자손들로 이루어진 트리
- Size of a tree
  - node의 개수
- Degree of a node
  - The number of subtrees
  - e.g. Leaf -> 0 degree
- Degree of a tree
  - Maximum degree of the nodes in the tree
- Height(depth) of a tree
  - Maximum level of any node in the tree
- Width of a tree

  - The size of the largest level

- Parent
  - 부모 노드
- Child
  - 자식 노드
- Sibling
  - 같은 부모를 가지는 노드
- Ancestor
  - 루트 노드까지의 경로에 있는 모든 노드
- Descendant
  - 자식 노드까지의 경로에 있는 모든 노드

### Tree Representation

#### K-array Tree

k개의 자식을 가지면 배열에 data을 포함하여 k개의 child를 가리킬 수 있는 포인터를 저장할 수 있는 공간을 fixed size로 할당한다. 하지만 이렇게 하면 불필요한 공간(n(k-1)+1)이 낭비가 된다.

#### Left child-Right sibling Representation

data와 left child, right sibling 포인터를 저장하는 구조이다. 이렇게 하면 불필요한 공간이 비교적 없어진다. 다만 parent와 직접적으로 연결되어 있지 않는 sibling node들은 parent를 찾기 위해서 불필요한 과정을 거쳐야 한다.

#### Left Child-Right Child Representation

data와 left child, right child 포인터를 저장하는 구조이다. 이렇게 하면 parent를 찾기 위해서 불필요한 과정을 거치지 않아도 된다. 이 표현법으로 나타낸 트리를 Binary Tree라고 한다.

### Binary Tree

Binary Tree는 Tree와 다른데 아래 2가지 큰 차이점이 있다.

- 각 노드의 최소 갯수는 0개이다.
  - tree는 1개
- children의 순서가 의미가 있다.
  - tree는 의미가 없다.

tree를 binary tree로 변환하는 것이 가능한데 left child-right sibling 표현법으로 먼저 변환한 후 left child-right child 표현법으로 변환하면 된다.

#### Properties of Binary Tree

- The maximum number of nodes at level i of a binary tree is 2^(i-1)
- The maximum number of nodes in a binary tree of height(depth) h is 2^h - 1
- leaf node의 개수는 degree가 2인 node의 개수보다 1개 많다.

#### Full Binary Tree & Complete Binary Tree

- Full Binary Tree
  - node를 추가하려면 level이 하나 늘어나야 하는 binary tree
- Complete Binary Tree
  - 마지막 level을 제외하고 모든 level이 완전히 채워져 있는 binary tree
  - 마지막 level은 왼쪽부터 순서대로 채워져 있다.

#### Array Representation of Binary Tree

- parent(i) = i/2
- leftChild(i) = 2i
- rightChild(i) = 2i+1

이러한 사실을 이용하면 pointer 없이도 array로 binary tree를 표현할 수 있다.

#### Linked Representation of Binary Tree

structure을 이용하여 data, left child pointer, right child pointer를 저장하여 표현하는 방법이다.
