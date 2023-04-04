# 문제해결 5주 차 Review

## 중간고사

중간고사는 4문제로 구성되어 있었다. 슬라이드와 강의 영상은 제공하지만 보지 않고도 풀 수 있도록 준비하는 것이 좋겠다. 그 외 gpt 모델을 사용한 extension은 사용 못하고 서칭도 못한다.

## Weekly Challeges Solution

전부 linked list에 대한 문제 였다.

### P1 - Add Two Numbers

> [LeetCode - Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)

음수가 아닌 정수로 이루어진 비어 있지 않은 2가지 linked list가 주어지는데 각 linked list는 반대 순서로 저장 되어 있다. 두 linked list에서 같은 index를 가진 node들을 더한 값을 linked list로 반환해라. 단 leading zero는 없어야 하고 만약에 10 이상의 수가 나오면 carry를 해야 한다.

#### P1 - Solution

``` c
typedef struct ListNode node_t;

node_t *new_digit(int digit)
{
  node_t *n;
  n = (node_t *)malloc(sizeof(node_t));
  n->val = digit;
  n->next = 0;
  return n;
}

node_t *addTwoNumbers(node_t *l1, node_t *l2)
{
  node_t *start, *p;
  int carry = 0;

  start = p = 0;
  while (l1 || l2)
  {
    int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;

    if (!start)
      start = p = new_digit(sum % 10);
    else
    {
      p->next = new_digit(sum % 10);
      p = p->next;
    }

    carry = sum / 10;

    if (l1) l1 = l1->next;
    if (l2) l2 = l2->next;
  }

  if (carry) p->next = new_digit(carry);

  return start;
}
```

### P2 - Remove nth Node from End of List

> [LeetCode - Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

linked list가 주어지면 tail node기준으로 n번째 node를 제거해라.

> n은 zero-based index가 아니고 one-based index이다.

#### P2 - Solution

``` c
typedef struct ListNode node_t;

node_t *removeNthFromEnd(node_t *head, int n)
{
node_t *left, *right;
left = right = head;

while (n--)
  right = right->next;

if (!right)
{
  node_t *next = head->next;
  free(head);
  return next;
}

while (right->next) // last node까지 계속 연결
  left = left->next, right = right->next;

node_t *next = left->next->next;
free(left->next);
left->next = next;

return head;
}
```

### P3 - Merge k Sorted Lists

> [LeetCode - Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

k개의 list가 주어지는데 각 list는 오름차순으로 정렬되어 있다. 이 k개의 list를 하나의 sorted list로 합쳐라.

#### P3 - Solution

두 개의 list를 합칠 때는 새로운 노드를 만들 필요 없이 계속 next index를 바꿔서 합칠 수 있다. 물론 n 개의 list를 합칠 때에도 이 두 개의 list를 합치는 함수를 사용해서 합칠 수 있지만 교수님은 모든 list를 앞에서 부터 서로 비교하면서 새로운 list를 만들어서 합쳤다.

``` c
node_t *mergeKLists(node_t **lists, int listsSize)
{
  node_t *head = 0, *ptr;

  while (1)
  {
    int min = 10001, min_index = -1;
    for (int i = 0; i < listsSize; i++)
      if (lists[i] && lists[i]->val < min)
      {
        min = lists[i]->val;
        min_index = i;
      }
    if (min_index < 0)
      break; // break if all lists are empty
    if (!head)
      head = ptr = lists[min_index];
    else
    {
      ptr->next = lists[min_index];
      ptr = lists[min_index];
      // ptr = ptr -> next = lists[min_index];
    }
    lists[min_index] = lists[min_index]->next;
  }
  return head;
}
```

## Computing a Power

a를 n번 곱하는데 필요한 시간 복잡도는? 보통 O(n)이다. 하지만 O(log n)으로 줄일 수 있다.

``` c
int a = 3, n = 10, result = 1;

while (n > 0) {
  if (n % 2) {
    result = result * a;
  }
  a = a * a;
  n = n/2;
}
```

위와 같이 2 개씩 묶어서 계산하면 더 빠르게 계산이 가능하다.
