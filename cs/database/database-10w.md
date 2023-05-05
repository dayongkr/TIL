# 데이터베이스개론 10주 차

이제는 Access Methods 쪽을 공부하게 된다.

해당 챕터에서는 B+tree 자료구조를 기반으로 진행하기 떄문에 이에 대한 사전 지식이 필요하다. 따라서 이를 추가적으로 공부하고 따로 다른 글에 정리했다.

## Indexing?

Indexing은 big set에서 몇 가지 hints를 통해 작은 subset을 찾는 것이다. 사전, 도서관, 은행, 구글 검색등 모든 곳에서 indexing을 사용한다. 이 때 검색을 위한 key를 Search key라고 하면 이는 단어, 제목, 저자, 키워드, 계정 id등이 될 수 있다.

이러한 indexing을 저장하는 solution으로는 B-tree index, inverted index등이 있으며 DB에서는 존재 유무를 빠르게 확인할 수 있는 bloom filter를 사용하기도 한다.

### Basic Concept

원하는 data에 접근하는 속도를 높이기 위해 사용하는 것으로 search key는 attributes의 set이다. index filed에는 data entry 또는 index entry 이라고 불리는 records로 이루어져있다. 이 때 record는 search key와 pointer로 이루어져있다.

### Index-based Access on Heap Files

index를 사용하지 않으면 full table scan 또는 binary search를 통해 원하는 data를 찾아야 한다. 하지만 index를 사용하면 index entry를 통해 원하는 data를 찾을 수 있다. 이때 range queries는 clustering factor에 의해 영향을 받는다.

DB는 미리 만들어둔 index 통계 자료를 통해 Excution Plan을 짠다.

모든 일에는 Trade-off가 있기 때문에 index-based access에서도 trade-off가 발생하는데 일단 장점으로는 search time이 빨라지고 이에 따른 단점은 공간/삽입/삭제 관점에서 overhead가 발생한다. 하지만 탐색이 중요한 상황에서는 index를 사용하는 것이 좋다.

#### Data Entry

data entries에는 3가지 종류가 있다.

- <k, data record itself>
  - data record 그 자체가 data entry가 된다.
- <k, rid of data record with key value k>
  - rid는 record id로 data record를 찾기 위한 pointer이다.
- <k, list of rids of data records with key k>
  - k에 해당하는 여러 개의 rids list를 가지고 있다.

### Range Search

일단 기본적으로 sorted data이면 binary search를 하는 것이 좋지만 여기서 더 나아가 index file을 만들고 이를 binary search를 하면 더 빠르게 찾을 수 있다.

이러한 index file을 만들 때 사용하는 방법으로는 2가지가 있다.

- ISAM (Index Sequential Access Method)
  - static한 tree structure로 insert/delete 과제어서 트리의 구조가 변경되지 않는다.
  - leaf pages는 sequential하게 sorting되어 있기 때문에 다음 leaf page을 위한 pointer가 필요 없다.
  - leaf page가 꽉 차면 overflow page를 만들어서 저장한다. 따라서 unbalanced tree가 될 수 있다.
- B+tree
  - dynamic한 tree structure로 insert/delete를 통해 트리의 구조가 변경된다.
  - 다음 leaf page을 위한 pointer가 필요하다.
  - 재구조화를 통해 balanced tree를 유지한다.
  - tree의 node는 left child, key, right child pointer로 이루어져있고 leaf node는 sibling pointer를 가지고 있다.

#### B+tree Stearch

Heap File에 records들이 같은 page에 잘 모여 있는 경우를 Well-clustered 아닌 경우를 Non-clustered라고 한다. 이 경우 여러 page를 거쳐가야 하기 때문에 physical I/O가 많이 발생한다.

이때 이를 분석하기 위해 Cluster factor를 사용하는데 이는 leaf page에 있는 record의 수를 leaf page의 크기로 나눈 것이다. 이 값이 1에 가까울 수록 well-clustered이다.
