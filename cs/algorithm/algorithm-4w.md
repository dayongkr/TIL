# 알고리즘 4주 차

## Hashing

기존의 comparison model을 사용해서 find를 하면 최소 O(log n)의 시간이 걸린다.

왜냐하면 comparison은 의사 결정 트리가 binary tree인데 이때 최소 높이는 log n이기 때문에 O(log n)이 걸린다. 이보다 빠르게 find를 할 수 있는 방법이 direct accessing인데 index가 너무 클 수 있기 때문에 인덱스를 더 작은 범위로 매핑하는 방법을 사용하는데 이것이 hashing이다.

hashing을 구현하는 방법은 다음과 같다.

1. division method
   1. h(k) = k mod m
   2. 입력값에 따라 collision이 많이 발생할 수 있다.
2. universal hashing
   1. h(k) = ((ak + b) mod p) mod m
   2. p는 prime number이고 a, b는 0 ~ p-1 사이의 임의의 정수이다.
   3. 입력값에 영향을 받지 않는다.
   4. 즉 non-deterministic하다.
   5. m이 최소한 저장될 데이터 개수의 linear하게 증가하면 chain의 크기는 상수가 된다.
      1. 충돌 가능성 -> 1/m 따라서 chain의 크기는 1 + (n-1)/m이 되기 떄문에 상수 크기가 된다.

그래도 충돌이 발생할 수 있는데 이를 해결하기 위해 아래의 방법을 사용한다.

1. open addressing
   1. 기존에 가지고 있던 테이블에서 빈 공간을 찾아서 저장한다.
2. chaining
   1. linked list를 사용해서 collision이 발생하면 linked list에 추가한다.
   2. 추가 공간이 필요하다.
