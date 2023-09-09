# 프로그래밍언어 2주 차

오늘은 Syntax와 Semantics에 대해 배웠고 그중 BNF(Context Free Grammar)에 대해 배웠다.

## Introduction

프로그래밍 언어란 인간과 기계이 소통하는 표현 방법 중 하나이다.

프로그래밍 언어는 두 부분을 나눌 수 있다.

- syntax: 표현식의 형태 또는 구조
- sematic: 표현식의 의미
- 둘의 경계는 항상 명확한 것은 아니다.

## Source to program

text file이 실행가능한 프로그램으로 바꾸는 과정은 다음과 같다.

- scanner: text file을 token으로 나눈다.
- parser: token을 parse tree로 바꾼다.
- semantic analyzer: parse tree를 semantic tree로 바꾼다.
- target code generator: semantic tree를 target code로 바꾼다.
- symbol table: symbol을 관리한다.

우리는 이중 syntax part인 scanner와 parser에 대해 배울 것이다.

## Syntax

syntax에서는 아래 어휘가 중요하다.

- sentence: string of characters
- language: set of sentences
- lexeme: the lowest level syntactic unit of a language
- token: a category of lexemes
- recognizer: 입력을 받고 그것이 언어에 속하는지 판단하는 것
- generator: 언어의 문장을 생성하는 것
- lexical analysis: 어휘 분석 -> token으로 나누는 것
- syntax analysis: 문법 분석 -> parse tree로 바꾸는 것

### Grammar

문법은 언어의 문장을 만드는 규칙이다. 또한 문법은 의미를 설명할 필요없고 옳음만 확인하면 된다.

#### Context Free Grammar

1950년에 noam chomsky가 개발한 language generator로 문법의 규칙을 나타낸다. 이는 추후에 BNF로 발전하게 된다.

#### BNF

LHS는 a single non-terminal symbol, RHS는 terminal, non-terminal symbols로 이루어져있다.

- 문법은 한정적이고 빈규칙은 존재하지 않는다.
- | 또는 or로 조합을 조합할 수 있다.
- BNF는 다른 언어를 설명하는 언어로 metalanguage라고 한다.
- pre-terminal은 single terminal symbol로 이루어져있다.
- recursion을 사용해서 repetition을 구현할 수 있다.
  - recursion이 존재하는 언어는 infinite language라고 하고 아닌 경우는 finite language라고 한다.
- rule을 terminal symbol로만 이루어지게 만드는 것을 derivation이라고 하고 이를 수행하는 순서에 따라 leftmost, rightmost등으로 부른다.

#### parse tree

parse tree는 derivation을 계층적으로 표현한 것을 말한다.

간혹 하나의 grammar에서 여러 parse tree를 만들 수 있는 경우가 있는데 이를 ambiguous gram,ar라고 한다.
