# Min-max heap

min, max heap의 장점을 가져온 CBT이다.

- root node는 min, 그 아래에는 max가 존재한다.
- min, max level이 번갈아 존재한다.
- min level에 있는 노드는 해당 노드의 subtree 중 가장 작은 key를 가진다
- max level에 있는 노드는 해당 노드의 subtree 중 가장 작은 key를 가진다

## 동작

push down(trickle down)을 사용해서 build를 한다.

```
function FLOYD-BUILD-HEAP(h):
  each index i from (length(h)/2 to 1):
    PUSH-DOWN(h, i)
  return h
```

h는 초기 배열이다.

### push down pseudo code

```
function PUSH-DOWN(h, i):
  만약에 i가 min level에 있으면:
    PUSH-DOWN-MIN(h, i)
  만약에 i가 max level에 있으면:
    PUSH-DOWN-MAX(h, i)
```
