# 팩토리얼 0의 개수

> [백준 1676번](https://www.acmicpc.net/problem/1676)

## 문제

N! 에서 뒤에서부터 처음 0이 아닌 숫자가 나올 때까지 0의 개수를 구하는 프로그램을 작성하는 것으로 입력으론 (0<= N <= 500)의 정수가 주어지고 0의 개수를 출력하면 된다.

## 해설

팩토리얼은 워낙 빠르게 커지기 때문에 팩토리얼을 구하고 확인하면 메모리 오버플로우가 발생할 수 있기 때문에 이러한 방법으로 풀면 안 된다.

결국 뒷자리가 0이라는 것은 2와 5의 곱으로 10이 만들어 진것인데 따라서 2와 5를 잘 체크하면 10의 몇 배수인지 알 수 있기 때문에 팩토리얼을 구할 필요 없이 확인이 가능하다. 다만 2 같은 경우에는 5보다 작기 때문에 5보다 팩토리얼을 구하는 과정에서 많이 나오기 때문에 5만 신경 써서 구할 수 있을 것이다.

따라서 5의 배수일 때마다 +1, 5^2의 배수일 때마다 +2... 5^N의 배수일 때마다 +N이라는 가설을 가지고 구현해보자.

``` python
num = int(input())

n = 1
result = 0

while (n < num):
    n *= 5
    result += int(num / n)

print(result)
```

while 문을 사용해서 굳이 N 번 확인하지 않고 밑이 5인 logN 번 확인하여 결과를 출력하는 코드를 작성했다. 어차피 배수별로 몇 개가 있는지가 중요하기 때문에 위와 같은 코드를 작성할 수 있었다.
