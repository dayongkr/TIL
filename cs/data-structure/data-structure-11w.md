# 자료구조개론 11주 차

## Heap

Complete Binary Tree이다. 즉 마지막 레벨을 제외하고는 모든 노드가 꽉 차있고 마지막 레벨은 왼쪽부터 채워져있다. 또한 모든 노드는 자신의 자식보다 크거나 같은 값을 가진다. 이를 Max Heap이라고 한다. Min Heap은 반대이다.

Heap은 보통 Priority Queue를 구현할 때 사용한다. Priority Queue는 우선순위가 높은 순서대로 요소를 꺼내는 자료구조이다. Sorted array 또는 unordered array로 구현하면 결국 삽입 + 삭제 과정이 O(n)이지만 Max Heap을 사용하면 삽입과 삭제가 O(logn)에 가능하다.

### Heap Insertion

Heap의 마지막 노드에 새로운 요소를 넣고 부모와 비교하면서 부모보다 크면 swap한다. 이를 반복하면 된다.

### Heap Deletion

Heap의 마지막 node를 삭제하고 root에 넣는다. 그리고 root부터 자식들과 비교하면서 자식보다 작으면 swap한다. 이를 반복하면 된다.

## Binary Search Tree

이는 non complete binary tree이다. 따라서 height이 logn을 만족하지 않을 수 있다. Binary Search Tree의 특징으로는 아래와 같다.

- 왼쪽 자식은 부모보다 작다.
- 오른쪽 자식은 부모보다 크다.
- 중복된 값은 없다.
- inorder traversal을 하면 정렬된 값을 얻을 수 있다.

### Searching a BST

- recursive
  - node가 null이면 null을 반환한다.
  - node의 값이 찾는 값보다 크면 왼쪽 자식으로 재귀호출한다.
  - 그렇지 않으면 오른쪽 자식으로 재귀호출한다.
  - node의 값이 찾는 값과 같으면 node를 반환한다.
- iterative
  - 찾는 값보다 node의 값이 크면 왼쪽 자식으로 이동한다.
  - 그렇지 않으면 오른쪽 자식으로 이동한다.
  - 찾으면 node를 반환한다.
  - node가 null이라서 반복문이 종료되면 null을 반환한다.

### BST Insertion

동일한 값이 존재하면 삽입하지 않는다. 삽입할 위치 즉 leaf node를 찾고 넣으려는 값이 해당 node의 값보다 작으면 왼쪽 자식으로 넣고 크면 오른쪽 자식으로 넣는다.

### BST Deletion

- leaf node인 경우
  - 그냥 삭제한다.
- 자식이 하나인 경우
  - 삭제하려는 node의 부모와 삭제하려는 node의 자식을 연결한다.
- 자식이 두 개인 경우
  - 오른쪽 subtree에서 가장 작은 값으로 삭제하려는 node의 값을 바꾼다.
  - 왼쪽 subtree에서 가장 큰 값으로 삭제하려는 node의 값을 바꾼다.
  - 둘 중에 하나 선택하면 된다.
