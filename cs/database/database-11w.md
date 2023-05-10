# 데이터베이스개론 11주 차

## B+ Tree

저번 수업에 이어서 B+ Tree에 대해서 배운다. 전에 B-tree, B+tree 둘 다 삽입 삭제도 정리했지만 간단하게 복습겸 정리하려고 한다.

### Insertion & Deletion

만약에 삽입, 삭제등으로 base table이 수정되면 매번 관련된 indexes가 바뀌어야한다.

#### Insertion

- 삽입할 leaf L을 찾는다.
  - L이 충분한 공간을 가지고 있으면 삽입하고 끝낸다.
  - 그렇지 않으면 L을 나누고 entiries를 반으로 나누고 middle key를 copy up한다.
- 분리는 index node에서 재귀적으로 발생할 수 있다.
  - index node는 똑같이 반으로 나누지만 middle key는 push up을 해야한다.
- 분리는 tree의 길이를 늘릴 수 있다.

> copy up: parent node에 복사해서 올리는 것, push up: parent node에 올리는 것

#### Deletion

- 삭제할 leaf L을 찾는다.
  - 삭제하고 나서도 반이상 차있으면 끝낸다.
  - L이 포함한 node에 sibling node에서 가져올 수 있는 entry가 있으면 가져온다.
  - 그렇지 않으면 L과 sibling node를 합친다.
- 병합이 발생하면 parent node에서는 entry(L과 sibling을 가르키는)를 삭제해야 한다.
- Merge는 root까지 전파될 수 있고 길이를 줄일 수 있다.

### Index

B+tree는 node에 최소 50% 이상의 entry가 있어야 한다. 따라서 공간 낭비가 심하다 볼 수 있다. 다만 equality그리고 range search 모두 가능하다는 장점이 있다. 또한 top levels만 메모리에 올려놓으면 된다는 장점도 있다.

B+tree 말고 hashing을 사용할 수도 있다. 하지만 equality search만 가능하고 range search는 불가능하다. 이외로 값의 범위가 작을땐 bitmap을 사용할 수 있고 multi-dimensional data는 R-tree를 사용할 수 있다.

## Exteranl Sorting

Operator Evaluator에서는 두가지 방법으로 sorting을 수행할 수 있다. 하나는 in-memory sorting이고 다른 하나는 external sorting이다. in-memory sorting은 메모리에 모든 데이터를 올려서 sorting을 수행하는 것이고 external sorting은 메모리에 올릴 수 없는 데이터를 sorting하는 것이다. 기본 알고리즘은 load-sort-store이다.

### Sorting Problem

만약에 1mb 메모리에서 1gb 데이터를 sorting해야한다면 어떻게 해야할까? 이런 문제를 sorting problem이라고 한다. 이 문제를 해결하기 위해서는 external sorting을 사용해야한다.

PGA에 해당하며 System Global Area 즉 SGA에 있는 Buffer Cache와 분리되어 있다.

### 2-Way Merge Sort (wtih 3 Buffers)

2개는 input buffer이고 1개는 output buffer이다. 2-way merge sort는 2개의 input buffer에 데이터를 채우고 sorting을 수행한다. 그리고 output buffer에 데이터를 채운다. 그리고 output buffer가 다 차면 output buffer를 disk에 쓰고 다시 채운다. 이 과정을 반복한다.

이렇게하면 2-way merge sort는 각 pass에 2개의 runs을 읽고 그들의 records를 병합하고 그 결과를 output buffer에 쓴다. 이러면 2^(s-i)개의 runs이 생성된다.

> i는 현재 pass의 number, s는 전체 pass의 수이다.

### General External Merge Sort (with B pages)

만약에 B개의 buffer pages와 N개의 pages가 있다면 N/B개의 runs이 생성된다. 이렇게 buffer가 많아지면 merge sort의 pass가 줄어들고 disk I/O가 줄어든다. 하지만 buffer가 많아지면 메모리를 많이 사용하게 된다. 또한 CPU-intensive하다.

### Some Optimization

- Replacement sort
  - 더 긴 runs를 생성하여 runs의 갯수를 줄인다.
- Blocked I/O
  - merge passes를 최적화하여 disk I/O를 줄인다.
- Double buffering
  - I/O를 overlap하여 CPU의 이용을 극대화한다.

#### Blocked I/O

해당 최적화 방법은 일정 크기를 가진 block 단위로 disk에서 각 input buffer로 가져와가지고 merge pass를 줄이는 최적화 방식이다.

Blocking factor 즉 cluster size를 늘리면 pass를 줄여 I/O 시간을 줄일 수 있다. 하지만 메모리를 많이 사용하게 된다. 만약에 pass의 수가 많아지면 I/O 시간이 늘어나게 된다. 이 둘의 trade off를 잘 생각해서 optimal한 cluster size를 정해야한다.

#### Double Buffering

I/O 요청이 완료되고 Sorting 하는 동안 기다리는 시간을 줄이기 위해 각 buffer에 대해 2개의 page를 사용한다. 하나는 I/O를 받고 다른 하나는 sorting을 수행한다. 이렇게 하면 I/O와 sorting을 overlap할 수 있다.

### Using B+ Tree for Sorting

만약에 Clustered한 B+tree를 사용하면 좋은 생각이지만 Non-clustered B+tree를 사용하면 좋은 생각은 아니다. 왜냐하면 Non-clustered B+tree는 각 pages에 record가 랜덤하게 분포되어 있기 때문이다. 따라서 I/O가 많이 발생하게 된다.
