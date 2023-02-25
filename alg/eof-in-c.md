# C언어 EOF

백준 알고리즘 문제를 풀다 보면 보통 몇 줄이 입력될지 맨 처음에 입력이 들어오는 게 대부분이지만 그렇지 않은 문제가 있다.

[10951-백준](https://www.acmicpc.net/problem/10951)이 이에 해당하는 문제로 결국 `End of File`을 다룰 줄 아는지에 대한 문제이다.

> `End of File - EOF`는 파일의 끝을 알리는 값으로 실제로는 -1과 같다.

먼저 입력을 담당하는 `scanf`의 `Return value`를 알아야 한다.

> Number of receiving arguments successfully assigned (which may be zero in case a matching failure occurred before the first receiving argument was assigned), or EOF if input failure occurs before the first receiving argument was assigned.
> 
> ref. [cppreference](https://en.cppreference.com/w/c/io/fscanf)

`scanf`는 성공적으로 받은 인수의 수를 반환하거나 첫 번째 인자를 할당받기 전 실패하면 `EOF`을 반환한다는 내용이다.

이러한 사실을 활용해서 코드를 짜면 위와 같은 문제를 해결할 수 있다.

``` c
int a;
while(scanf("%d", &a) != EOF) {
  printf("%d", a);
}
```

`while`문을 사용해서 `scanf`의 반환 값이 `EOF`일 때까지 반복해서 입력받고 이를 출력하는 코드이다.

즉 이를 통해 처음에 몇 개의 줄이 입력받는지 알려주지 않더라도 풀 수 있는 것이다.
