# 문제해결 11주 차 Review

## Weekly problem

### 856. Score of Parentheses

> [문제 링크](https://leetcode.com/problems/score-of-parentheses/)

짝이 있는 parentheses로 이루어진 문자열이 주어진다. 이 문자열을 score로 변환하는 규칙은 다음과 같다.

- `()`는 1점이다.
- `AB`라면 `A+B`의 점수이다.
- `(A)`라면 `2*A`의 점수이다.

문자열을 score로 변환한 값을 구하라.

Stack에 `(`를 만나면 -1을 push하고 `)` pop을 하고 이때 pop한 값이 -1이라면 1을 넣어주고 아니라면 -1이 나올때 까지 더하고 2를 곱해준다.

### 946. Validate Stack Sequences

> [문제 링크](https://leetcode.com/problems/validate-stack-sequences/)

정수형 pushed, poped 배열이 주어지면 초기 빈 스택에 push와 pop을 해서 두 배열을 같게 만들 수 있는지 여부를 반환하라.

일단 pushed 배열을 순회하면서 스택에 push를 하다가 poped 배열의 요소와 같은 값이 나오면 pop을 해준다. 이를 반복했을 때 popped 배열의 모든 요소가 pop 되었다면 true를 반환하고 아니라면 false를 반환한다.

> hint. stack 사용

### 462. Minimum Moves to Equal Array Elements II

> [문제 링크](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

n size를 가진 정수형 배열 nums가 주어지면 배열의 모든 요소가 같아지도록 요소를 증가시키거나 감소시키는 (+1 or -1) 최소 횟수를 구하라.

각 요소를 최소로 증가시키거나 감소시키려면 좌우 대칭이어야 한다. 즉 중간값을 구하면 최소 횟수를 구할 수 있다. median을 구하려면 정렬이 필요한데 이는 stdlib의 qsort를 사용하면 된다. qsort 함수는 array, size, element size, compare 함수를 인자로 받는다.

```c
int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int minMoves2(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    int median = nums[numsSize / 2], moves = 0;
    for (int i = 0; i < numsSize; i++) {
        moves += abs(nums[i] - median); // abs: 절대값
    }
    return moves;
}
```
