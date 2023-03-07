# 문제해결 1주 차 Review

1주 차 문제 발표 및 교수님 해법으로 수업이 이루어졌다.

## Ugly Number

> [문제 링크](https://leetcode.com/problems/ugly-number/)

``` c
bool isUgly(int n){
  if(n <= 0) return 0;

  while(n % 2 == 0) n /= 2;
  while(n % 3 == 0) n /= 3;
  while(n % 5 == 0) n /= 5;

  return n == 1;
}
```

## Climbing Stairs

> [문제 링크](https://leetcode.com/problems/climbing-stairs/)

``` c
int climbStairs(int n){
  int a = 0, b = 1, c;
  for(;n;n--) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}
```

피보나치수열인지 알아내는 게 중요한 문제, 이를 사용해서 만든 문제들이 많이 존재한다.

> T[n] =  T[n-1] + T[n-2]

## Factorial Trailing Zeros

> [문제 링크](https://leetcode.com/problems/factorial-trailing-zeroes/)

``` c
int trailingZeroes(int n){ // O(logn)
  int sum = 0;
  for(int i = 5; i <= n; i *= 5) sum += n / i;
  return sum;
}
```

팩토리얼은 매우 빠르게 증가하기 때문에 이를 계산하고 풀면 너무 큰 수를 다뤄야 하기 때문에 다른 방법을 찾는 게 Key Point.

## Count Primes

> [문제 링크](https://leetcode.com/problems/count-primes/)

``` c
int isPrime[5000001];
int countPrimes(int n){
  int i;
  for(i = 2; i < n; i++) isPrime[i] = 1;
  for(i = 2; i * i < n; i++) { 
    // i * i 아래에 있는 소수의 배수만 빼는 방식 매우 효율적이다.
    if(!isPrime[i]) continue;
    for(int j = i * i; j < n; j += i) isPrime[j] = 0;
    // i*i 밑은 이미 제거되었으므로 i*i부터 시작
  }
  int count = 0;
  for(i = 2; i < n; i++) count += isPrime[i];
  return count;
}
```

에라토테네스의 체의 문제
