# 문제해결 10주 차 Reveiw

## Binary Search

함수 인자에 있는 배열은 포인터와 같은 역할을 하기 때문에 따로 크기를 정의하지 않는다. 또한 포인터이기 때문에 배열의 크기를 알 수 없어 매개변수로 받아야 한다. 2차원 배열의 경우에는 가로의 길이는 정의해줘야 한다.

> e.g. int (\*b)[10]

## Weekly Problem Solving Review

### H-Index II

[LeetCode](https://leetcode.com/problems/h-index-ii/)

위 문제는 i 번째 논문이 인용된 횟수가 citations\[i]라고 할 때, h번 이상 인용된 논문이 h편 이상임을 만족하는 h의 최댓값을 구하는 문제이다.

단 log 시간 복잡도로 풀어야 한다.

naive하게 생각하면 처음부터 선형 탐색을 하면서 h번 이상 인용된 논문이 h편 이상인지 확인하면 된다. 하지만 이렇게 하면 시간 복잡도가 O(n)이 되어버린다.

따라서 이분 탐색 중 first occurence of target을 이용하여 O(log n)으로 풀어야 한다.

### Search in Rotated Sorted Array

[LeetCode](https://leetcode.com/problems/search-in-rotated-sorted-array/)

위 문제는 오름차순으로 정렬된 배열이 회전했을 수 있는 배열이 주어졌을 때, target이 배열에 존재하면 그 인덱스를, 존재하지 않으면 -1을 반환하는 문제이다.

먼저 맨 앞이 뒤보다 크다면 회전이 되었다는 것이다. 이를 이용하여 이분 탐색을 진행한다. mid 기준 l과 r을 비교하면서 sorted된 부분을 찾아간다. 그리고 target이 sorted된 부분에 속한다면 그 부분에서 이분 탐색을 진행한다. 만약 target이 sorted된 부분에 속하지 않는다면 다른 부분에서 이분 탐색을 진행한다.

### Median of Two Sorted Arrays

[LeetCode](https://leetcode.com/problems/median-of-two-sorted-arrays/)

위 문제는 두 개의 정렬된 배열이 주어졌을 때, 두 배열의 중앙값을 구하는 문제이다.

병합해서 풀면 O(m+n)이 되어버린다. 따라서 이분 탐색을 이용하여 O(log(m+n))으로 풀어야 한다.

먼저 두 배열의 길이를 m, n이라고 하자. m+n이 홀수일 때와 짝수일 때를 나누어 생각해야 한다. 한 배열의 index를 가르키는 변수 i가 주어지면 해당 변수로 다른 배열의 index를 가르키는 변수를 만들 수 있다. 짝수일 경우 j = (m+n)/2 - i, 홀수일 경우 j = (m+n+1)/2 - i로 반올림을 해준다.

이제 한 배열을 이분 탐색하면 어차피 다른 배열의 포인터는 이에 따라 움직이게 된다. 따라서 O(log(min(m,n)))이 된다.

> 둘 중에 작은 배열을 선택해 이분 탐색을 진행하는 것이 더 효율적이다. 따라서 min(m,n)이 된다.
