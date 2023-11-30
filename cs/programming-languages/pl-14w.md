# 프로그래밍언어 14주 차

## 함수형 프로그래밍

- Imperative language: von Neumann architecture
- Functional language: mathematical functions
  - mathematical functions: domain set을 range set으로 mapping하는 것
- 변수를 사용하지 않고 반복문도 사용하지 않는다.
- 함수의 합성으로 프로그램을 작성한다.
- 함수는 first-class value이다.
- higher-order function을 사용한다.
  - 함수를 인자로 받거나 함수를 리턴하는 함수
- Apply to all
  - map, filter, reduce
- Fundamental of FPL
  - mimicking mathematical functions
  - 변수를 관리하지 않아도 되므로 side effect가 없다.
  - Referential transparency
    - 함수의 결과는 인자에만 의존한다.
    - 함수의 결과는 항상 동일하다.

## Scheme - DrRacket

- ((lambda (x) (\* x x)) 3) => 9
- (+ 5 2) => 7
- (define (square x) (\* x x)) => (square 3) => 9
  - 함수 정의
- #t => true #f => false
- even? => 짝수인지 확인, odd? => 홀수인지 확인, zero? => 0인지 확인, positive? => 양수인지 확인, negative? => 음수인지 확인
- (if 조건 참일때 거짓일때) => 조건이 참이면 참일때를 실행하고 거짓이면 거짓일때를 실행한다.
- (cond (조건1 참일때) (조건2 참일때) (else 거짓일때)) => 조건1이 참이면 참일때를 실행하고 조건2가 참이면 참일때를 실행하고 둘다 거짓이면 거짓일때를 실행한다.
- '(A B) => list A B
- (car '(A B)) => A : list의 첫번째 원소를 리턴한다.
- (cdr '(A B)) => (B) : list의 첫번째 원소를 제외한 나머지 원소를 리턴한다.
- (cons 'A '(B C)) => (A B C) : list를 만든다.
- EQ? => pointer value를 비교한다.
- EQV? => value를 비교한다.
- list? => list인지 확인한다.
- null? => list가 비어있는지 확인한다.
- (let ((x 3) (y 4)) (+ x y)) => 7 : lambda의 syntactic sugar
