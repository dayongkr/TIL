# 프로그래밍언어 5주 차

변수의 구성요소를 배우게된다.

## Introduction

변수의 속성으로는 이름, 주소, 값, 타입, 생명주기, 스코프가 있다.

- name
  - identifier로써의 역할을 한다.
  - length: 요즘 언어는 보통 제한이 없지만 컴파일러마다 다르다
  - special character: 특수문자를 포함하는 경우가 있다.
  - case sensitivity: 대소문자를 구분하는 경우가 있다.
  - reserved words: 예약어를 사용할 수 없다.
- Addresses
  - 할당될 메모리 주소
  - alias는 혼동을 준다
  - 파이썬은 값을 할당하면 reference가 풀린다.

## Binding

binding이란 개체 그리고 속성을 연결하는 것을 말한다.

- language design time
  - symbol들을 operation과 연결한다.
- langauge implementation time
  - 실수를 표현하는 방법
- compile time
  - 변수의 타입을 결정한다.
- load time
  - static 변수를 메모리에 할당한다.
- runtime
  - static이 아닌 변수를 메모리에 할당한다.
- static
  - runtime 이전에 binding이 결정된다.
- dynamic
  - 실행시간에 binding이 결정된다.
- explicit
  - 프로그래머가 결정한다.
- implicit
  - 컴파일러가 결정한다.

## variable attributes

- lifetime
  - allocation
  - deallocation
- static
  - 실행 이전에 메모리에 할당된다.
- stack-dynamic
  - 함수가 호출될 때 메모리에 할당된다.
- explicit heap-dynamic
  - 프로그래머가 할당하고 해제한다.
  - java는 garbage collector가 해제한다.
- implicit heap-dynamic
  - 프로그래머가 할당하지만 해제하지 않는다
